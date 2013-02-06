/* lnpeaks - Find the indicess of the last n peaks of a vector

	Arguments
		int m			Length of data vector
		double data[]	Vector to search for peaks
		int p			Number of last peaks to find (2 gets the last 2 pks)
		int theln[]		Array in which to put last p peaks (from end -> start)


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
lnpeaks(int m, double data[], int p, int theln[])
{
	int maxp=100, nps, thepeaks[maxp], i;
	peaks(m, data, &nps, thepeaks);
	for (i=0; i<p && i<maxp; i++){
		theln[i] = thepeaks[nps-1-i];
	}
}
