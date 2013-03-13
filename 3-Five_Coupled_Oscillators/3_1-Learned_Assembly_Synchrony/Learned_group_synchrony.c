/* Learned_Synchrony.c- shows how 2 oscillators can learn to 
                        oscillate in-phase

    Copyright 2012
    Brendan Hasz
    bhasz@brandeis.edu
    www.cs.brandeis.edu/~bhasz/main.php
    Brandeis University, Waltham, MA, USA

*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include "../../utils/neuro/get_last_period/get_last_period.h"
#include "../../utils/basic_math/basic_math.h"
#include "../../utils/neuro/plasticPingRateN_recW/plasticPingRateN_recW.h"
#include "../../utils/fileIO/fileIO.h"
#include "../../utils/multithreads/multithreads.h"
#include "Learned_group_synchrony_worker.h"
#include "../../utils/stats/stats.h"

int main(void){

    /*********** INITIALIZE STUFF *************/
    /* Initialize random seed */
    time_t randseed = time(NULL);
    srand(randseed);
    printf("Seeded with %lld\n", (long long) randseed);

    int n=10000; //timesteps per plastic trial
    int no=5; //number of oscillators
    int plasticTrials = 10;
    int g=2*no; //number of groups
    double dt = 0.0001;
    int t,i,j,k,l;  //counters
    double Re[n][no], R_i[no][2]; //Excitatory rate vector and initial rate vec
    double R[n][g]; //All groups rate vec

    //Init weights
    int rw = 100;  //how often to record syn weights
    double W_t[n/rw][g][g]; //Weight matrix over time
    double wW[2][2];    //Within-oscillator synaptic weights
        wW[0][0]=2;         wW[0][1]=2.873; //EE    EI
        wW[1][0]=-2.873;    wW[1][1]=-2;    //IE    II
    double scl = 2/no;
    double xW[2][2];    //Initial x-group synaptic strengths
        xW[0][0]=0.2*scl;   xW[0][1]=0.3*scl;   //xEE   xEI
        xW[1][0]=-0.5*scl;  xW[1][1]=0*scl;     //xIE   xII
    double W[g][g];    //All weights
    for (i=0;i<g;i+=2){ for (j=0;j<g;j+=2){
        for (k=0;k<2;k++){ for (l=0;l<2;l++){
            if (i==j){ //within group block
                W[i+k][j+l] = wW[k][l];
            } else { //x-group
                W[i+k][j+l] = xW[k][l];
            }
        }}
    }}
    double W_1D[g*g];
    for (i=0;i<g;i++){
        for (j=0;j<g;j++){
            W_1D[g*i+j] = W[i][j];
        }
    }

    //Weights alowed to change?
    int W_c[g][g];
    for (i=0;i<g;i++){ for (j=0;j<g;j++){
        if (i%2==0 && j%2==0 && i!=j){ //if we're @ an xEE weight,
            W_c[i][j]=1;
        } else {
            W_c[i][j]=0;
        }
    }}

    //Weight bounds?
    int W_b[g][g];
    for (i=0;i<g;i++){ for (j=0;j<g;j++){
        if (i%2==0 && j%2==0 && i!=j){ //if we're @ an xEE weight,
            W_b[i][j]=0.3;
        } else {
            W_b[i][j]=0;
        }
    }}

    //Plasticity time constants
    double t_w = 5000;
    double t_th = 500;

    double th[g][g];
    for (i=0;i<g;i++){ for (j=0;j<g;j++){
        if (i%2==0 && j%2==0 && i!=j){ //if we're @ an xEE weight,
            th[i][j]=15;
        } else {
            th[i][j]=0;
        }
    }}

    //Gamma and tau
    double gamma[g];
    for (i=0;i<g;i+=2){
        gamma[i] = 10;      //Excitatory
        gamma[i+1] = -10;   //Inhibitory
    }
    double tau[g];
    for (i=0;i<g;i+=2){
        tau[i] = 0.002; //AMPA (Excitatory - 2ms)
        tau[i+1] = 0.01; //GABA_A (Inhibitory - 10ms)
    }

    //Find initial rate vector
    int p=1000;
    double lp_rates[p][2];
    get_last_period(&p, lp_rates, wW);

    double R_i_A1[no][2];
            R_i_A1[0][0] = lp_rates[0][0]+gen_rand(); //O1, 2, and 3 are IN-phase,
            R_i_A1[0][1] = lp_rates[0][1]+gen_rand();
            R_i_A1[1][0] = lp_rates[0][0]+gen_rand();
            R_i_A1[1][1] = lp_rates[0][1]+gen_rand();
            R_i_A1[2][0] = lp_rates[0][0]+gen_rand();
            R_i_A1[2][1] = lp_rates[0][1]+gen_rand();
            R_i_A1[3][0] = lp_rates[p/2][0]+gen_rand(); //O4, 5 are OUT-phase
            R_i_A1[3][1] = lp_rates[p/2][1]+gen_rand();
            R_i_A1[4][0] = lp_rates[p/2][0]+gen_rand();
            R_i_A1[4][1] = lp_rates[p/2][1]+gen_rand();


    //Multithreading stuff
    int pd_res = 1000;
    double phdiffs[4*pd_res];
    pthread_t threads[NUM_THREADS];
    THREAD_DAT_1D t_args[NUM_THREADS];
    int t_divs[NUM_THREADS+1];
    segment_threads(NUM_THREADS, 0, pd_res, t_divs);

    double o2_vec[pd_res], o3_vec[pd_res], o4_vec[pd_res], o5_vec[pd_res]; 
    int pl_res = 1; //How many plastic runs to do
    double avgphdiffs[pl_res][4];
    double stdphdiffs[pl_res][4];
    
    //put data in thread args
    for (i=0;i<NUM_THREADS;i++){
        t_args[i].id = i;
        t_args[i].a = t_divs[i];
        t_args[i].b = t_divs[i+1];
        t_args[i].res = pd_res;
        t_args[i].DATA = (double *)&phdiffs;
        t_args[i].DATA_IN = (double *)&W_1D;
    }


    /*********** TESTER RUN OF 5 GROUPS w/ RANDOM START ***********/
