/* phdiff - Calculate the phase difference between two functions

	Calculate the phase difference between two functions A and B of length n 
	using cross-correlation. Finds the cross-correlation across one period,
	and finds the phase difference at which the cross-correlation is greatest.
	Will only yeild accurate results if both functions have similar 
	frequencies.

	Arguments
		int n		Length of input vectors
		double A[]	First input vector
		double B[]	Second input vector

	Returns
		double tpd	The phase difference between the two functions 0->2*pi


	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0 Unported 
	License.  You can use it and modify it any way you like as long as you 
	aren't commercially making money off it - if you are, I want some too!

*/

double
phdiff(int n, double A[], double B[])
{

	double sr=SAMPLING_FREQ, P; //sr=Sampling rate
	int p, p2;

	P = 2*sr/(freq(n, A) + freq(n, B));  //Period duration in ms
	p2 = (int) round(P/2);  //range of cross-correlation: +/-p2
	p = 2*p2;
	
	//Perform the cross-correlation
	double xcorrvec[p];
	xcorr(n, A, B, p, xcorrvec);

	//Smooth the cross correlation function
	int sf = 8;  //Smoothing factor, higher is less smooth
	gsmoothip(p, xcorrvec, floor(p/sf));

	//Find the max index of the xcorr fn, and corresponding phdiff
	return 2*M_PI*abs(maxindex(p, xcorrvec)-p2)/P;
}
