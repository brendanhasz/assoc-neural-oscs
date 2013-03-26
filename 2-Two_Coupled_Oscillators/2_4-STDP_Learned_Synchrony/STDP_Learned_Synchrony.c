/*
    STDP_Learned_Synchrony.c

*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "../../utils/neuro/get_last_period/get_last_period.h"
#include "../../utils/fileIO/fileIO.h"
#include "../../utils/basic_math/basic_math.h"
#include "../../utils/neuro/rateN/rateN.h"
#include "../../utils/neuro/rateSTDP/rateSTDP.h"

int main(void){

    //********************** INITIALIZE PARAMS!!! *************************

    // Initialize random seed
    int randseed = time(NULL);
    srand( randseed );
    printf("Seeded with %d\n", randseed);

    // Simulation Params
    int tr, st, i, j, k, l, t;  //counters
    int n = 10000;  //timesteps
    double dt = 1e-4;   //timestep duration
    int no = 2; //number of oscillators
    int g = 2*no;   //number of neuron groups
    double R[n][g]; //Rate vectors
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
    double W_t[n/step][g][g];
    int W_c[g][g];  //Which synapses have plasticity?
        for (i=0; i<g; i++){ for (j=0; j<g; j++){ W_c[i][j]=0; }}
        W_c[0][2]=1;    W_c[2][0]=1;    //Only xee synapses change

    //Get init rates
    double R_i[g];
    int p=1000;
    double rates[p][2];
    get_last_period(&p, rates, wW);

    //Filenames
    //TODO

    //Trial parameters
    int numtr = 10;     //number of trials
    int numsteps = 10;  //number of stdp measurements within each trial
    int pdres = 100;    //resolution of phdiff measurements per step
    double W_tr[numtr][no*(no-1)];
    double pd_tr[numtr][numsteps][pdres];

    //Multithreading
    //TODO




    //************************* SIMULATE!!! ****************************
    //STARTING IN-PHASE
    //TODO: initialize per-thread params to start in-phase
    for (i=0; i<NUM_THREADS; i++){
        pthread_create(&threads[i], NULL, STDP...worker, (void*)&t_args[i]);
    }
    waitfor_threads(NUM_THREADS, threads);

    //for tr = 1: numtrials
        //for st = 1:numsteps
            //simulate for n timesteps using rateN (using updated weights from last step)
            //find weight change using rateSTDP
            //update weights to what u found
            //find phdiff vector w/ these new weights
        //endfor
    //endfor


    //STARTING OUT-OF-PHASE
    //TODO: initialize per-thread params to start out-of-phase 
    for (i=0; i<NUM_THREADS; i++){
        pthread_create(&threads[i], NULL, STDP...worker, (void*)&t_args[i]);
    }
    waitfor_threads(NUM_THREADS, threads);




    return 0;

}

