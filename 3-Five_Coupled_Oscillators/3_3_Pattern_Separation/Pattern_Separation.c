/*
    STDP_Learned_Synchrony.c

*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

//#include "../../utils/neuro/get_last_period/get_last_period.h"
//#include "../../utils/fileIO/fileIO.h"
//#include "../../utils/basic_math/basic_math.h"
//#include "../../utils/neuro/rateN/rateN.h"
//#include "../../utils/neuro/rateSTDP/rateSTDP.h"
//#include "../../utils/sig_proc/phdiff2.h"

#include "../../utils/multithreads/multithreads.h"
#include "Pattern_Separation.h"
#include "Pattern_Separation_worker.h"

int main(void){

    int i, j, k;
    int numsteps = NUMST;
    int numtr = NUMTR;
    int percres = PERCRES;

    //Multithreading
    double perccorr[NUMTR][NUMST]; //Percent correct over time and over trials
        double perccorr_vec[NUMTR*NUMST];
    double perccorr2[NUMTR][NUMST]; //Percent correct over time and over trials
        double perccorr_vec2[NUMTR*NUMST];
    THREAD_3_2_DAT t_args[NUM_THREADS];
    pthread_t threads[NUM_THREADS];
    int t_divs[NUM_THREADS+1];
    segment_threads(NUM_THREADS, 0, NUMTR, t_divs);
    for (i=0; i<NUM_THREADS; i++){
        t_args[i].id = i;           //Thread ID
        t_args[i].a = t_divs[i];    //Start trial #
        t_args[i].b = t_divs[i+1];  //End trial #
        t_args[i].numtr = NUMTR;
        t_args[i].numsteps = NUMST;
        t_args[i].percres = PERCRES;
        t_args[i].perccorr = (double *)&perccorr_vec;
        t_args[i].perccorr2 = (double *)&perccorr_vec2;
    }
        


    //********************* SIMULATE TRIALS!!! ********************

    //run threads
    for (i=0; i<NUM_THREADS; i++){
        pthread_create(&threads[i], NULL, Pattern_Separation_worker, (void*)&t_args[i]);
    }
    waitfor_threads(NUM_THREADS, threads);


    //store passed vector in 2d arrays
    for (i=0;i<NUMTR; i++){
        for (j=0; j<NUMST; j++){
            perccorr[i][j] = perccorr_vec[i*NUMST+j];
            perccorr2[i][j] = perccorr_vec2[i*NUMST+j];
        }
    }
    

    //SAVE DATA

    //save percorr
    asave(NUMTR, NUMST, perccorr, "perccorr_all.dat");

    //save percorr
    asave(NUMTR, NUMST, perccorr2, "perccorr2_all.dat");
    

    return 0;

}

