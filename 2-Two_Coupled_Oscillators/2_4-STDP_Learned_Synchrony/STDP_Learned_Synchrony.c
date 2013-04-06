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
#include "STDP_Learned_Synchrony.h"
#include "STDP_Learned_Synchrony_worker.h"

int main(void){

    int i, j, k;
    double pd_sum;
    int numsteps = NUMST;
    int numtr = NUMTR;
    int pd_res = PDRES;

    //Multithreading
    //TODO
    double Wxee_tr[NUMTR][2][NUMST]; //xEE Weights over time for each trial
        double Wxee_tr_vec[NUMTR*2*NUMST]; //Vector form for passing to thread
    double pd_tr[NUMTR][PDRES][NUMST]; //SS phase difference over time for each trial
        double pd_tr_vec[NUMTR*PDRES*NUMST];
    THREAD_2_4_DAT t_args[NUM_THREADS];
    pthread_t threads[NUM_THREADS];
    int t_divs[NUM_THREADS+1];
    segment_threads(NUM_THREADS, 0, NUMTR, t_divs);
    for (i=0; i<NUM_THREADS; i++){
        t_args[i].id = i;           //Thread ID
        t_args[i].a = t_divs[i];    //Start trial #
        t_args[i].b = t_divs[i+1];  //End trial #
        t_args[i].numtr = NUMTR;
        t_args[i].numsteps = NUMST;
        t_args[i].pdres = PDRES;
        t_args[i].Wxee_tr = (double *)&Wxee_tr_vec;
        t_args[i].pd_tr = (double *)&pd_tr_vec;
    }
        


    //********************* SIMULATE STARTING IN-PHASE!!! ********************
    //initialize per-thread params to start in-phase
    for (i=0; i<NUM_THREADS; i++){
        t_args[i].initphdiff = 0;
    }

    //run threads
    for (i=0; i<NUM_THREADS; i++){
        pthread_create(&threads[i], NULL, STDP_Learned_Synchrony_worker, (void*)&t_args[i]);
    }
    waitfor_threads(NUM_THREADS, threads);

    //store passed vectors in 3d arrays
    for (i=0;i<NUMTR; i++){
        for (j=0; j<PDRES; j++){
            for (k=0; k<NUMST; k++){
                pd_tr[i][j][k] = pd_tr_vec[i*PDRES*NUMST+j*NUMST+k];
            }
        }
    }
    for (i=0;i<NUMTR; i++){
        for (j=0; j<NUMST; j++){
            Wxee_tr[i][0][j] = Wxee_tr_vec[i*2*NUMST+0*NUMST+j];
            Wxee_tr[i][1][j] = Wxee_tr_vec[i*2*NUMST+1*NUMST+j];
        }
    }

    //SAVE DATA FROM IN-PHASE

    //Save average weights per step (between trials)
    double W_sum1, W_sum2;
    char * Wxee_avg_fname = "Wxee_avg.dat";
    double Wxee_averaged[numsteps][2];
    for (i=0; i<numsteps; i++){
        W_sum1 = 0;
        W_sum2 = 0;
        for (j=0; j<numtr; j++){
            W_sum1 += Wxee_tr[j][0][i];
            W_sum2 += Wxee_tr[j][1][i];
        }
        Wxee_averaged[i][0] = W_sum1/numtr;
        Wxee_averaged[i][1] = W_sum2/numtr;
    }
    asave(numsteps, 2, Wxee_averaged, Wxee_avg_fname); //Save 2d array


    //Save stdev. of weights per step (between trials)
    char * Wxee_stderr_fname = "Wxee_stderr.dat";
    double Wxee_stderr[numsteps][2];
    double stderr_in[numtr][numsteps], stderr_out[numsteps];

    //Find stderr of first Wxee
    for (i=0; i<numtr; i++){  //put 1st wxee in stderr_in
        for (j=0; j<numsteps; j++){
            stderr_in[i][j] = Wxee_tr[i][0][j];
        }
    }
    stderrvec(numtr, numsteps, stderr_in, stderr_out);
    for (j=0; j<numsteps; j++){ //put result in array to save
        Wxee_stderr[j][0] = stderr_out[j];
    }
    
    //Find stderr of second Wxee
    for (i=0; i<numtr; i++){  //put 2nd wxee in stderr_in
        for (j=0; j<numsteps; j++){
            stderr_in[i][j] = Wxee_tr[i][1][j];
        }
    }
    stderrvec(numtr, numsteps, stderr_in, stderr_out);
    for (j=0; j<numsteps; j++){ //put result in array to save
        Wxee_stderr[j][1] = stderr_out[j];
    }

    asave(numsteps, 2, Wxee_stderr, Wxee_stderr_fname); //Save 2d array


    //Save average phdiff (as a 2d array)
    char * phdiff_avg_fname = "phdiff_avg.dat";
    double pd_averaged[pd_res][numsteps];
    for (i=0; i<pd_res; i++){
        for (j=0; j<numsteps; j++){
            pd_sum = 0;
            for (k=0; k<numtr; k++){
                pd_sum += pd_tr[k][i][j];
            }
            pd_averaged[i][j] = pd_sum/numtr;
        }
    }
    asave(pd_res, numsteps, pd_averaged, phdiff_avg_fname); //Save 2d array



    //********************* SIMULATE STARTING OUT-OF-PHASE!!! ********************
    //TODO




    return 0;

}

