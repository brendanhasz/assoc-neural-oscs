/* gsmoothip - Smooth a vector in place

	Smooths function A of length n with a gaussian kernel of length w.
	Replaces A with the smoothed function.
	
	Arguments
		int n		Length of array
		double A[]	Vector to smooth
		int w		Width of smoothing kernel (larger=more smoothing)

        
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
gsmoothip(int n, double A[], int w)
{
	double S[n];
	gsmooth(n, A, S, w);
	vcpy(n, S, A);
}
