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

int main(void){

    /*********** INITIALIZE STUFF *************/
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
        
        t_args[i].a = 
    }


    /*********** BEFORE PLASTICITY PD_INIT VS PD_SS PLOT  *************/




    /*********** DO PLASTIC RUN ******************/


 


    /*********** AFTER PLASTICITY PD_INIT VS PD_SS PLOT  *************/




    return 0;

}
