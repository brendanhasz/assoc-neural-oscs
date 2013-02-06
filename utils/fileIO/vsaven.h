/* vsaven - Save any number of vectors to a file

	Arguments
		int n			Length of the vectors to be saved
		int nv			Number of vectors to save
		double (*A[])[]	Array of pointers to the vectors to be saved
		char fileName[]	The desired name of file		

        
	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0 Unported 
	License.  You can use it and modify it any way you like as long as you 
	aren't commercially making money off it - if you are, I want some too!

*/

void vsaven(int n, int nv, double (*A[nv])[], char fileName[]);
