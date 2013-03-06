/*
	pingRateN - Simulates a system of coupled neural PING oscillators

	Simulates coupled PING oscillators - you specify the cross-group
	connectivity and initial rates for each group. Uses the simple rate
    model described in Ch. 7.5 of "Theoretical Neuroscience", by
    Peter Dayan and L. F. Abbott.

	INPUTS
	int n				Number of timesteps to simulate
	int no				Number of oscillators
	double Re[n][no]	Rate vectors to return Excit. group rates in
	double R_i[no][2]	Initial rates for groups
	double xEE			Cross-oscillator E->E syn strength
	double xEI			Cross-oscillator E->E syn strength
	double xIE			Cross-oscillator E->E syn strength
	double xII			Cross-oscillator E->E syn strength
	double wW[2][2]		Within-oscillator strength {{EE, EI},{IE, II}}
	double dt			Timestep duration in seconds


	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0
	Unported License.  You can use it and modify it any way you like as
	long as you aren't commercially making money off it - if you are,
	I want some too!

*/

#include <math.h>
#include <stdlib.h>
#include "../plasticRateN_recW/plasticRateN_recW.h"
#include "../../basic_math/basic_math.h"

// gen_rand - Generate a random number (double) from 0 to 1
#ifndef rrand
#define rrand() ( rand() / (1.0 + RAND_MAX) )
#endif


void
plasticPingRateN_recW(int n, int no, double Re[n][no], double R_i[no][2],
    double xEE, double xEI, double xIE, double xII,
    int xEE_c, int xEI_c, int xIE_c, int xII_c,
    double wW[2][2], double dt, double W_t[n/100][2*no][2*no])
{

    int g = 2*no, i, j, k, l; //Num groups, counters
    double t_w = 100000;    //time constant for syn weight change
    double t_th = 1000;     //time constant for sliding threshold

    double R[n][g];     //Rate vectors for each group

    double R_i_s[g];
    for (i=0; i<g; i++){ //set initial rates with a little stochasticity
        R_i_s[i] = max(0,R_i[i/2][i%2]+gen_randn());
    }

    double gamma[g]; //External input
    for (i=0; i<g; i=i+2){
        gamma[i] = 10;      //Excitatory
	gamma[i+1] = -10;   //Inhibitory
    }

    double tau[g]; //Synaptic time constants
    for (i=0; i<g; i=i+2){
        tau[i] = 0.002;     //AMPA (Excitatory) - 2ms
        tau[i+1] = 0.01;    //GABA_A (Inhibitory) - 10ms
    }

    double th[g][g];
        for (i=0; i<g; i++){ for (j=0; j<g; j++){ th[i][j]=0; }}

    double W[g][g];     //Initial synaptic weight
    double W_b[g][g];   //Synaptic weight bounds
        for (i=0; i<g; i++){ for (j=0; j<g; j++){ W_b[i][j]=0; }}
    int W_c[g][g];   //Syn weights allowed to change?
        for (i=0; i<g; i++){ for (j=0; j<g; j++){ W_c[i][j]=0; }}
    for (i=0; i<g; i=i+2){
        for (j=0; j<g; j=j+2){
            if (i==j){	//Within-group weights
                for (k=0;k<2;k++){ for (l=0;l<2;l++){ W[i+k][i+l]=wW[k][l]; }}
            }
            else {  //Cross-group weights
                W_b[i][j] = 0.3;    //SET xEE WEIGHT BOUND
                th[i][j] = 20;      //set thresh for depression for xEE as 20hz
                //Allow synapses to change?
                W_c[i][j] = xEE_c;      //xEE
                W_c[i][j+1] = xEI_c;    //xEI
                W_c[i+1][j] = xIE_c;    //xIE
                W_c[i+1][j+1] = xII_c;  //xII
                //Init syn weights
                W[i][j] = xEE;      //xEE
                W[i][j+1] = xEI;    //xEI
                W[i+1][j] = xIE;    //xIE
                W[i+1][j+1] = xII;  //xII
            }
        }
    }


    //Simulate with plasticity
    plasticRateN_recW(g, n, R, R_i_s, W_t, W_c, W, W_b, t_w, th, t_th, gamma, tau, dt);


    //Copy excitatory rate vectors into output vectors
    for (i=0; i<no; i++){
        for (j=0; j<n; j++){
            Re[j][i] = R[j][2*i];
        }
    }

}
