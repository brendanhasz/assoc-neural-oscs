/* speaks - Find the peaks in data (after smoothing data)

	Smoothes the vector, and then finds peaks (points where the derivative goes
	from positive to negative).


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
speaks(int n, double data[], int *p, int peaks[], int SMOOTH_FLAG)
{
	//Smoothing
	int w=20, i;
	double A[n];
	gsmooth(n, data, A, w);
	
	//Find peaks
	*p = 0;
	for (i=1; i<n-1; i++){
		if ( A[i]-A[i-1]>0 && A[i+1]-A[i]<=0 ){
			peaks[*p] = i;
			*p = *p + 1;
		}
	}
}
