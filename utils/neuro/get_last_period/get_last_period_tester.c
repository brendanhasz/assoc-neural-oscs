/*
	get_last_period_tester - tests the function get_last_period

	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

*/

#include <stdio.h>
#include "../rateN/rateN.h"
#include "get_last_period.h"
#include "../../fileIO/fileIO.h"

int main(void)
{

	int g = 2;          //Number of groups
	int n = 9999;       //Timesteps
	double dt=0.0001;   //Duration of timestep
    
	double R[n][g];     //Rate vectors
    
	double R_i[g];      //Initial rates
		R_i[0] = 30; //Excitatory
		R_i[1] = 20; //Inhibitory
        
	double W[g][g];     //Synaptic weights
		W[0][0]=2;		W[0][1]=2.873;	//EE	EI
		W[1][0]=-2.873;	W[1][1]=-2;		//IE	II
        
	double gamma[g];    //External input
		gamma[0] = 10;      //->E cells
		gamma[1] = -10;     //->I cells
        
	double tau[g];      //Time constants
		tau[0] = 0.002; //AMPA (excitatory)
		tau[1] = 0.010;	//GABA_A (inhibitory)
	
    
    //Simulate
	rateN(g, n, R, R_i, W, gamma, tau, dt);
	
	//Get last period
	int p, lp_max=400;
	double lp_rates[lp_max][2];
	get_last_period(&p, lp_rates, W);
	
    //Save data
	char * filename = "get_last_period_tester.dat";
	asave(p, 2, lp_rates, filename);
	
	printf("Done!  Data saved as %s\n", filename);

	return 0;

}
