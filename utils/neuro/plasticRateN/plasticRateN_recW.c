/*
    plasticRateN - Simulates a system of coupled groups of neurons
        using simple rate models, and allows the initial synaptic
        weights to change over time according to synaptic plasticity
        rules.
    
    plasticRateN_recW(g, n, R[g][n], R_i[g], W[g][g], gamma[g], tau[g], dt)

    Simulates a system of coupled groups of neurons using the simple rate
    model described in Ch. 7.5 of "Theoretical Neuroscience", by Peter Dayan
    and L. F. Abbott.  Allows the initial synaptic weights to change over
    time according to the BCM Rule (Bienenstock, Cooper, Munro, 1982).

    INPUTS
    int g            Number of groups to simulate
    int n            Number of timesteps to simulate
    double R[g][n]   Rate vectors of each group over time
    double R_i[g]    Initial rates for each group
    double W[n/100][g][g]  Weight vectors of each synapse over time
    int W_c[g][g]    Do the weights change over time? 0 (no) or nonzero (y)
    double W_i[g][g] Initial synaptic weights between groups (W[i][j]: i->j)
    double tau_w[g][g]      Time constants for syn. weight change
    double theta_i[g][g]    Inital sliding thresh values
    double tau_theta[g][g]  Sliding thesh time constants
    double gamma[g]  Constant input to each group
    double tau[g]    Time constant of each group
    double dt        Timestep duration
	
	
    Copyright 2012
    Brendan Hasz
    bhasz@brandeis.edu
    www.cs.brandeis.edu/~bhasz/main.php
    Brandeis University, Waltham, MA, USA

*/

#ifndef MAX
#define MAX(x,y) (x > y ? x : y)
#endif

void
plasticRateN_recW(int g, int n, double R[n][g], double R_i[], 
    double W_t[n/100][g][g], int W_c[g][g], double W[g][g], 
    double tau_w, double theta[g][g], double tau_theta,
    double gamma[], double tau[], double dt)
{

    //Variables
    int t,i,j,l;  //counters
    double s; //sum of weights
    int uw=10; //update syn weights each uw timesteps
    int rw=100; //record syn weights each rw timesteps

    //Initial rates
    for (i=0; i<g; i++){
	R[0][i] = R_i[i];
    }
	
    //Simulate
    for (t=1; t<n; t++){  //for each timestep,
	l = t-1; //find last timestep
	for (i=0; i<g; i++){ //update each rate model
	    s = 0;  //Reset sum
	    for (j=0; j<g; j++){ //sum synaptic inputs
	        s += W[j][i]*R[l][j];
	    }
	    R[t][i]=R[l][i]+dt/tau[i]*(-R[l][i]+MAX(0,s+gamma[i])); //integrate
	}
        if (t%uw==0){ //every once in a while, update weights
            //REMEMBER, must multiply time constant by 10 then
            for (i=0; i<g; i++){
                for (j=0; j<g; j++){
                    if (W_c[i][j]>0){ //only update if this syn is updatable
                    W[i][j]=W[i][j]+uw*dt/tau_w*(R[t][j]*R[t][i]*(R[t][j]-theta[i][j]));
                    theta[i][j]=uw*dt/tau_theta*(R[t][j]*R[t][j]-theta[i][j]);
                    }
                }
            }
        }
        if (t%rw==0){ //every once and a while, record weights
            for (i=0; i<g; i++){
                for (j=0; j<g; j++){
                    W_t[t/rw][i][j] = W[i][j];
                }
            }
        }
    }

}
