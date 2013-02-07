/* phdiff2 - Calculate the phase difference between two functions

	Calculate the phase difference between two functions A and B of length n 
	by finding the peaks of the functions.  While faster than cross-correlation
	and FFT method, only works for very smooth functions.  Pass a 2d array,
	whoose columns are rate vectors; each column is rate vector for one group.

	Arguments
		int n		Length of input vectors
		int ng		Number of groups (number of columns in A)
		double A[]	Rate matrix
        double pds[][]  phase difference matrix

	Returns
		double tpd	The phase difference between the two functions (0->2*pi)


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
#include "l2peaks.h"

void
phdiff2(int n, int ng, double A[][ng], double pds[ng][ng])
{	
	//TODO: could start at A[max(0, n-2000)] or something for faster...
	// int m=1000; //like this
	int i, j, thisl2[2], theln[ng][2];
	double thevec[n], temppd;
		
	//Find last 2 peaks for each group
	for (i=0; i<ng; i++){
		for (j=0; j<n; j++){ //copy group into vector
			thevec[j] = A[j][i];
		}
		l2peaks(n, thevec, thisl2);
		theln[i][0] = thisl2[0];  //Save 2nd to last peak
		theln[i][1] = thisl2[1];  //Save last peak
	}
	
	//Using peaks, find phase difference matrix
	i=0;
	while (i<ng){
		j=i+1;
		while (j<ng){
			//find phase difference (0->2*pi)
			temppd = 2*M_PI*(
				(theln[i][0]<theln[j][0] ? 
					theln[j][0] : 
					theln[j][1])
				-theln[i][0]) / (theln[i][1]-theln[i][0]);
						
			//convert to 0->pi
			pds[i][j] = temppd>M_PI ? 2*M_PI-temppd : temppd;
			
			j++;
		}
		i++;
	}
	
}
