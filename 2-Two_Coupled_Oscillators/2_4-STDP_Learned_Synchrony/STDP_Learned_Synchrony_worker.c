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
#include "../../utils/multithreads/multithreads.h"
#include "../../utils/neuro/pingRateN/pingRateN.h"
#include "../../utils/neuro/get_last_period/get_last_period.h"
#include "../../utils/sig_proc/phdiff2.h"

void
*Learned_Synchrony_worker(void *arg)
{
    //Cast input args to data structure
    THREAD_DAT_1D * in = arg;
    printf("Starting thread %d...\n", in->id);

    //Simulation duration params
    int n=9999, no=2;
    double dt=0.0001;
    int i,j; //counters
    int res = in->res; //resolution

    //Within-oscillator syn strengths
    double wW[2][2];
        wW[0][0]=2;         wW[0][1]=2.873; //EE    EI
        wW[1][0]=-2.873;    wW[1][1]=-2;    //IE    II

    //X-oscillator synaptic strengths
    double ei=0.3, ie=-0.5, ii=0; 
    double ee=in->DATA_IN[0];

    //Find rates for one period
    int p=1000;
    double lp_rates[p][2];
    get_last_period(&p, lp_rates, wW);

    //Initialize Arrays
    double Re[n][no];
    double R_i[no][2];
    double pds[no][no];

    //Multiple trials
    int numtrials = 300;
    double thesum;


    /********* LOOP THROUGH INIT PHDIFFS ASSIGNED TO THIS THREAD***********/
    for (i=in->a; i<in->b; i++){
        //find init rates for this init phasediff
        R_i[0][0] = lp_rates[0][0];
        R_i[0][1] = lp_rates[0][1];
        R_i[1][0] = lp_rates[i*p/res][0];
        R_i[1][1] = lp_rates[i*p/res][1];

        thesum = 0;

        //find avg phdiff over some trials
        for (j=0; j<numtrials; j++){
            
            //Simulate
            pingRateN(n,no,Re,R_i,ee,ei,ie,ii,wW,dt);

            //Find steady state phase diff
            phdiff2(n, no, Re, pds);

            //add this phdiff to sum
            thesum += pds[0][1];

        }

        //Assign SS phase diff to output data array
        in->DATA[i] = thesum/numtrials;

    }


}

