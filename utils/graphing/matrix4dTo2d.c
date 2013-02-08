/*
	matix4dTo2d - Transforms a 4-d matrix into a 2-d one

	Longer description of the filelength

	INPUTS
	c		lalala
	d		lololo

	OUTPUTS
	a		hehehe
	b		hahaha


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

void matrix4dTo2d(int a, int b, int c, int d, double A[a][b][c][d], double B[a*c][b*d])
{


int ee, ii, ei, ie, Yee, Xii, Y, X;

for (ee=0; ee<a; ee++){
  Yee = ee*c;  //Y position of block
  for (ii=0; ii<b; ii++){
	Xii = ii*d;  //X position of block
	for (ei=0; ei<c; ei++){
	  Y = Yee+ei;  //Y position of pixel
	  for (ie=0; ie<d; ie++){
		X = Xii + ie;  //X position of pixel
		B[Y][X] = A[ee][b-1-ii][ei][d-1-ie];
	  }
	}
  }
}

}
