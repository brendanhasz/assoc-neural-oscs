/* gsmooth - Smooth a vector using gaussian smoothing

	Smooths function A of length n with a gaussian kernel of length w.
	Replaces returns the smoothed vector in array S, also length n.
	
	Arguments
		int n		Length of array
		double A[]	Vector to smooth
		double S[]	Vector in which to store smoothed data
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

void gsmooth(int n, double A[], double S[], int w);
