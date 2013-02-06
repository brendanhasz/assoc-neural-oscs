/* vcpy - Copy a vector

	Arguments
		int n			Length of vectors
		double src[]	Vector to be copied from
		double dest[]	Vector to be copied into


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
vcpy(int n, double src[], double dest[])
{
	int i;
	for (i=0; i<n; i++){
		dest[i] = src[i];
	}
}
