/* Learned_Synchrony.c- shows how 2 oscillators can learn to 
                        oscillate in-phase

    Copyright 2012
    Brendan Hasz
    bhasz@brandeis.edu
    www.cs.brandeis.edu/~bhasz/main.php
    Brandeis University, Waltham, MA, USA

*/

#include <stdio.h>
#include "../../utils/neuro/get_last_period/get_last_period.h"
#include "../../utils/neuro/plasticPingRateN_recW/plasticPingRateN_recW.h"
#include "../../utils/fileIO/fileIO.h"
#include "../../utils/multithreads/multithreads.h"
#include "Learned_Synchrony_worker.h"

int main(void){

    /*********** INITIALIZE STUFF *************/
    int n=10000; //timesteps per plastic trial
    int no=5; //number of oscillators
    int plasticTrials = 10;
    int g=2*no; //number of groups
    double dt = 0.0001;
    int rw = 100;  //how often to record syn weights
    int t,i,j,k,l;  //counters
    double W_t[n/rw][g][g]; //Weight matrix over time
    double Re[n][no], R_i[no][2]; //Excitatory rate vector and initial rate vec

    //Init weights
    double wW[2][2];    //Within-oscillator synaptic weights
        wW[0][0]=2;         wW[0][1]=2.873; //EE    EI
        wW[1][0]=-2.873;    wW[1][1]=-2;    //IE    II
    double W[4];    //Cross-group
        W[0]=0.2;   W[1]=0.3;   //xEE   xEI
        W[2]=-0.5;  W[3]=0;     //xIE   xII
    int xEE_c=1, xEI_c=0, xIE_c=0, xII_c=0; //Syn weights allowed to change?


    //Find initial rate vector
    int p=1000;
    double lp_rates[p][2];
    get_last_period(&p, lp_rates, wW);

    //Init rates for A1 and A2
    double R_i_A1[no][2], R_i_A2[no][2];
    for (i=0; i<3; i++){ //In-group start at peak
        R_i_A1[i][0] = lp_rates[0][0];
        R_i_A1[i][1] = lp_rates[0][1];
        R_i_A2[i+2][0] = lp_rates[0][0];
        R_i_A2[i+2][1] = lp_rates[0][1];
    }
    for (i=0; i<2; i++){ //Out-group start at trough
        R_i_A1[i+3][0] = lp_rates[p/2][0];
        R_i_A1[i+3][1] = lp_rates[p/2][1];
        R_i_A2[i][0] = lp_rates[p/2][0];
        R_i_A2[i][1] = lp_rates[p/2][1];
    }


    //Multithreading stuff
    int pd_res = 100;
    double phdiffs[pd_res];
    pthread_t threads[NUM_THREADS];
    THREAD_DAT_1D t_args[NUM_THREADS];
    int t_divs[NUM_THREADS+1];
    segment_threads(NUM_THREADS, 0, pd_res, t_divs);
    
    //put data in thread args
    for (i=0;i<NUM_THREADS;i++){
        t_args[i].id = i;
        t_args[i].a = t_divs[i];
        t_args[i].b = t_divs[i+1];
        t_args[i].res = pd_res;
        t_args[i].DATA = (double *)&phdiffs;
        t_args[i].DATA_IN = (double *)&W;
    }


    /*********** BEFORE PLASTICITY PD_INIT VS PD_SS PLOT  *************/
    //Run threads
    for (i=0;i<NUM_THREADS;i++){
        pthread_create(&threads[i],NULL,Learned_group_synchrony_worker,(void*)&t_args[i]);
    }

    //Wait for threads to finish
    waitfor_threads(NUM_THREADS, threads);

    //Write data to file
    char * fn_pre = "Learned_group_synchrony_PREplas.dat";
    vsave(pd_res, phdiffs, fn_pre);
    printf("Done with PRE-PLASTICITY - data saved as %s\n", fn_pre);



    /*********** DO ALTERNATING A1 / A2 PLASTIC RUNS ******************/
    //Create new file to store weights
    char * fn_plas_w = "Learned_group_synchrony_plas_w.dat";
    FILE * pFile_wn = fopen(fn_plas_w,"w"); fprintf(pFile_wn, "\n"); fclose(pFile_wn);
    FILE * pFile_w = fopen(fn_plas_w,"a"); //now open it for appending

    //Create new file to store weights
    char * fn_plas_r = "Learned_group_synchrony_plas_r.dat";
    FILE * pFile_rn = fopen(fn_plas_r,"w"); fprintf(pFile_rn, "\n"); fclose(pFile_rn);
    FILE * pFile_r = fopen(fn_plas_r,"a"); //now open it for appending

    //Simulate
    for (l=0; l<plasticTrials; l++){ //alternate A1, A2
        //ASSEMBLY 1
        plasticPingRateN_recW(n,no,Re,R_i_A1,W[0],W[1],W[2],W[3],
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


        //ASSEMBLY 2
        plasticPingRateN_recW(n,no,Re,R_i_A1,W[0],W[1],W[2],W[3],
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

    fclose(pFile_w);
    fclose(pFile_r);



    /*********** AFTER IN-PLASTICITY PD_INIT VS PD_SS PLOT  *************/
    //Run threads
    for (i=0;i<NUM_THREADS;i++){
        pthread_create(&threads[i],NULL,Learned_group_synchrony_worker,(void*)&t_args[i]);
    }

    //Wait for threads to finish
    waitfor_threads(NUM_THREADS, threads);

    //Write data to file
    char * fn_post = "Learned_group_synchrony_POSTplas.dat";
    vsave(pd_res, phdiffs, fn_post);
    printf("Done with POST-PLASTICITY - data saved as %s\n", fn_post);



    return 0;

}

