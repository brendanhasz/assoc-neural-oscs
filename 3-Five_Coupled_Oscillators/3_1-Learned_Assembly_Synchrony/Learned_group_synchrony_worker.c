/* Learned_Synchrony_worker.c

    Thread code for finding phase diffs

    Copyright 2013
    Brendan Hasz
    bhasz@brandeis.edu
    www.cs.brandeis.edu/~bhasz/main.php
    Brandeis University, Waltham, MA, USA

*/

//threads.h
//get_last_period
//pingRateN
//phdiff2

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../../utils/multithreads/multithreads.h"
#include "../../utils/basic_math/basic_math.h"
#include "../../utils/neuro/pingRateN/pingRateN.h"
#include "../../utils/neuro/get_last_period/get_last_period.h"
#include "../../utils/sig_proc/phdiff2.h"

void
*Learned_group_synchrony_worker(void *arg)
{
    //Cast input args to data structure
    THREAD_DAT_1D * in = arg;
    printf("Starting thread %d...\n", in->id);

    //Simulation duration params
    int n=20000;
    int no=5, g=2*no;
    double dt=0.0001;
    int t,i,j,k,l; //counters
    int res = in->res; //resolution

    //Within-oscillator syn strengths
    double wW[2][2];
        wW[0][0]=in->DATA_IN[0];    wW[0][1]=in->DATA_IN[1];    //EE    EI
        wW[1][0]=in->DATA_IN[g];    wW[1][1]=in->DATA_IN[g+1];  //IE    II
    double W[g][g];
        for (i=0;i<g;i++){
            for (j=0;j<g;j++){
                W[i][j] = in->DATA_IN[i*g+j];
            }
        }

    //Tau and gamma for rateN
    double gamma[g], tau[g];
    for (i=0;i<g;i+=2){ //Input
        gamma[i]=10;    //Excitatory
        gamma[i+1]=-10; //Inhibitory
    }
    for (i=0;i<g;i+=2){ //Time constants
        tau[i]=0.002;    //Excitatory
        tau[i+1]=0.01;  //Inhibitory
    }

    //Find rates for one period
    int p=1000;
    double lp_rates[p][2];
    get_last_period(&p, lp_rates, wW);

    //Initialize Arrays
    double Re[n][no];
    double R[n][g];
    double R_i[no][2];
    double pds[no][no];

    //Multiple trials
    int rp3, rp4, rp5;


    /********* LOOP THROUGH INIT PHDIFFS ASSIGNED TO THIS THREAD***********/
    for (i=in->a; i<in->b; i++){
        //print percent done message
        if (i%100==0){
            printf("T%d: %f percent done\n", in->id, 100*(((double)i-in->a)/((double)in->b-in->a)));
        }

        //find init rates for this init phasediff
        //O1, O2 in-phase
        R_i[0][0] = lp_rates[0][0]+gen_rand();
        R_i[0][1] = lp_rates[0][1]+gen_rand();
        R_i[1][0] = lp_rates[0][0]+gen_rand();
        R_i[1][1] = lp_rates[0][1]+gen_rand();
        //rest @ random phases
        rp3 = rand() % p;
        rp4 = rand() % p;
        rp5 = rand() % p;
        R_i[2][0] = lp_rates[rp3][0]+gen_rand();
        R_i[2][1] = lp_rates[rp3][1]+gen_rand();
        R_i[3][0] = lp_rates[rp4][0]+gen_rand();
        R_i[3][1] = lp_rates[rp4][1]+gen_rand();
        R_i[4][0] = lp_rates[rp5][0]+gen_rand();
        R_i[4][1] = lp_rates[rp5][1]+gen_rand();

        //Simulate    
        rateN(g, n, R, R_i, W, gamma, tau, dt);
        for (t=0;t<n;t++){ //Convert R to Re
            for (j=0;j<g;j+=2){
                Re[t][j/2] = R[t][j];
            }
        }

        //Find steady state phase diffs
        phdiff2(n, no, Re, pds);
        //printf("init phdiff index: %d\n",i);
        //printpds(no, pds);

        //Assign SS phase diff to output data array
        in->DATA[i*4] = pds[0][1]; //phdiff between o1 and o2
        in->DATA[i*4+1] = pds[0][2]; //phdiff between o1 and o3
        in->DATA[i*4+2] = pds[0][3]; //phdiff between o1 and o4
        in->DATA[i*4+3] = pds[0][4]; //phdiff between o1 and o5

    }


}

