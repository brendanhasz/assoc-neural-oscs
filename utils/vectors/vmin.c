/* vmin - Find the minimum value in a vector

	Arguments
		int n		Length of array
		double A[]	Array for which to find the min value

        
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
vmin(int n, double A[])
{
	int i;
	double themin = A[0];
	for (i=1; i<n; i++){ themin = min(themin,A[i]);	}
	return themin;
}
