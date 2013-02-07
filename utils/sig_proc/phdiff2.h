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

void phdiff2(int n, int ng, double A[][ng], double pds[ng][ng]);
