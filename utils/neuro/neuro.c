/* fileIO.c

	*** FILE OPERATION FUNCTIONS ***
	vsave - Save a vector to file
	vsave2 - Save 2 vectors to file
	vsaven - Save any number of vectors to file
	asave - Save a 2D array to file
	TODO: vload - Load a vector from a file
	TODO: vsaven - Load any number of vectors from a file
	TODO: aload2 - Load a 2d array from a file


	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0 Unported 
	License.  You can use it and modify it any way you like as long as you 
	aren't commercially making money off it - if you are, I want some too!

*/
#include "../../sig_proc/l2peaks.h"

#include "rateN/rateN.c"
#include "get_last_period/get_last_period.c"
#include "pingRateN/pingRateN.c"
