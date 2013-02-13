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
#include "EE_Attractor_worker.h"
#include "../../utils/fileIO/asave.h"

int main(void)
{
	//Simulation resolution
	int ee_res=200;
	int ipd_res=200;
	int i;	

	//phase difference storage array
	double phdiffs[ee_res][ipd_res];
	/*
	double **phdiffs;
	phdiffs = (double**) malloc(ee_res*sizeof(double*));
	for (i=0; i<ee_res; i++)
		phdiffs[i] = (double*) malloc(ipd_res*sizeof(double));
	*/


	/********************SIMULATION USING THREADING *****************/
	//Declare thread arrays
	pthread_t threads[NUM_THREADS];
	THREAD_DAT_2D t_args[NUM_THREADS];
	int t_divs[NUM_THREADS+1];

	//Segment/assign chunks to threads
	segment_threads(NUM_THREADS, 0, ee_res, t_divs);
	
	//Put data in thread args
	for (i=0; i<NUM_THREADS; i++){
		t_args[i].a = t_divs[i];
		t_args[i].b = t_divs[i+1];
		t_args[i].resr = ee_res;
		t_args[i].resc = ipd_res;
		//TODO: problem on following line...
		t_args[i].OUT = &phdiffs;
	}

	printf("Well we got here... problem creating threads...\n");

	//Run
	for (i=0; i<NUM_THREADS; i++){
		//TODO: problem on following line...
		pthread_create(&threads[i],NULL,EE_Attractor_worker,(void*)&t_args[i]);
	}
	
	//Join
	waitfor_threads(NUM_THREADS, NULL);


	/******************* WRITE DATA TO FILE **********************/
	char * filename = "EE_Attractor.dat";
	asave(ee_res, ipd_res, phdiffs, filename);
	printf("Data saved as %s\n", filename);
	

	return 0;

}

