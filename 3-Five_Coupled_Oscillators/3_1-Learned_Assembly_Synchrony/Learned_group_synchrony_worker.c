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
    int n=50000;
    int no=5;
    double dt=0.0001;
    int i,j,k,l; //counters
    int res = in->res; //resolution

    //Within-oscillator syn strengths
    double wW[2][2];
        wW[0][0]=2;         wW[0][1]=2.873; //EE    EI
        wW[1][0]=-2.873;    wW[1][1]=-2;    //IE    II

    //X-oscillator synaptic strengths
    double scl = 2/no;
    double ei=0.3*scl, ie=-0.5*scl, ii=0*scl; 
    double ee=in->DATA_IN[0]*scl;

    //Find rates for one period
    int p=1000;
    double lp_rates[p][2];
    get_last_period(&p, lp_rates, wW);

    //Initialize Arrays
    double Re[n][no];
    double R_i[no][2];
    double pds[no][no];

    //Multiple trials
    int numtrials = 30;
    double thesum;
    int rp3, rp4, rp5;


    /********* LOOP THROUGH INIT PHDIFFS ASSIGNED TO THIS THREAD***********/
    for (i=in->a; i<in->b; i++){
        printf("T%d: %f percent done\n", in->id, 100*(((double)i-in->a)/((double)in->b-in->a)));
        //find init rates for this init phasediff
        //O1, O2 in-phase
        R_i[0][0] = lp_rates[0][0];
        R_i[0][1] = lp_rates[0][1];
        R_i[1][0] = lp_rates[0][0];
        R_i[1][1] = lp_rates[0][1];
        //rest @ random phases
        rp3 = rand() % p;
        rp4 = rand() % p;
        rp5 = rand() % p;
        R_i[2][0] = lp_rates[rp3][0];
        R_i[2][1] = lp_rates[rp3][1];
        R_i[3][0] = lp_rates[rp4][0];
        R_i[3][1] = lp_rates[rp4][1];
        R_i[4][0] = lp_rates[rp5][0];
        R_i[4][1] = lp_rates[rp5][1];

            
        //Simulate
        pingRateN(n,no,Re,R_i,ee,ei,ie,ii,wW,dt);

        //Find steady state phase diffs
        phdiff2(n, no, Re, pds);
        //printf("init phdiff index: %d\n",i);
        //printpds(no, pds);

        //Assign SS phase diff to output data array
        in->DATA[i] = pds[0][1]; //phdiff between o1 and o2
        in->DATA[i+1] = pds[0][2]; //phdiff between o1 and o3
        in->DATA[i+2] = pds[0][3]; //phdiff between o1 and o4
        in->DATA[i+3] = pds[0][4]; //phdiff between o1 and o5

    }


}

