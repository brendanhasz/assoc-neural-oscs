/* freqspec - Simple way to get frequency spectrum

	Gets the neuroscience-relevant frequency spectrum for input data
	that is, trunucates all frequenies higher than 200Hz.
	
	Arguments
		int nn			Length of vector data[]
		double data[]	Data as a fn of time
		double f[]		Vector of frequency points (x-axis of power spec)
		double a[]		Vector of amplitudes (y-axis of power spec)


	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0 Unported 
	License.  You can use it and modify it any way you like as long as you 
	aren't commercially making money off it - if you are, I want some too!

*/

double *
freqspec(int nn, double data[], double f[], double a[])
{
	double sr = SAMPLING_FREQ;
	double cutoff_freq_high = 200;  //Don't bother with frequencies above here
	double cutoff_freq_low = 4;  //Don't bother with frequencies below here
	int n = nextpow2(nn), i;  //Next pow of 2 to ensure valid input to realfft
	double A[n], ff[n];
	zeros(n, A);  //Pad with zeros
	zeros(n, ff);
	ff[0]=0;
	vcpy(nn, data, A);  //Copy data into new array - don't write over our data!
	realfft(n, A, 1);  //Perform the discrete fourier transform
	linspace(0,sr/2,n,ff);  //Get x values (frequency values in power spec)
	for (i=0; i<n; i++) { 
		if ( ff[i] > cutoff_freq_low && ff[i] < cutoff_freq_high ) {
			A[i] = abs(A[i]);
		} else {
			A[i] = 0;
		}
	}
	vcpy(nn, A, a);   //Write into passed freq and amplitude arrays, but only
	vcpy(nn, ff, f);  //up to the length specified!
	return a;
}
