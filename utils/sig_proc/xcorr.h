/* xcorr - Calculate the cross-correlation function between two vectors

	Arguments
		int n		Length of input vector A
		double A[]	First input vector for which to find the X-correlation fn
		double B[]	Second input vec for which to find the X-correlation fn
		int nn		Desired length of X-correlation return vector
		double yy[]	Y values of the X-correlation fn

        
	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0 Unported 
	License.  You can use it and modify it any way you like as long as you 
	aren't commercially making money off it - if you are, I want some too!

*/

void xcorr(int n, double A[], double B[], int nn, double yy[]);
