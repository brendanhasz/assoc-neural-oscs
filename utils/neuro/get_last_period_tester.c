/*
	HelloWorld - prints a welcoming message to the terminal
	[a b] = main(c, d)

	Longer description of the filelength

	INPUTS
	c		lalala
	d		lololo

	OUTPUTS
	a		hehehe
	b		hahaha


	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0 Unported 
	License.  You can use it and modify it any way you like as long as you 
	aren't commercially making money off it - if you are, I want some too!

*/

#include <stdio.h>
#include "neuroutils.h"

int main(void)
{

	int n = 400;    //Timesteps
    double R[n][2];    //Rate vector
	double W[4]; //Synaptic weights
		W[0]=2;		W[1]=2.873;	//EE	EI
		W[2]=-2.873;	W[3]=-2;		//IE	II

    get_init_rates(&n, R, W);
    
    printf("period = %f\n",n);

    //Save data
	char * filename = "get_init_rates_tester.dat";
	asave2(n, 2, R, filename);
	
	printf("Done!  Data saved as %s\n", filename);

	return 0;

}
