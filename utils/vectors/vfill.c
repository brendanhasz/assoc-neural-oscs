/* vfill - Fill a vector with a given value

	Arguments
		int n		Length of array
		double A[]	Array to fill
		double x	Value to fill array with

        
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
vfill(int n, double A[], double x)
{
	int i;
	for (i=0; i<n; i++)
	{
		A[i] = x;
	}
}
