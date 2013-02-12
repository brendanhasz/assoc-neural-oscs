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
#include <pthread.h>
#include "EE_Attractor_worker.h"
#include "../../utils/neuro/pingRateN/pingRateN.h"
#include "../../utils/sig_proc/phdiff2.h"

/*
typedef struct {
	int n;
	int no;
	int p;
	int trials;
	double dt;
	int ee_res;
	int ee_a;
	int ee_b;
	int ipd_res;
	double lp_rates[p][2];
	double ee_vec[ee_res];
	double ei;
	double ie;
	double ii;
	double wW[2][2];
	double (*phdiffs)[ee_res][ipd_res];
} thread_struct;
*/

void *EE_Attractor_worker(void *arg)
{
	
	//Cast input args to structure
	thread_struct *in = arg;	

	//Counters
	int i, j, k;
	
	//Initialize arrays
	double Re[n][no];
	double R_i[no][no];
	double pds[no][no];
	
	/**************LOOP THROUGH EE STRS AND INIT PHASE DIFFS *************/
	for (i=in->ee_a; i<in->ee_b; i++){
		printf("%f percent done\n", 100*((double) i-in->ee_a)/((double) in->ee_b-in->ee_a));
		for (j=0; j<in->ipd_res; j++){

			//find initial rates for this init phasediff
			R_i[0][0]=in->lp_rates[0][0];
			R_i[0][1]=in->lp_rates[0][1];
			R_i[1][0]=in->lp_rates[j*in->p/in->ipd_res][0];
			R_i[1][1]=in->lp_rates[j*in->p/in->ipd_res][1];
			
			phdiffs[i][j]=0; //Initialize sum to 0

			for (k=0; k<trials; k++){ //for several trials

				//simulate
				pingRateN(n,no,Re,R_i,ee_vec[i],ei,ie,ii,wW,dt);
			
				//find steady state phase difference
				phdiff2(n, no, Re, pds);
				phdiffs[i][j]=phdiffs[i][j]+pds[0][1]; //Add to sum
			}

			phdiffs[i][j]=phdiffs[i][j]/trials; //Find average

		}
	}

	/******************* WRITE DATA TO FILE **********************/
	char * filename = "EE_Attractor.dat";
	asave(ee_res, ipd_res, phdiffs, filename);
	printf("Data saved as %s\n", filename);
	

	return 0;

}
