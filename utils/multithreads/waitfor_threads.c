/*
	waitfor_threads

	Waits for the threads of passed pointers before continuting
*/

#include "multithreads.h"

void 
waitfor_threads(int n, pthread_t threadps[])
{
	int i;
	for (i=0; i<n; i++){
		pthread_join(threadps[i],NULL);
	}
}

