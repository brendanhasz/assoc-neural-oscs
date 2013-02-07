/* stats.c

	*** STATISTICS FUNCTIONS ***
	sum - Calculate the sum of a vector
	mean - Calculate the mean of a vector
	var - Calculate the variance of a vector
	std - Calculate the standard deviation of a vector
	TODO: ttest - Find probability that 2 normal dists are drawn from same dist
	TODO: anova - Find prob. that multiple normal dists drawn from same dist
	TODO: krwaltest - Kruskal-Wallis non-parametric test of dist prob


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

/* sum - Calculate the sum of a vector
	Arguments
		int n			Length of the vector to be summed
		double A[]		The vector to be summed
		
	Returns
		double thesum	The sum of all elements in the vector
*/
#include "sum.c"


/* mean - Calculate the mean of a vector of values
	Arguments
		int n			Length of the vector
		double A[]		Vector for which to find the mean
		
	Returns
		double themean	The mean of the vector
*/
#include "mean.c"


/* var - Calculate the variance of a vector
	Arguments
		int n			Length of the vector
		double A[]		Vector for which to find the variance
		
	Returns
		double thevar	The variance of the vector
*/
#include "var.c"


/* std - Calculate the standard deviation of a vector
	Arguments
		int n			Length of the vector
		double A[]		Vector for which to find the standard deviation
		
	Returns
		double thestd	The standard deviation of the vector
*/
#include "std.c"
