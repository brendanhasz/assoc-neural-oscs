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
	double (*lp_rates)[][2];
	double (*ee_vec)[];
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
	double Re[in->n][in->no];
	double R_i[in->no][in->no];
	double pds[in->no][in->no];
	
	/**************LOOP THROUGH EE STRS AND INIT PHASE DIFFS *************/
	for (i=in->ee_a; i<in->ee_b; i++){
		printf("%f percent done\n", 100*((double) i-in->ee_a)/((double) in->ee_b-in->ee_a));
		for (j=0; j<in->ipd_res; j++){

			//find initial rates for this init phasediff
			R_i[0][0]=in->lp_rates[0][0];
			R_i[0][1]=in->lp_rates[0][1];
			R_i[1][0]=in->lp_rates[j*in->p/in->ipd_res][0];
			R_i[1][1]=in->lp_rates[j*in->p/in->ipd_res][1];
			
			in->phdiffs[i][j]=0; //Initialize sum to 0

			for (k=0; k<in->trials; k++){ //for several trials

				//simulate
				pingRateN(in->n,in->no,Re,R_i,in->ee_vec[i],
					in->ei,in->ie,in->ii,in->wW,in->dt);
			
				//find steady state phase difference
				phdiff2(in->n, in->no, Re, pds);
				in->phdiffs[i][j]=in->phdiffs[i][j]+pds[0][1]; //Add to sum
			}

			in->phdiffs[i][j]=in->phdiffs[i][j]/in->trials; //Find average

		}
	}

	return NULL;

}
