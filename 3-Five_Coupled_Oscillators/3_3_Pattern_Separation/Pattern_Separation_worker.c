/*
    STDP_Learned_Synchrony_worker.c

*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

#include "../../utils/neuro/get_last_period/get_last_period.h"
#include "../../utils/fileIO/fileIO.h"
#include "../../utils/basic_math/basic_math.h"
#include "../../utils/neuro/rateN/rateN.h"
#include "../../utils/neuro/rateSTDP/rateSTDP.h"
#include "../../utils/sig_proc/phdiff2.h"
#include "Pattern_Separation.h"
#include "../../utils/multithreads/multithreads.h"

//Define "within" function
//checks if x and v are within t of each other
#ifndef ABS
#define ABS(x) ( ((x)>0) ? (x) : (-(x)) )
#endif

#ifndef WITHN
#define WITHN(x,v,t) ( ABS((x)-(v))<(t) ? 1 : 0 )
#endif

#ifndef MAX
#define MAX(x,y) ( x>y ? x : y )
#endif

void * Pattern_Separation_worker(void * arg){

    //cast input args to data structure
    THREAD_3_2_DAT * IN = arg;

    //********************** INITIALIZE PARAMS!!! *************************

    // Initialize random seed
    int randseed = time(NULL);
    srand( randseed );
    printf("Thread %d seeded with %d\n", IN->id, randseed);

    // Simulation Params
    int tr, st, i, j, k, l, t, pat, gr;  //counters
    double pat_score, pat_score2;
    double withresh = 0.8;
    int n_s = 5000;  //timesteps in each step
    int n_perc = 10000;  //timesteps in simulation for calculating perc correct
    double dt = 1e-4;   //timestep duration
    int no = 5; //number of oscillators
    int g = 2*no;   //number of neuron groups
    double R_s[n_s][g]; //Rate vectors for step
    double R_perc[n_perc][g]; //Rate vectors for finding perccorr
    double gamma[g];
        for ( i=0; i<g; i+=2 ){
            gamma[i] = 10;      //E cells
            gamma[i+1] = -10;   //I cells
        }
    double tau[g];
        for ( i=0; i<g; i+=2 ){
            tau[i] = 2e-3;      //E cells (AMPA syn time constant)
            tau[i+1] = 10e-3;   //I cells (GABA_A syn time constant)
        }
    
    //Weights
    double wee=2, wei=2.873, wie=-2.873, wii=-2;  //Within-oscillator weights
        double wW[2][2];
        wW[0][0]=wee;   wW[0][1]=wei;   //EE    EI
        wW[1][0]=wie;   wW[1][1]=wii;   //IE    II
    double W_0[g][g];
        //double xee=0.2, xei=0.3, xie=-0.5, xii=0;  //Init Between-osc weights
        double wf = 2/((double) no);
        double xee=0.2*wf, xei=0.3*wf, xie=-0.5*wf, xii=0*wf;  //Init Between-osc weights
        //double xee=0.2, xei=0.3, xie=-0.5, xii=0;  //Init Between-osc weights
        assignPingW(no, W_0, wee, wei, wie, wii, xee, xei, xie, xii);
    int step = 10; //step for recording plasticity
    double W_t[n_s/step][g][g];
    int W_c[g][g];  //Which synapses have plasticity?
        for (i=0; i<g; i++){ 
            for (j=0; j<g; j++){ 
                if (i%2==0 && j%2==0){
                    W_c[i][j]=1; //only xEE synapses change
                } else {
                    W_c[i][j]=0;
                }
            }
        }

    //Get init rates
    double R_i[g];
    int p=1000;
    double rates[p][2];
    get_last_period(&p, rates, wW);

    //Trial parameters
    int numtr = IN->numtr;     //number of trials
    int numsteps = IN->numsteps;  //number of stdp measurements within each trial
    double W_tr[g][g]; //weights for this trial
    //phasediff trial params
    int percres = IN->percres;    //resolution of phdiff measurements per step
    double perc_sum;
    double perc_sum2;
    double pds[g][g];

    //Randomness/heterogeinity
    double w_ran = 0.001;
    //double w_ran = 0.005;
    //double r_ran = 0.02;
    double r_ran = 0.02;
    double r_noise = 0.01;

    //filenames
    /*
    char * fname_cum_w = "cum_w.dat";
        FILE * cum_w_file_n = fopen(fname_cum_w, "w");
        fclose(cum_w_file_n);
        FILE * cum_w_file;
    char * fname_cum_r = "cum_r.dat";
        FILE * cum_r_file_n = fopen(fname_cum_r, "w");
        fclose(cum_r_file_n);
        FILE * cum_r_file;
    */
    char * fname_cum_r_t = "cum_r_t.dat";
        FILE * cum_r_t_file_n = fopen(fname_cum_r_t, "w");
        fclose(cum_r_t_file_n);
        FILE * cum_r_t_file;
    
    //Patterns
    int numpats = 2;
    int p_ind;
    double pats[numpats][no];
        //First pattern (1, 2, 3)
        pats[0][0] = 0;
        pats[0][1] = 0;
        pats[0][2] = 0;
        pats[0][3] = M_PI;
        pats[0][4] = M_PI;
        //Second pattern (3, 4, 5)
        pats[1][0] = M_PI;
        pats[1][1] = M_PI;
        pats[1][2] = 0;
        pats[1][3] = 0;
        pats[1][4] = 0;
    double t_pat[no]; //TEST PATTERN FOR PATTERN SEPARATION
        /*
        t_pat[0] = 0; 
        t_pat[1] = 0;
        t_pat[2] = M_PI; 
        t_pat[3] = 0;
        t_pat[4] = 0; 
        */
        t_pat[0] = 0; 
        t_pat[1] = M_PI;
        t_pat[2] = M_PI; 
        t_pat[3] = M_PI;
        t_pat[4] = 0; 

    //declare array for storing weights
    double weights[numsteps*numpats][no-1];

    //********************* SIMULATE STARTING IN-PHASE!!! ********************

    for (tr=IN->a; tr<IN->b; tr++){
        
        //set init weights with a *little* randomness
        for (i=0;i<g;i++){ 
            for (j=0;j<g;j++){ 
                W_tr[i][j]=W_0[i][j]+w_ran*gen_randn(); 
            }
        }

        //Simulate in steps
        for (st=0; st<numsteps; st++){

            printf("Trial %d of %d, Step %d of %d\n", tr, numtr, st, numsteps);

            //Present each pattern + update weights
            for (pat=0; pat<numpats; pat++){
                
                //Set init rates
                for (gr=0; gr<no; gr++){
                    p_ind = ( (int) (
                            p + 
                            (((double) p)*pats[pat][gr]/2/M_PI) + //plus pattern phase
                            (((double) p)*r_ran*gen_randn()/M_PI) // +/- r_ran phase
                        ))
                        %p;
                    //printf("train: p_ind for patt:%d gr:%d = %d\n", pat, gr, p_ind);
                    R_i[gr*2] = rates[p_ind][0]+r_noise*gen_rand(); //E
                    R_i[gr*2+1] = rates[p_ind][1]+r_noise*gen_rand(); //I
                    //if (IN->id==0){ printf("\tpats[%d][%d]=%f\tp_ind=%d    \trates[%d]=%f\n", pat, gr, pats[pat][gr], p_ind, gr*2, rates[p_ind][0]); }
                }

                //Simulate w/ pattern
                rateN(g, n_s, R_s, R_i, W_tr, gamma, tau, dt);

                //save rates to file
                if (IN->id==0 && st%10==0 && (st>100 || st<1)){
                    printf("saving rates\n");
                    cum_r_t_file = fopen(fname_cum_r_t, "a");
                    for (t=0; t<n_s-1; t++){
                        for (gr=0; gr<no; gr++){
                            fprintf(cum_r_t_file, "%f \t", R_s[t][gr*2]);
                        }
                        fprintf(cum_r_t_file, "\n");
                    }
                    fclose(cum_r_t_file);
                }

                //Apply STDP
                rateSTDP(n_s, g, dt, R_s, W_t, W_tr, W_c); 

                //print weights
                /*
                printf("weights:\n");
                for (i=0;i<no;i++){ 
                    for (j=0;j<no;j++){ 
                        printf("%f \t", W_tr[2*i][2*j]);
                    }
                    printf("\n");
                }
                */

                //Update weights
                for (i=0;i<g;i++){ 
                    for (j=0;j<g;j++){ 
                        if (W_t[n_s/step-1][i][j]>0.0 && W_t[n_s/step-1][i][j]<1.0){
                            W_tr[i][j] = W_t[n_s/step-1][i][j]; 
                        }
                    }
                }


            }

            //find perc correct over lots of trials on TEST PATTERN
            perc_sum = 0;
            perc_sum2 = 0;
            for (i=0; i<percres; i++){
                    
                //set init rates for test pattern w/ randomness
                for (gr=0; gr<no; gr++){
                    p_ind = ( (int) (
                            p + 
                            (((double) p)*t_pat[gr]/2.0/M_PI) + //plus pattern phase
                            (((double) p)*r_ran*gen_randn()/M_PI) // +/- r_ran phase
                        ))
                        %p;
                    R_i[gr*2] = rates[p_ind][0]+r_noise*gen_rand(); //E
                    R_i[gr*2+1] = rates[p_ind][1]+r_noise*gen_rand(); //I
                }

                //Simulate
                rateN(g, n_perc, R_perc, R_i, W_tr, gamma, tau, dt);

                //accuracy on training 
                phdiff2(n_perc, g, R_perc, pds);

                //what % of the time does it end up in pat[0] first pattern
                pat_score = 0;
                for (gr=0; gr<no; gr++){
                    if (WITHN(ABS(pds[0][0]-pds[0][2*gr]), ABS(pats[0][0]-pats[0][gr]), withresh)){
                        pat_score++;
                    }
                }
                if (pat_score==no){
                    perc_sum++;
                }

                //what % of the time does it end up in pat[1] second pattern
                pat_score2 = 0;
                for (gr=0; gr<no; gr++){
                    if (WITHN(ABS(pds[0][0]-pds[0][2*gr]), ABS(pats[1][0]-pats[1][gr]), withresh)){
                        pat_score2++;
                    }
                }
                if (pat_score2==no){
                    perc_sum2++;
                }

            //save rates to file
            /*
            if (IN->id==0 && i==0 && st%10==0 && (st>100 || st<1)){
                printf("saving rates\n");
                cum_r_file = fopen(fname_cum_r, "a");
                for (t=0; t<n_perc-1; t++){
                    for (gr=0; gr<no; gr++){
                        fprintf(cum_r_file, "%f \t", R_perc[t][gr*2]);
                    }
                    fprintf(cum_r_file, "\n");
                }
                fclose(cum_r_file);
            }
            */

            }

            //Add this avg perc correct to array
            IN->perccorr[tr*numsteps+st] = perc_sum/((double) percres);
            IN->perccorr2[tr*numsteps+st] = perc_sum2/((double) percres);
            printf("percscore=%f\tpercscore2=%f\n", perc_sum/((double) percres), perc_sum2/((double) percres));
            

        }

    }

}

