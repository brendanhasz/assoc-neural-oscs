/* vrandn - Generate a vector of values drawn from a normal distribution

	Arguments
		int n		Length of array
		double A[]	Array to fill with random numbers from normal dist.


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
vrandn(int n, double A[])
{
	int i;
	for (i=0; i<n; i++)
	{
		A[i] = gen_randn();
	}
}
