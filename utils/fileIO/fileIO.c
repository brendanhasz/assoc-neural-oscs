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

#include <stdio.h>
#include <stdlib.h>

/* vsave - Saves a vector to a file
	INPUTS
		int n			Length of the vector to save to file
		double A[]		Vector to save to file
		char fileName[]	The name of the file to save to
*/
#include "vsave.c"


/* vsave2 - Save 2 vectors to a file
	INPUTS
		int n			Length of the vector to save to file
		double A[]		First vector to save to file (1st column)
		double B[]		Second vector to save to file (2nd column)
		char fileName[]	The name of the file to save to
*/
#include "vsave2.c"


/* vsaven - Save any number of vectors to a file
	Arguments
		int n			Length of the vectors to be saved
		int nv			Number of vectors to save
		double ?? A		Array of pointers to the vectors to be saved
		char fileName[]	The desired name of file		
*/
#include "vsaven.c"


/* asave - Saves a 2d array to a file
	INPUTS
		int n			Height of the array to save to file
		int m			Length of the array to save to file
		double A[]		Vector to save to file
		char fileName[]	The name of the file to save to
*/
#include "asave.c"
