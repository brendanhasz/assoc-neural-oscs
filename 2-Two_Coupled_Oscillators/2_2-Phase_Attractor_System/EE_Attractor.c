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
#include "../../utils/multithreads/multithreads.h"
#include "../../utils/vectors/linspace.h"
#include "../../utils/neuro/get_last_period/get_last_period.h"
#include "../../utils/neuro/pingRateN/pingRateN.h"
#include "../../utils/sig_proc/phdiff2.h"
#include "../../utils/fileIO/asave.h"

int main(void)
{
	//Simulation duration params
	int n=9999, no=2;
	double dt=0.0001;
	int i, j, k; //counters

	//X-oscillator synaptic strengths
	double ei=0.3;
	double ie=-0.5;
	double ii=0;

	//X-osc EE strength
	double ee_a=0;
	double ee_b=0.3;
	int ee_res=200;
	double ee_vec[ee_res];
	linspace(ee_a, ee_b, ee_res, ee_vec);

	//Initial phase difference steps
	int ipd_res = 200;

	//Number of trials per param choice
	int trials = 20;
	
	//Within-group synaptic strengths
	double wW[2][2];
		wW[0][0]=2;		wW[0][1]=2.873;	//EE	EI
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


	/********************SIMULATION USING THREADING *****************/
	//TODO: this...
	//use segment function in multithreads
	pthread_t threads[NUM_THREADS];
	thread_struct t_args[NUM_THREADS];
	int t_divs[NUM_THREADS+1];

	//segment
	segment_threads(NUM_THREADS, 0, ee_res, t_divs);
	
	//Put data in thread args
	for (i=0; i<NUM_THREADS; i++){
		t_args.n = 
		...
	}

	//run
	for (i=0; i<NUM_THREADS; i++){
		pthread_create(&threads[i], NULL, EE_Attractor_worker, &t_args[i]);
	}
	
	//Join
	waitfor_threads(NUM_THREADS, 



	/******************* WRITE DATA TO FILE **********************/
	char * filename = "EE_Attractor.dat";
	asave(ee_res, ipd_res, phdiffs, filename);
	printf("Data saved as %s\n", filename);
	

	return 0;

}
