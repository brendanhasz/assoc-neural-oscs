/* acorr - Calculate the Autocorrelation function for a vector

	Arguments
		int n		Length of input vector A
		double A[]	Input vector for which to find the autocorrelation fn
		int nn		Desired length of autocorrelation return vector
		double yy[]	Y values of the autocorrelation fn

        
	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0 Unported 
	License.  You can use it and modify it any way you like as long as you 
	aren't commercially making money off it - if you are, I want some too!

*/

void
acorr(int n, double A[], int nn, double yy[])
{
	xcorr(n, A, A, nn, yy);  //Just cross-corr of the same fn twice
}
