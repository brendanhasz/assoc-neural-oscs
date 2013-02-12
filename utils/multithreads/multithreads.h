/*
	multithreads.h - header info for multithreading



*/

#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 4

//TODO: waitfor_threads - waits for threads to join
void waitfor_threads(int n, pthread_t threadps[]);

//segment_threads - segments a loop for threading
void segment_threads(int n, int a, int b, int divs[]);
