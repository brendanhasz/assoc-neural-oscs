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

void
gsmooth(int n, double A[], double S[], int w)
{
	if ( w>n || w<1 ) { return; } //Make sure inputs are valid
	
	int w2, i, j, ii;
	double gauss[w], thesum, scl;

	w2 = (int)floor(w/2); //Half of the width of gauss curve

	//Create the gaussian kernel
	vgauss(w,gauss,3);

	//Smooth the function
	zeros(n,S);  //Initialize smoothed function to 0
	for (i=0; i<n; i++)
	{
		thesum=0;
		for (j=0; j<w; j++)
		{
			ii = i+j-w2;
			if (ii<0) ii = abs(ii);
			else if (ii>=n) ii = n-1-ii%n;	
			thesum += A[ii]*gauss[j];
		}
		S[i] = thesum;
	}

}
