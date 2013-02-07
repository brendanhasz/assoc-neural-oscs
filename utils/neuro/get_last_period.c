/*
	get_last_period - returns the E and I rate vectors of last period
    
    get_last_period(int *p, rates[][2], wW[4])

    Fills rates[] with rates of 2 groups of cells (E+I) over the last
    oscillation of a 1-second time window.
    
	INPUTS
	n		Timesteps to simulate
	rates   n-by-2 array to fill with 2 rate vectors [0]=E, [1]=I
    wW      Within-group connection strength for this PING oscillator

	OUTPUTS
	n		changes to be the length of the period (in 100s of us)
	rates	fills with rate vectors


	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0 Unported 
	License.  You can use it and modify it any way you like as long as you 
	aren't commercially making money off it - if you are, I want some too!

*/

#include "rateN.h"
#include "../sig_proc/l2peaks.h"

void
get_last_period(int *p, double rates[][2], double wW[2][2])
{
    //Initialize values
    int g=2, i, n=9999;
	double dt=0.0001;   //Duration of timestep
    double R[n][g];
    double R_i[g];
        R_i[0] = 30; //Excitatory
        R_i[1] = 20; //Inhibitory
    double gamma[g];
        gamma[0] = 10;
        gamma[1] = -10;
    double tau[g];
        tau[0] = 0.002; //AMPA
        tau[1] = 0.010;	//GABA_A
        
    rateN(g, n, R, R_i, wW, gamma, tau, dt); //Simulate

    //Copy excitatory vector into its own vector
    double Re[n];
    for (i=0; i<n; i++) { Re[i] = R[i][0];}

    //Get last 2 peak indexes
    int tl2p[2];
    l2peaks(n, Re, tl2p);
    
    //Determine period length in timesteps
    *p = tl2p[1] - tl2p[0];
    
    //Write rates between last 2 peaks into rates
    for (i=0; i<*p; i++){
        rates[i][0] = R[tl2p[0]+i][0];
        rates[i][1] = R[tl2p[0]+i][1];
    }

}
