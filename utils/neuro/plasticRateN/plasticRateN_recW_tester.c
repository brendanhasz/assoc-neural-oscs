/*
	rateNtester - Tests the rateN rate model simulator function

	Tests the rateN function by having it simulate a simple PING oscillator

	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0 Unported
	License.  You can use it and modify it any way you like as long as you
	aren't commercially making money off it - if you are, I want some too!

*/

#include <stdio.h>
#include "rateN.h"
#include "../../fileIO/fileIO.h"

int main(void)
{

    int g = 4;          //Number of groups
    int n = 9999;       //Timesteps
    double dt=0.0001;   //Duration of timestep
    
    double R[n][g];     //Rate vectors
    
    double R_i[g];      //Initial rates - initially in-phase
	R_i[0] = 30; //Excitatory
	R_i[1] = 20.1; //Inhibitory
	R_i[2] = 30.1; //Excitatory
	R_i[3] = 20; //Inhibitory
        
    double W[g][g];     //Synaptic weights - in-phase steady state
        double wee=2, wei=2.873, wie=-2.873, wii=-2;
        double xee=0.1, xei=0, xie=0, xii=0; //SS in-phase
        //double xee=0, xei=0.3, xie=0.3, xii=0; //SS out-of-phase
	W[0][0]=wee;    W[0][1]=wei;    W[0][2]=xee;    W[0][3]=xei;
	W[1][0]=wie;    W[1][1]=wii;    W[1][2]=xie;    W[1][3]=xii;
        W[2][0]=xee;    W[2][1]=xei;    W[2][2]=wee;    W[2][3]=wei;
        W[3][0]=xei;    W[3][1]=xii;    W[3][2]=wei;    W[3][3]=wii; 
        
    double gamma[g];    //External input
	gamma[0] = 10;      //->E cells - G1
	gamma[1] = -10;     //->I cells - G1
	gamma[2] = 10;      //->E cells - G2
	gamma[3] = -10;     //->I cells - G2
        
    double tau[g];      //Time constants
	tau[0] = 0.002; //AMPA (excitatory)  - G1
	tau[1] = 0.010;	//GABA_A (inhibitory)- G1
	tau[2] = 0.002; //AMPA (excitatory)  - G2
	tau[3] = 0.010;	//GABA_A (inhibitory)- G2
	
    
    //Simulate
	rateN(g, n, R, R_i, W, gamma, tau, dt); //Simulate
	
    //Save data
	char * filename = "rateN_tester.dat";
	asave(n, g, R, filename);
	
	printf("Done!  Data saved as %s\n", filename);

	return 0;

}
