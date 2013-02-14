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
	int i, j;	

	//phase difference storage array
	double phdiffs[ee_res*ipd_res];


	/********************SIMULATION USING THREADING *****************/
	//Declare thread arrays
	pthread_t threads[NUM_THREADS];
	THREAD_DAT_1D t_args[NUM_THREADS];
	int t_divs[NUM_THREADS+1];

	//Segment/assign chunks to threads
	segment_threads(NUM_THREADS, 0, ee_res, t_divs);
	
	printf("t_divs[0]=%d\n", t_divs[0]);
	for (i=1; i<=NUM_THREADS; i++){
		printf("t_divs[%d]=%d\n", i, t_divs[i]);
	}

	//Put data in thread args
	for (i=0; i<NUM_THREADS; i++){
		t_args[i].a = t_divs[i];
		t_args[i].b = t_divs[i+1];
		t_args[i].res = ee_res;
		t_args[i].DATA = (double *)&phdiffs;
	}

	printf("Well we got here... problem creating threads...\n");

	//Run
	for (i=0; i<NUM_THREADS; i++){
		pthread_create(&threads[i],NULL,EE_Attractor_worker,(void*)&t_args[i]);
	}
	
	//Wait for the threads to finish
	waitfor_threads(NUM_THREADS, threads);

	//Put 1d vector -> 2d array
	double phdiffs_2d[ee_res][ipd_res];
	for (i=0; i<ee_res; i++){
		for (j=0; j<ipd_res; j++){
			phdiffs_2d[i][j]=phdiffs[i*ee_res+j];
		}
	}	

	/******************* WRITE DATA TO FILE **********************/
	char * filename = "EE_Attractor.dat";
	asave(ee_res, ipd_res, phdiffs_2d, filename);
	printf("Data saved as %s\n", filename);
	

	return 0;

}

