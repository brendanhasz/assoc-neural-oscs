/* EE_Attractor.c

	Finds steady state phase difference for a two-oscillator system
	as a function of initial phase difference and EE-cross-oscillator
	synaptic strength.


	Copyright (C) 2013 Brendan Hasz
	bhasz@brandeis.edu
	http://www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA
*/

#include <stdio.h>
#include "../../utils/vectors/linspace.h"
#include "../../utils/neuro/get_last_period/get_last_period.h"
#include "../../utils/neuro/pingRateN/pingRateN.h"
#include "../../utils/sig_proc/phdiff2.h"
#include "../../utils/graphing/matrix4dTo2d.h"
#include "../../utils/fileIO/asave.h"

int main(void)
{
	//Simulation duration params
	int n=9999, no=2;
	double dt=0.0001;
	int i, j; //counters

	//X-oscillator synaptic strengths
	double ei=0.3;
	double ie=-0.5;
	double ii=0;

	//X-osc EE strength
	double ee_a=0;
	double ee_b=0.2;
	int ee_res=10;
	double ee_vec[ee_res];
	linspace(ee_a, ee_b, ee_res, ee_vec);

	//Initial phase difference steps
	int ipd_res = 100;
	
	//Within-group synaptic strengths
	double wW[2][2];
		wW[0][0]=2;			wW[0][1]=2.873;	//EE	EI
		wW[1][0]=-2.873;	wW[1][1]=-2;	//IE 	II

	//Find rates for one period
	int p=1000;
	double lp_rates[p][2];
	get_last_period(&p, lp_rates, wW);

	//Initialize arrays
	double Re[n][no];
	double R_i[no][no];
	double pds[no][no];
	double phdiffs[ee_res][ipd_res];

	/**************LOOP THROUGH EE STRS AND INIT PHASE DIFFS *************/
	for (i=0; i<ee_res; i++){
		printf("Starting ee %d of %d\n", i, ee_res);
		for (j=0; j<ipd_res; j++){

			printf("\tStarting phdiff %d of %d\n", j, ipd_res);
			//find initial rates for this init phasediff
			R_i[0][0]=lp_rates[0][0];
			R_i[0][1]=lp_rates[0][1];
			R_i[1][0]=lp_rates[j*p/ipd_res][0];
			R_i[1][1]=lp_rates[j*p/ipd_res][1];
			
			//simulate
			pingRateN(n, no, Re, R_i, ee_vec[i], ei, ie, ii, wW, dt);
			
			//find steady state phase difference
			phdiff2(n, no, Re, pds);
			phdiffs[i][j]=pds[0][1];
		}
	}

	/******************* WRITE DATA TO FILE **********************/
	


	return 0;

}
