/* 
	multithreads_tester.c

	Tests the multithreading functions and header file

*/

#include <stdio.h>
#include "multithreads.h"

void * t_func(void * args){

	THREAD_DAT_1D * in = args;
	int a = in->a;
	int b = in->b;
	int res = in->res;
	int i;

	for (i=a; i<b; i++){
		in->DATA[i] = i;
	}

	printf("INSIDE le thread!\n");

	pthread_exit(NULL);
}


int main(void)
{
	int i;

	pthread_t threads[NUM_THREADS];
	THREAD_DAT_1D t_args[NUM_THREADS];
	int t_divs[NUM_THREADS+1];

	//Matrix to pass into threads
	int res = 20;
	double thevector[res];
	
	//Segment matrix indexes for threads
	segment_threads(NUM_THREADS, 0, res, t_divs);

	//Put data in thread args
	for (i=0; i<NUM_THREADS; i++){
		t_args[i].a = t_divs[i];
		t_args[i].b = t_divs[i+1];
		t_args[i].res = res;
		t_args[i].DATA = thevector;
	}


	//Run the threads
	for (i=0; i<NUM_THREADS; i++){
		printf("About to start thread %d\n", i);
		pthread_create(&threads[i],NULL,t_func,(void*)&t_args[i]);
	}

	//Wait for the threads to finish
	waitfor_threads(NUM_THREADS,threads);

	printf("All threads have joined.\n\n");

	//Print data
	for (i=0; i<res; i++){
		printf("%f\n", thevector[i]);
	}

	printf("Done!\n");

	return 0;

}


