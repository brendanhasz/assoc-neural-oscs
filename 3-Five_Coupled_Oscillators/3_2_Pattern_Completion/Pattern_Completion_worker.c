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
#include "Pattern_Completion.h"
#include "../../utils/multithreads/multithreads.h"

//Define "within" function
//takes number, a value, and a threshold (number w/i thresh of value)
#ifndef WI
#define WI(x,v,t) (((x<v+t) && (x>v-t)) ? 1 : 0)
#endif

void * Pattern_Completion_worker(void * arg){

    //cast input args to data structure
    THREAD_3_2_DAT * IN = arg;

    //********************** INITIALIZE PARAMS!!! *************************

    // Initialize random seed
    int randseed = time(NULL);
    srand( randseed );
    printf("Thread %d seeded with %d\n", IN->id, randseed);

    // Simulation Params
    int tr, st, i, j, k, l, t, pat, gr;  //counters
    double pat_score;
    double withresh = 0.5;
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
        double xee=0.2, xei=0.3, xie=-0.5, xii=0;  //Init Between-osc weights
        assignPingW(no, W_0, wee, wei, wie, wii, xee, xei, xie, xii);
    int step = 10; //step for recording plasticity
    double W_t[n_s/step][g][g];
    int W_c[g][g];  //Which synapses have plasticity?
        for (i=0; i<g; i++){ for (j=0; j<g; j++){ W_c[i][j]=0; }}
        W_c[0][2]=1;    W_c[2][0]=1;    //Only xee synapses change

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
    double pds[g][g];

    //Randomness/heterogeinity
    double w_ran = 0.01;
    double r_ran = 0.01;
    double r_noise = 0.001;

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
    double t_pat[no];
        t_pat[0] = 0; 
        t_pat[1] = M_PI; 
        t_pat[2] = 0; 
        t_pat[3] = M_PI; 
        t_pat[4] = M_PI; 

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
                    printf("train: p_ind for patt:%d gr:%d = %d\n", pat, gr, p_ind);
                    R_i[gr*2] = rates[p_ind][0]+r_noise*gen_rand(); //E
                    R_i[gr*2+1] = rates[p_ind][1]+r_noise*gen_rand(); //I
                }

                //Simulate w/ pattern
                rateN(g, n_s, R_s, R_i, W_tr, gamma, tau, dt);

                //Apply STDP
                rateSTDP(n_s, g, dt, R_s, W_t, W_tr, W_c); 

                //Update weights
                for (i=0;i<g;i++){ 
                    for (j=0;j<g;j++){ 
                        W_tr[i][j] = W_t[n_s/step-1][i][j]; 
                    }
                }

            }

            //find perc correct over lots of trials on TEST PATTERN
            perc_sum= 0;
            for (i=0; i<percres; i++){
                    
                //set init rates for test pattern w/ randomness
                for (gr=0; gr<no; gr++){
                    p_ind = ( (int) (
                            p + 
                            (((double) p)*t_pat[gr]/2/M_PI) + //plus pattern phase
                            (((double) p)*r_ran*gen_randn()/M_PI) // +/- r_ran phase
                        ))
                        %p;
                    printf("test: p_ind for patt:%d gr:%d = %d\n", pat, gr, p_ind);
                    R_i[gr*2] = rates[p_ind][0]+r_noise*gen_rand(); //E
                    R_i[gr*2+1] = rates[p_ind][1]+r_noise*gen_rand(); //I
                }

                //simulate
                rateN(g, n_perc, R_perc, R_i, W_tr, gamma, tau, dt);

                //is the SS pattern correct? (use alpha-score?)
                phdiff2(n_perc, g, R_perc, pds);
                pat_score = 0;
                for (gr=0; gr<no; gr++){
//#define WI(x,v,t) (((x<v+t) && (x>v-t)) ? 1 : 0)
                    if (WI(pats[0][i]-pats[0][0],0,withresh) == WI(pds[0][gr]-pds[0][0],0,withresh)){
                        pat_score++;
                    }
                }
                pat_score = pat_score/no;

                //add this perc correct score to sum
                perc_sum += pat_score;

            }

            //Add this avg perc correct to array
            IN->perccorr[tr*numsteps+st] = perc_sum/percres;

        }

    }



}