/*
    double Rees[n][no];
    int nn = 20000, phaseInd;
    double R_i_rand[no][2];
            R_i_rand[0][0] = lp_rates[0][0];
            R_i_rand[0][1] = lp_rates[0][1];
            R_i_rand[1][0] = lp_rates[0][0];
            R_i_rand[1][1] = lp_rates[0][1];
        for (i=2;i<no;i++){
            phaseInd = rand() % p;
            R_i_rand[i][0] = lp_rates[phaseInd][0];
            R_i_rand[i][1] = lp_rates[phaseInd][1];
        }
    pingRateN(nn,no,Rees,R_i_rand,W[0]*2/5,W[1]*2/5,W[2]*2/5,W[3]*2/5,wW,dt);
    char * fn_prnt = "Learned_group_synchrony_5grouptester.dat";
    asave(n, no, Rees, fn_prnt);
    printf("Done with pingRateN 5-group tester - data saved as %s\n", fn_prnt);
 */   



/******************************* LOOP THROUGH PLASTIC RUNS *****************/

    //Create new file to store weights
    char * fn_plas_w = "Learned_group_synchrony_plas_w.dat";
    FILE * pFile_w = fopen(fn_plas_w,"w"); 
    //fprintf(pFile_wn, "\n"); fclose(pFile_wn);
    //FILE * pFile_w = fopen(fn_plas_w,"a"); //now open it for appending

    //Create new file to store weights
    char * fn_plas_r = "Learned_group_synchrony_plas_r.dat";
    FILE * pFile_r = fopen(fn_plas_r,"w"); 
    //fprintf(pFile_rn, "\n"); fclose(pFile_rn);
    //FILE * pFile_r = fopen(fn_plas_r,"a"); //now open it for appending


