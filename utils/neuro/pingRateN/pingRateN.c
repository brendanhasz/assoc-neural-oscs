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
#include "../rateN/rateN.h"

// gen_rand - Generate a random number (double) from 0 to 1
#ifndef rrand
#define rrand() ( rand() / (1.0 + RAND_MAX) )
#endif


void
pingRateN(int n, int no, double Re[n][no], double R_i[no][2],
	double xEE, double xEI, double xIE, double xII,
	double wW[2][2], double dt)
{

	int g = 2*no, i, j;	//Num groups, counters
	double R[n][g];		//Rate vectors for each group

	double gamma[g]; //External input
	for (i=0; i<g; i=i+2){
		gamma[i] = 10;		//Excitatory
		gamma[i+1] = -10;	//Inhibitory
	}

	double tau[g]; //Synaptic time constants
	for (i=0; i<g; i=i+2){
		tau[i] = 0.002;		//AMPA (Excitatory) - 2ms
		tau[i+1] = 0.01;	//GABA_A (Inhibitory) - 10ms
	}

	double R_i_s[g];
	for (i=0; i<g; i++){ //set initial rates with a little
		R_i_s[i] = R_i[i/2][i%2]+rrand(); //stochasticity
	}

	double W[g][g];	//Synaptic weights
	for (i=0; i<g; i=i+2){
		for (j=0; j<g; j=j+2){
			if (i==j){	//Within-group weights
				W[i][i] = wW[0][0];		//wEE
				W[i][i+1] = wW[0][1];	//wEI
				W[i+1][i] = wW[1][0];	//wIE
				W[i+1][i+1] = wW[1][1];	//wII
			}
			else {	//Cross-group weights
				W[i][j] = xEE;		//xEE
				W[i][j+1] = xEI;	//xEI
				W[i+1][j] = xIE;	//xIE
				W[i+1][j+1] = xII;	//xII
			}
		}
	}


	//Simulate
	rateN(g, n, R, R_i_s, W, gamma, tau, dt);


	//Copy excitatory rate vectors into output vectors
	for (i=0; i<no; i++){
		for (j=0; j<n; j++){
			Re[j][i] = R[j][2*i];
		}
	}

}
