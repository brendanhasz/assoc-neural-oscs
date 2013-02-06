/* maxindex - Get the index of the max value

	Arguments
		int n		Length of vector
		double A[]	Vector in which to find the maximum index
		
	Returns
		int theind	The index of the max value in the vector

        
	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0 Unported 
	License.  You can use it and modify it any way you like as long as you 
	aren't commercially making money off it - if you are, I want some too!

*/

int
maxindex(int n, double A[])
{
	int theind=0, i;
	double maxval=A[0];
	for (i=0; i<n; i++){
		if ( A[i] > maxval ) {
			theind = i;
			maxval = A[i];
		}
	}
	return theind;
}
