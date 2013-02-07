/* freqspec - Simple way to get frequency spectrum

	Gets the neuroscience-relevant frequency spectrum for input data
	that is, trunucates all frequenies higher than 200Hz.
	
	Arguments
		int nn			Length of vector data[]
		double data[]	Data as a fn of time
		double f[]		Vector of frequency points (x-axis of power spec)
		double a[]		Vector of amplitudes (y-axis of power spec)


	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0 Unported 
	License.  You can use it and modify it any way you like as long as you 
	aren't commercially making money off it - if you are, I want some too!

*/

double * freqspec(int nn, double data[], double f[], double a[]);
