/*
	rateNtester - Tests the rateN rate model simulator function

	Tests the rateN function by having it simulate a simple PING oscillator

	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

*/

#include <stdio.h>
#include "plasticRateN_recW.h"
#include "../rateN/rateN.h"
#include "../../fileIO/fileIO.h"

int main(void)
{

    int i,j,t;

    int g = 4;          //Number of groups
    int n = 999;       //Timesteps
    double dt=0.0001;   //Duration of timestep
    
    double R[n][g];     //Rate vectors
    
    double R_i[g];      //Initial rates - initially in-phase
	R_i[0] = 30; //Excitatory
	R_i[1] = 20; //Inhibitory
	R_i[2] = 30.1; //Excitatory
	R_i[3] = 20.1; //Inhibitory

    double W_t[n/100][g][g];
    
    int W_c[g][g];
        for (i=0; i<g; i++){ for (j=0; j<g; j++){ W_c[i][j]=0; }}
        W_c[0][2]=1;    W_c[2][0]=1;  //Only allow xEE weights to change
        
    double W[g][g];     //Synaptic weights - in-phase steady state
        double wee=2, wei=2.873, wie=-2.873, wii=-2;
        double xee=0.1, xei=0, xie=0, xii=0; //SS in-phase
        //double xee=0, xei=0.3, xie=0.3, xii=0; //SS out-of-phase
	W[0][0]=wee;    W[0][1]=wei;    W[0][2]=xee;    W[0][3]=xei;
	W[1][0]=wie;    W[1][1]=wii;    W[1][2]=xie;    W[1][3]=xii;
        W[2][0]=xee;    W[2][1]=xei;    W[2][2]=wee;    W[2][3]=wei;
        W[3][0]=xie;    W[3][1]=xii;    W[3][2]=wie;    W[3][3]=wii; 
       
    double t_w = 0.5; //time constant for syn weight change (secs) 

    double th[g][g];
        for (i=0; i<g; i++){ for (j=0; j<g; j++){ th[i][j]=0; }}
        th[0][2]=10;    th[2][0]=10;  //Thresh for depression is avg E rate

    double t_th = 0.1;  //time constant for sliding threshold
 
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
	
/*    
    //Simulate
    plasticRateN_recW(g, n, R, R_i, W_t, W_c, W, t_w, th, t_th, gamma, tau, dt); //Simulate

    //Save data
    char * filename = "plasticRateN_recW_tester_rate.dat";
    asave(n, g, R, filename);
	
    char * filename_w = "plasticRateN_recW_tester_w.dat";
    double output_w[n/100][g*g];
    for (t=0; t<n/100; t++){ for (i=0; i<g; i++){ for (j=0; j<g; j++){
        output_w[t][g*i+j] = W_t[t][i][j];
    }}}
    asave(n/100, g*g, output_w, filename_w);
    printf("Done!  Data saved as %s\n", filename);
   */
 
    //Simulate without plasticity
    rateN(g, n, R, R_i, W, gamma, tau, dt);

    //Save data
    char * filename_n = "plasticRateN_recW_tester_np.dat";
    asave(n, g, R, filename_n);

    return 0;

}
