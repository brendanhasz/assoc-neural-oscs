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
    double G1_perccorr[NUMTR][NUMST]; //Percent correct over time and over trials
        double G1_perccorr_vec[NUMTR*NUMST];
    double G2_perccorr[NUMTR][NUMST]; //Percent correct over time and over trials
        double G2_perccorr_vec[NUMTR*NUMST];
    THREAD_3_3_DAT t_args[NUM_THREADS];
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
        t_args[i].G1_perccorr = (double *)&G1_perccorr_vec;
        t_args[i].G2_perccorr = (double *)&G2_perccorr_vec;
    }
        


    //********************* SIMULATE TRIALS!!! ********************

    //run threads
    for (i=0; i<NUM_THREADS; i++){
        pthread_create(&threads[i], NULL, Pattern_Separation_worker, (void*)&t_args[i]);
    }
    waitfor_threads(NUM_THREADS, threads);


    //store passed vectors in 2d arrays
    for (i=0;i<NUMTR; i++){
        for (j=0; j<NUMST; j++){
            G1_perccorr[i][j] = G1_perccorr_vec[i*NUMST+j];
            G2_perccorr[i][j] = G2_perccorr_vec[i*NUMST+j];
        }
    }

    //SAVE DATA 
    //Save avg percorr for g1
    //Save average perccorr
    double p_sum1, p_sum2;
    char * G1_perccorr_avg_fname = "G1_perccorr_avg.dat";
    char * G2_perccorr_avg_fname = "G2_perccorr_avg.dat";
    double G1_perccorr_averaged[numsteps], G2_perccorr_averaged[numsteps];
    for (i=0; i<NUMST; i++){
        p_sum1 = 0;
        p_sum2 = 0;
        for (j=0; j<NUMTR; j++){
            p_sum1 += G1_perccorr[j][i];
            p_sum2 += G2_perccorr[j][i];
        }
        G1_perccorr_averaged[i] = p_sum1/NUMTR;
        G2_perccorr_averaged[i] = p_sum2/NUMTR;
    }
    vsave(NUMST, G1_perccorr_averaged, G1_perccorr_avg_fname); //Save vector
    vsave(NUMST, G2_perccorr_averaged, G2_perccorr_avg_fname); //Save vector

    //Save stderr of perccorr
    char * G1_perccorr_stderr_fname = "G1_perccorr_stderr.dat";
    char * G2_perccorr_stderr_fname = "G2_perccorr_stderr.dat";
    double G1_stderr_out[NUMST], G2_stderr_out[NUMST];
    stderrvec(NUMTR, NUMST, G1_perccorr, G1_stderr_out);
    stderrvec(NUMTR, NUMST, G2_perccorr, G2_stderr_out);
    vsave(NUMST, G1_stderr_out, G1_perccorr_stderr_fname); //Save vector
    vsave(NUMST, G2_stderr_out, G2_perccorr_stderr_fname); //Save vector
    
    

    return 0;

}