int pr; //plastic loops
for (pr=0; pr<pl_res;pr++){

    /*********** BEFORE PLASTICITY AVG PHDIFFS *************/
    //Run threads
    for (i=0;i<NUM_THREADS;i++){
        pthread_create(&threads[i],NULL,Learned_group_synchrony_worker,(void*)&t_args[i]);
    }

    //Wait for threads to finish
    waitfor_threads(NUM_THREADS, threads);

    //Find avg phdiffs
    for (i=0;i<pd_res;i++){
        o2_vec[i] = phdiffs[i*4];
        o3_vec[i] = phdiffs[i*4+1];
        o4_vec[i] = phdiffs[i*4+2];
        o5_vec[i] = phdiffs[i*4+3];
    }
    avgphdiffs[pr][0] = mean(pd_res, o2_vec);    
    avgphdiffs[pr][1] = mean(pd_res, o3_vec);    
    avgphdiffs[pr][2] = mean(pd_res, o4_vec);    
    avgphdiffs[pr][3] = mean(pd_res, o5_vec);    

    stdphdiffs[pr][0] = std(pd_res, o2_vec);    
    stdphdiffs[pr][1] = std(pd_res, o3_vec);    
    stdphdiffs[pr][2] = std(pd_res, o4_vec);    
    stdphdiffs[pr][3] = std(pd_res, o5_vec);    

    printf("%d: Avg ph diff between O1 and O2: %f +/- %f\n", pr, avgphdiffs[pr][0], stdphdiffs[pr][0]);
    printf("%d: Avg ph diff between O1 and O3: %f +/- %f\n", pr, avgphdiffs[pr][1], stdphdiffs[pr][1]);
    printf("%d: Avg ph diff between O1 and O4: %f +/- %f\n", pr, avgphdiffs[pr][2], stdphdiffs[pr][2]);
    printf("%d: Avg ph diff between O1 and O5: %f +/- %f\n", pr, avgphdiffs[pr][3], stdphdiffs[pr][3]);




    /*********** DO PLASTIC RUNS WHERE A1 IS IN-PHASE ******************/
    printf("STARTING PLASTIC RUN %d\n", pr);

    //Simulate
    //for (l=0; l<plasticTrials; l++){ //alternate A1, A2
    //ASSEMBLY 1

    //plasticRateN_recW call
    plasticRateN_recW(g,n,R,R_i_A1,W_t,W_c,W,W_b,t_w,th,t_th,gamma,tau,dt);
    //Set 2D matrix returned as W -> W_1D for doing above step
    for (i=0;i<g;i++){ for (j=0;j<g;j++){
        W_1D[g*i+j] = W[i][j];
    }}
    //Append to file for weights
    for (t=0;t<n/rw;t++){
        for (i=0;i<g;i++){ for (j=0;j<g;j++){
            if (i%2==0 && j%2==0 && i!=j){ //if we're @ an xEE weight,
                fprintf(pFile_w, "%f\t", W_t[t][i][j]);
            }
        }}
        fprintf(pFile_w, "\n"); //new timestep
    }
    //Append to file for rates
    for (t=0; t<n; t++){ 
        for (i=0;i<no;i++){
            fprintf(pFile_r, "%f\t", Re[t][i]);
        }
        fprintf(pFile_r, "\n");
    }

    printf("DONE WITH PLASTIC RUN %d\n", pr);

/*
        //ASSEMBLY 2
        plasticPingRateN_recW(n,no,Re,R_i_A2,W[0],W[1],W[2],W[3],
                            xEE_c,xEI_c,xIE_c,xII_c,wW,dt,W_t);    
        W[0] = (W_t[n/rw-1][0][2]+W_t[n/rw-1][0][2])/2; //set new xEE weight for next run
        printf("xEE weight after plastic run %d (A1): %f\n",i,W_t[n/rw-1][0][2]);
        //Append to file for weights
        for (t=0;t<n/rw;t++){
            for (i=0;i<g;i++){ for (j=0;j<g;j++){
                if (i%2==0 && j%2==0 && i!=j){ //if we're @ an xEE weight,
                    fprintf(pFile_w, "%f\t", W_t[t][i][j]);
                }
            }}
            fprintf(pFile_w, "\n"); //new timestep
        }
        //Append to file for rates
        for (t=0; t<n; t++){ 
            for (i=0;i<no;i++){
                fprintf(pFile_r, "%f\t", Re[t][i]);
            }
            fprintf(pFile_r, "\n");
        }
    }
*/

    }

    fclose(pFile_w);
    fclose(pFile_r);

    printf("Done!\n");

    return 0;

}

