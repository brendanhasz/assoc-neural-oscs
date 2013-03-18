/*
	rateN - Simulates a system of coupled neurons using simple rate models
    
	rateN(g, n, R[g][n], R_i[g], W[g][g], gamma[g], tau[g], dt)

	Simulates a system of coupled groups of neurons using the simple rate
    model described in Ch. 7.5 of "Theoretical Neuroscience", by Peter Dayan
    and L. F. Abbott.

	INPUTS
	int g			Number of groups to simulate
	int n			Number of timesteps to simulate
	double R[g][n]	Rate vectors of each group over time
	double R_i[g]	Initial rates for each group
	double W[g][g]	Synaptic weight matrix between groups (W[i][j]: i->j)
	double gamma[g]	Constant input to each group
	double tau[g]	Time constant of each group
	double dt		Timestep duration
	
	
	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0 Unported 
	License.  You can use it and modify it any way you like as long as you 
	aren't making money off it - if you are, I want some too!

*/

#include <stdio.h>

#ifndef MAX
#define MAX(x,y) (x > y ? x : y)
#endif

void rateN(int g, int n, double R[n][g], double R_i[], double W[g][g], double gamma[], double tau[], double dt)
{
    
	//Variables
	int t,i,j,l;  //counters
	double s; //sum of weights

	//Initial rates
	for (i=0; i<g; i++){
		R[0][i] = R_i[i];
	}
	
	//Simulate
	for (t=1; t<=n; t++){  //for each timestep,
		l = t-1; //find last timestep
		for (i=0; i<g; i++){ //update each rate model
			s = 0;  //Reset sum
			for (j=0; j<g; j++){ //sum synaptic inputs
				s += W[j][i]*R[l][j];
			}
			R[t][i]=R[l][i]+dt/tau[i]*(-R[l][i]+MAX(0,s+gamma[i])); //integrate
		}
	}
}


void
assignPingW(int no, double W[2*no][2*no], 
            int wee, int wei, int wie, int wii,
            int xee, int xei, int xie, int xii)
{
    int i,j,g=2*no;
    double wW[2][2];  //Within-oscillator weights
        wW[0][0]=wee;   wW[0][1]=wei;   //EE    EI
        wW[1][0]=wie;   wW[1][1]=wii;   //EE    EI
    double xW[2][2];  //Cross-oscillator weights
        xW[0][0]=xee;   xW[0][1]=xei;   //EE    EI
        xW[1][0]=xie;   xW[1][1]=xii;   //EE    EI

    for (i=0; i<g; i++){
        for (j=0; j<g; j++){
            if ( i/2 == j/2 ){
                W[i][j] = wW[i%2][j%2];
            } else {
                W[i][j] = xW[i%2][j%2];
            }
        }
    }
}

