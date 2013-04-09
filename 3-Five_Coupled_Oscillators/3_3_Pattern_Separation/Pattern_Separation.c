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
#include "Pattern_Completion.h"
#include "Pattern_Completion_worker.h"

int main(void){

    int i, j, k;
    int numsteps = NUMST;
    int numtr = NUMTR;
    int percres = PERCRES;

    //Multithreading
    double perccorr[NUMTR][NUMST]; //Percent correct over time and over trials
        double perccorr_vec[NUMTR*NUMST];
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
    }
        


    //********************* SIMULATE TRIALS!!! ********************

    //run threads
    for (i=0; i<NUM_THREADS; i++){
        pthread_create(&threads[i], NULL, Pattern_Completion_worker, (void*)&t_args[i]);
    }
    waitfor_threads(NUM_THREADS, threads);


    //store passed vector in 2d arrays
    for (i=0;i<NUMTR; i++){
        for (j=0; j<NUMST; j++){
            perccorr[i][j] = perccorr_vec[i*NUMST+j];
        }
    }

    //SAVE DATA 
    //Save average perccorr
    double p_sum;
    char * perccorr_avg_fname = "perccorr_avg.dat";
    double perccorr_averaged[numsteps];
    for (i=0; i<NUMST; i++){
        p_sum = 0;
        for (j=0; j<NUMTR; j++){
            p_sum += perccorr[j][i];
        }
        perccorr_averaged[i] = p_sum/NUMTR;
    }
    vsave(NUMST, perccorr_averaged, perccorr_avg_fname); //Save vector

    //Save stderr of perccorr
    char * perccorr_stderr_fname = "perccorr_stderr.dat";
    double stderr_out[NUMST];
    stderrvec(NUMTR, NUMST, perccorr, stderr_out);
    vsave(NUMST, stderr_out, perccorr_stderr_fname); //Save vector
    
    



    return 0;

}

