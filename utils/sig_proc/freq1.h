/* freq1 - Get most prominent frequency in a vector (after smoothing f spec)

	Returns the frequency value of the highest amplitude peak in the frequency
	spectrum, optionally after smoothing the frequency spectrum (if SMOOTH_FLAG
	is set to TRUE)
	
	Arguments
		int n			Length of data vector
		double data[]	Vector for which to find frequency
		int SMOOTH_FLAG	If true, will smooth the frequency spectrum before
							finding the largest amplitude peak

	Returns 
		double thefreq	The most prominent frequency in the vector


	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0 Unported 
	License.  You can use it and modify it any way you like as long as you 
	aren't commercially making money off it - if you are, I want some too!

*/

double freq1(int n, double data[], int SMOOTH_FLAG);
