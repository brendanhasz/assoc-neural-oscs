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
    int g=2*no; //number of groups
    double dt = 0.0001;
    int rw = 100;  //how often to record syn weights
    int t,i,j;  //counters
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
    char * fn_pre_pdvpd = "Learned_Synchrony_pre_pdvpd.dat";
    vsave(pd_res, phdiffs, fn_pre_pdvpd);
    printf("Done with PRE - data saved as %s\n", fn_pre_pdvpd);



    /*********** DO ALTERNATING A1 / A2 PLASTIC RUNS ******************/
    //TODO: create new file
    char * fn_plasIN_r = "Learned_Synchrony_plas_IN_r.dat";
    double output_w_in[n/rw][g*g];

    //Simulate
    for (i=0; i<plasticTrials; i++){ //alternate A1, A2
        //ASSEMBLY 1
        plasticPingRateN_recW(n,no,Re,R_i_A1,W[0],W[1],W[2],W[3],
                            xEE_c,xEI_c,xIE_c,xII_c,wW,dt,W_t);    
        W[0] = (W_t[n/rw-1][0][2]+W_t[n/rw-1][0][2])/2; //set new xEE weight for next run
        printf("xEE weight after plastic run %d (A1): %f\n",i,W_t[n/rw-1][0][2]);
        //TODO: append to file

        //ASSEMBLY 2
        plasticPingRateN_recW(n,no,Re,R_i_A1,W[0],W[1],W[2],W[3],
                            xEE_c,xEI_c,xIE_c,xII_c,wW,dt,W_t);    
        W[0] = (W_t[n/rw-1][0][2]+W_t[n/rw-1][0][2])/2; //set new xEE weight for next run
        printf("xEE weight after plastic run %d (A1): %f\n",i,W_t[n/rw-1][0][2]);
        //TODO: append to file
    }



    //Convert weight matrix into storable one
    for (t=0;t<n/rw;t++){ for (i=0;i<g;i++){ for (j=0;j<g;j++){
        output_w_in[t][g*i+j] = W_t[t][i][j];
    }}}

    //And save the final xEE weights for later
    double W_ppIN_SS = W_t[n/rw-1][0][2];

    //Save data
    char * fn_plasIN_w = "Learned_Synchrony_plas_IN_w.dat";
    asave(n/rw, g*g, output_w_in, fn_plasIN_w);
    printf("Plastic run, init-IN, weight data saved as %s\n", fn_plasIN_w);



    /*********** AFTER IN-PLASTICITY PD_INIT VS PD_SS PLOT  *************/
    //Set xEE weight
    W[0] = W_ppIN_SS;

    //Run threads
    for (i=0;i<NUM_THREADS;i++){
        pthread_create(&threads[i],NULL,Learned_Synchrony_worker,(void*)&t_args[i]);
    }

    //Wait for threads to finish
    waitfor_threads(NUM_THREADS, threads);

    //Write data to file
    char * fn_postIN_pdvpd = "Learned_Synchrony_postIN_pdvpd.dat";
    vsave(pd_res, phdiffs, fn_postIN_pdvpd);
    printf("Done with POST-IN - data saved as %s\n", fn_postIN_pdvpd);



    return 0;

}

