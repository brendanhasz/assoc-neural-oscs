/* vectors.c

	*** VECTOR FUNCTIONS ***
	vcpy - Copy a vector
	vrand - Fill a vector with random numbers from 0 to 1
	vrandn - Generate a vector of numbers drawn from a gaussian distribution
	vmax - Find the maximum value in a vector
	vmin - Find the minimum value in a vector
	maxindex - Find the index of the max value in a vector
	vfill - Fill a vector with a given value
	zeros - Fill a vector with zeros
	ones - Fill a vector with ones
	linspace - Generate a vector of linearly spaced values within a range
	vgauss - Generate a gaussian function vector
	diff - Find the derivative of a function vector
	TODO: diff1 - Efficient differentiation

    
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
#include <stdlib.h>
#include "../basic_math/basic_math.h"

#include "vcpy.c"
#include "vrand.c"
#include "vrandn.c"
#include "vmax.c"
#include "vmin.c"
#include "maxindex.c"
#include "vfill.c"
#include "zeros.c"
#include "ones.c"
#include "linspace.c"
#include "vgauss.c"
#include "diff.c"




