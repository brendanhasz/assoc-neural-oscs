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
#include "../../utils/neuro/pingRateN/pingRateN.h"
#include "../../utils/fileIO/fileIO.h"
#include "../../utils/multithreads/multithreads.h"
#include "Learned_Synchrony_worker.h"

int main(void){

    /*********** INITIALIZE STUFF *************/
    //Init weights
    double W[4];
        W[0] = 0.2;

    //Multithreading stuff
    int pd_res = 100;
    int i,j;
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
        pthread_create(&threads[i],NULL,Learned_Synchrony_worker,(void*)&t_args[i]);
    }

    //Wait for threads to finish
    waitfor_threads(NUM_THREADS, threads);

    //Write data to file
    char * fn_pre_pdvpd = "Learned_Synchrony_pre_pdvpd.dat";
    vsave(pd_res, phdiffs, fn_pre_pdvpd);
    printf("Done with PRE - data saved as %s\n", fn_pre_pdvpd);


    /*********** DO PLASTIC RUN ******************/


 


    /*********** AFTER PLASTICITY PD_INIT VS PD_SS PLOT  *************/




    return 0;

}
