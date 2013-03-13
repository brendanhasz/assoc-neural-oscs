/* pingRateN_tester - tests the pingRateN function
    
	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

*/

#include <stdio.h>
#include "../get_last_period/get_last_period.h"
#include "pingRateN.h"
#include "../../fileIO/fileIO.h"

int main(void){
	
	int n=29999, no=2;
	double dt = 0.0001;
	double Re[n][no], R_i[no][2];
	double xEE_IN=0.15, xEI_IN=0, xIE_IN=0, xII_IN=0;	//SS in-phase
	double xEE_OUT=0, xEI_OUT=1, xIE_OUT=0, xII_OUT=0; //SS out
	//double xEE_OUT=0, xEI_OUT=0.3, xIE_OUT=-0.3, xII_OUT=0; //SS out
	double wW[2][2];     //within-oscillator synaptic weights
		wW[0][0]=2;			wW[0][1]=2.873;	//EE	EI
		wW[1][0]=-2.873;	wW[1][1]=-2;		//IE	II
	
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
	
	
	
	/*************INIT IN, SS IN *****************/
	pingRateN(n,no,Re,R_i_IN,xEE_IN,xEI_IN,xIE_IN,xII_IN,wW,dt);
	
	//Save data
	char * filename1 = "pingRateN_tester_iIN_ssIN.dat";
	asave(n, no, Re, filename1);
	printf("Data saved as %s\n", filename1);
	
	
	/*************INIT IN, SS OUT *****************/
	pingRateN(n,no,Re,R_i_IN,xEE_OUT,xEI_OUT,xIE_OUT,xII_OUT,wW,dt);
	
	//Save data
	char * filename2 = "pingRateN_tester_iIN_ssOUT.dat";
	asave(n, no, Re, filename2);
	printf("Data saved as %s\n", filename2);


	/*************INIT OUT, SS IN *****************/
	pingRateN(n,no,Re,R_i_OUT,xEE_IN,xEI_IN,xIE_IN,xII_IN,wW,dt);
	
	//Save data
	char * filename3 = "pingRateN_tester_iOUT_ssIN.dat";
	asave(n, no, Re, filename3);
	printf("Data saved as %s\n", filename3);


	/*************INIT OUT, SS OUT *****************/
	pingRateN(n,no,Re,R_i_OUT,xEE_OUT,xEI_OUT,xIE_OUT,xII_OUT,wW,dt);
	
	//Save data
	char * filename4 = "pingRateN_tester_iOUT_ssOUT.dat";
	asave(n, no, Re, filename4);
	printf("Data saved as %s\n", filename4);


	return 0;
	
}
