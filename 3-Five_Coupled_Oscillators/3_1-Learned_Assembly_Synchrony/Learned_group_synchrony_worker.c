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
    int O3A;


    /********* LOOP THROUGH INIT PHDIFFS ASSIGNED TO THIS THREAD***********/
    for (i=in->a; i<in->b; i++){
        printf("T%d: %f percent done\n", in->id, 100*(((double)i-in->a)/((double)in->b-in->a)));
        //find init rates for this init phasediff
        //Assembly 1
        R_i[0][0] = lp_rates[0][0];
        R_i[0][1] = lp_rates[0][1];
        R_i[1][0] = lp_rates[0][0];
        R_i[1][1] = lp_rates[0][1];
        //Assembly 2
        R_i[3][0] = lp_rates[i*p/res][0];
        R_i[3][1] = lp_rates[i*p/res][1];
        R_i[4][0] = R_i[3][0];
        R_i[4][1] = R_i[3][1];

        thesum = 0;

        //find avg phdiff over some trials
        for (j=0; j<numtrials; j++){

            //Osc3 is in both A1 and A2?
            O3A = (gen_rand()>0.5 ? 0 : 1);
            if (O3A>0){ //Randomly assign O3 to A1,
                R_i[2][0] = R_i[0][0];
                R_i[2][1] = R_i[0][1];
            } else { //or A2
                R_i[2][0] = R_i[3][0];
                R_i[2][1] = R_i[3][1];
            }
            
            //Simulate
            pingRateN(n,no,Re,R_i,ee,ei,ie,ii,wW,dt);

            //Find steady state phase diff
            phdiff2(n, no, Re, pds);
            //printf("init phdiff index: %d\n",i);
            //printpds(no, pds);

            //add this phdiff to sum
            for (k=0;k<no;k++){ for (l=k;l<no;l++){
                if (O3A>0){ //O3 is in A1
                    if ((k==0 | k==1 | k==2) && (l==3 | l==4)){
                        thesum += pds[k][l]; //phdiffs between A1 and A2
                    }
                } else { //O3 is in A2
                    if ((l==2 | l==3 | l==4) && (k==0 | k==1)){
                        thesum += pds[k][l]; //phdiffs between A1 and A2
                    }
                }
            }}
        }

        //Assign SS phase diff to output data array
        in->DATA[i] = thesum/numtrials/6; //avg trials and Assembly sums

    }


}

