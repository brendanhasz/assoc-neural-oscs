/* linspace - Generate a vector of linearly spaced values

	Generate a length n vector of linearly spaced values from a to b, in 
	array A.

	Arguments
		int a		Starting value (first value)
		int b		Ending value (last value)
		int n		Number of values (length of generated vector)
		double A[]	Array in which to put vector of values

        
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
linspace(double a, double b, int n, double A[])
{
	double step = (b-a)/(n-1);
	int i;
	for (i=0; i<n; i++) { A[i] = a+i*step; }
}
