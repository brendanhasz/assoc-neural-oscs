/*
    STDP_Learned_Synchrony.c

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

int main(void){

    //********************** INITIALIZE PARAMS!!! *************************

    // Initialize random seed
    int randseed = time(NULL);
    srand( randseed );
    printf("Seeded with %d\n", randseed);

    // Simulation Params
    int tr, st, i, j, k, l, t;  //counters
    int n_s = 5000;  //timesteps in each step
    int n_pd = 10000;  //timesteps in simulation for calculating SS phdiff
    double dt = 1e-4;   //timestep duration
    int no = 2; //number of oscillators
    int g = 2*no;   //number of neuron groups
    double R_s[n_s][g]; //Rate vectors for step
    double R_pd[n_pd][g]; //Rate vectors for finding phase diff
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
    double W_0i[g][g]; //Between-oscillator weights ss=in
        double ixee=0.15, ixei=0, ixie=0, ixii=0;    
        assignPingW(no, W_0, wee, wei, wie, wii, ixee, ixei, ixie, ixii);
    double W_0o[g][g]; //Between-oscillator weights ss=out
        double oxee=0, oxei=1, oxie=0, oxii=0;            
        assignPingW(no, W_0o, wee, wei, wie, wii, oxee, oxei, oxie, oxii);
    int step = 10;
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
    int numtr = 10;     //number of trials
    int numsteps = 10;  //number of stdp measurements within each trial
    double Wxee_tr[numtr][2][numsteps]; //xEE Weights over time for each trial
    double W_tr[g][g]; //weights for a trial
    //phasediff trial params
    int pd_res = 100;    //resolution of phdiff measurements per step
    int numpdtr = 10;   //number of trials per init phase diff
    double pd_tr[numtr][pd_res][numsteps]; //SS phase difference over time for each trial
    double pd_sum;
    double pds[g][g];

    //Filenames
    char * cum_rate_fname = "cum_rate.dat";
        FILE * cum_rate_file_n = fopen(cum_rate_fname, "w"); //Create new file
        fclose(cum_rate_file_n);
        FILE * cum_rate_file; //file pointer for append
    char * cum_weight_fname = "cum_weight.dat";
        FILE * cum_weight_file_n = fopen(cum_weight_fname, "w"); //New file
        fclose(cum_weight_file_n);
        FILE * cum_weight_file; //file pointer for append
    char * cum_phdiffs_fname = "cum_phdiffs.dat";
        FILE * cum_phdiffs_file_n = fopen(cum_phdiffs_fname, "w"); //New file
        fclose(cum_phdiffs_file_n);
        FILE * cum_phdiffs_file; //file pointer for append
    
    char * weight_fname = "weight.dat";
    char * phdiffs_fname = "phdiffs.dat";

    //Multithreading
    //TODO


    printf("Got to simulating!\n");


    //************************* SIMULATE!!! ****************************
    //STARTING IN-PHASE
    //initialize per-thread params to start in-phase
    //for (i=0; i<NUM_THREADS; i++){
    //    pthread_create(&threads[i], NULL, STDP...worker, (void*)&t_args[i]);
    //}
    //waitfor_threads(NUM_THREADS, threads);

    for (tr=0; tr<numtr; tr++){
        
        //set init weights with a *little* randomness
        for (i=0;i<g;i++){ 
            for (j=0;j<g;j++){ 
                W_tr[i][j]=W_0[i][j]+0.001*gen_randn(); 
            }
        }

        //Simulate in steps
        for (st=0; st<numsteps; st++){

            printf("Trial %d of %d, Step %d of %d\n", tr, numtr, st, numsteps);

            //Set init rates (in-phase) w/ randomness
            R_i[0] = rates[0][0]+0.01*gen_rand();  //g1 E
            R_i[1] = rates[0][1]+0.01*gen_rand();  //g1 I
            R_i[2] = rates[0][0]+0.01*gen_rand();  //g2 E
            R_i[3] = rates[0][1]+0.01*gen_rand();  //g2 I

            //Simulate w/ new weights for this step
            rateN(g, n_s, R_s, R_i, W_tr, gamma, tau, dt);

            //Find weight change for this step
            rateSTDP(n_s, g, dt, R_s, W_t, W_tr, W_c); 
            
            //update weights
            for (i=0;i<g;i++){ 
                for (j=0;j<g;j++){ 
                    W_tr[i][j] = W_t[n_s/step-1][i][j]; 
                }
            }

            //record new weights
            Wxee_tr[tr][0][st] = W_tr[0][2];
            Wxee_tr[tr][1][st] = W_tr[2][0];

            printf("\tWxee = %f, %f\n", Wxee_tr[tr][0][st], Wxee_tr[tr][1][st]);

            //find phdiff vector w/ new weights
            for (i=0; i<pd_res; i++){
                pd_sum = 0;
                for (j=0; j<numpdtr; j++){
                    
                    //set init rates for this init phdiff w/ randomness
                    R_i[0] = rates[0][0]+0.01*gen_rand();  //g1 E
                    R_i[1] = rates[0][1]+0.01*gen_rand();  //g1 I
                    R_i[2] = rates[i/pd_res*p][0]+0.01*gen_rand();  //g2 E
                    R_i[3] = rates[i/pd_res*p][1]+0.01*gen_rand();  //g2 I

                    //simulate
                    rateN(g, n_pd, R_pd, R_i, W_tr, gamma, tau, dt);

                    //find steady state phdiff
                    phdiff2(n_pd, g, R_pd, pds);
                    
                    //add this phdiff to sum
                    pd_sum += pds[0][2];

                }

                //Add this avg phdiff to array
                pd_tr[tr][i][st] = pd_sum/numpdtr;

            }

            //Append to files
            //Append weight vectors
            cum_weight_file = fopen(cum_weight_fname,"a"); //file pointer for append
            for (i=0; i<n_s/step-1; i++){
                fprintf(cum_weight_file, "%f\t%f\n", W_t[i][0][2], W_t[i][2][0]);
            }
            fclose(cum_weight_file);

            //Append rate vectors
            cum_rate_file = fopen(cum_rate_fname,"a"); //file pointer for append
            for (i=0; i<n_s; i++){
                fprintf(cum_rate_file, "%f\t%f\n", R_s[i][0], R_s[i][2]);
            }
            fclose(cum_rate_file);

            //Append phdiff vectors
            cum_phdiffs_file = fopen(cum_phdiffs_fname,"a"); //file pointer for append
            for (i=0; i<pd_res; i++){
                fprintf(cum_phdiffs_file, "%f\t", pd_tr[tr][i][st]);
            }
            fprintf(cum_phdiffs_file, "\n");
            fclose(cum_phdiffs_file);

        }

    }




    //STARTING OUT-OF-PHASE
    //TODO




    return 0;

}

