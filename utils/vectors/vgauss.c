/* vgauss - Generate a gaussian function vector

	Generates a gaussian function in the array A of length n, ranging across d 
    standard deviations
	
	Arguments
		int n		Length of vector to fill
		double A[]	Vector to fill with gaussian function
		double d	How many standard deviations to include

        
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
vgauss(int n, double A[], double h)
{

	double a=0, b=1;
	double mu = (a+b)/2;
	double sig = (b-a)/(2*h);
	double c = h/(sqrt(2*M_PI)*pow(sig,2));

	//Create the gaussian
	linspace(a,b,n,A);
	int i;
	for (i=0; i<n; i++)
	{
		A[i] = c*exp(-pow((A[i]-mu)/sig,2)/2);
	}
}
