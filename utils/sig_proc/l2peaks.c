/*	l2peaks - Finds the last two peaks of a function
	
	Arguments
		int n		Length of the data vector
		double A[]	Vector of data
		int thel2[]	Vector in which to return last 2 peaks


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
l2peaks(int n, double data[], int thel2[])
{
	thel2[0] = 0;
	thel2[1] = 0;
	int i;
	for (i=1; i<n-1; i++){
		if ( (data[i-1] < data[i]) && (data[i] > data[i+1]) ){
			thel2[0] = thel2[1];
			thel2[1] = i;
		}
	}

}
