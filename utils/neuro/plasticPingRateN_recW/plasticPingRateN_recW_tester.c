/* pingRateN_tester - tests the pingRateN function
    
	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

*/

#include <stdio.h>
#include "../get_last_period/get_last_period.h"
#include "plasticPingRateN_recW.h"
#include "../../fileIO/fileIO.h"

int main(void){
	
    int n=100000, no=2; //timesteps and number of oscillators
    int g=2*no; //number of groups
    double dt = 0.0001;
    int rw = 10;
    int t,i,j; //counters
    double W_t[n/rw][2*no][2*no]; //Weight matrix over time (filled in by plasticPingRateN)
    double Re[n][no], R_i[no][2];
    double xEE=0.2, xEI=0.3, xIE=-0.5, xII=0;	//init x-group syn weights
    int xEE_c=1, xEI_c=0, xIE_c=0, xII_c=0; //allow synapses to change?
    double wW[2][2];     //within-oscillator synaptic weights
        wW[0][0]=2;         wW[0][1]=2.873; //EE    EI
        wW[1][0]=-2.873;    wW[1][1]=-2;    //IE    II
	
    //Get init rate vector
    int p=400;
    double lp_rates[p][2];
    get_last_period(&p, lp_rates, wW);
	
    double R_i_IN[2][2], R_i_OUT[2][2];
    R_i_IN[0][0]=lp_rates[0][0];
    R_i_IN[0][1]=lp_rates[0][1];
    R_i_IN[1][0]=lp_rates[0][0];
    R_i_IN[1][1]=lp_rates[0][1];

    R_i_OUT[0][0]=lp_rates[0][0];
    R_i_OUT[0][1]=lp_rates[0][1];
    R_i_OUT[1][0]=lp_rates[p/2][0];
    R_i_OUT[1][1]=lp_rates[p/2][1];
	
	
	
    /*************INIT IN *****************/
    //Simulate
    plasticPingRateN_recW(n,no,Re,R_i_IN,xEE,xEI,xIE,xII,
                    xEE_c,xEI_c,xIE_c,xII_c,wW,dt,W_t);

    //Save data
    char * filename_in = "plasticPingRateN_recW_tester_iIN.dat";
    asave(n, no, Re, filename_in);
    printf("Init-in, Rate data saved as %s\n", filename_in);

    //Convert weight over time to a 2d printable matrix
    double output_w[n/rw][g*g];
    for (t=0;t<n/rw;t++){ for (i=0;i<g;i++){ for (j=0;j<g;j++){
        output_w[t][g*i+j] = W_t[t][i][j];
    }}}
	
    //Save data for weights
    char * filename_w_in = "plasticPingRateN_recW_tester_w_iIN.dat";
    asave(n/rw, g*g, output_w, filename_w_in);
    printf("Init-in, Weight data saved as %s\n", filename_w_in);



    /************* INIT OUT *****************/
    //Simulate
    plasticPingRateN_recW(n,no,Re,R_i_OUT,xEE,xEI,xIE,xII,
                    xEE_c,xEI_c,xIE_c,xII_c,wW,dt,W_t);

    //Save data
    char * filename_out = "plasticPingRateN_recW_tester_iOUT.dat";
    asave(n, no, Re, filename_out);
    printf("Data saved as %s\n", filename_out);
	
    //Convert weight over time to a 2d printable matrix
    for (t=0;t<n/rw;t++){ for (i=0;i<g;i++){ for (j=0;j<g;j++){
        output_w[t][g*i+j] = W_t[t][i][j];
    }}}

    //Save data for weights
    char * filename_w_out = "plasticPingRateN_recW_tester_w_iOUT.dat";
    asave(n/rw, g*g, output_w, filename_w_out);
    printf("Init-in, Weight data saved as %s\n", filename_w_out);

    return 0;
	
}

