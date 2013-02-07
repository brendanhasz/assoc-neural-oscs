/* amp - Calculate the amplitude of a vector

	Arguments
		int n			Length of the vector
		double data[]	The vector for which to calculate the amplitude
		
	Returns
		double amptd	The amplitude of the vector


	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0 Unported 
	License.  You can use it and modify it any way you like as long as you 
	aren't commercially making money off it - if you are, I want some too!

*/

#include <math.h>

double
amp(int n, double data[])
{
	double mn=mean(n, data), sm=0;
	int i;
	for (i=0; i<n; i++){
		sm += pow(data[i]-mn,2);
	}
	return sqrt(sm/n);
}
