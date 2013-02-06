/* diff - Cind the derivative of a vector (difference between points)

	Simplest differential calculation - just finds the difference between
	points. df/dt(n) = f(n+1) - f(n)
	
	Arguments
		int n		Length of vector
		double A[]	Vector for which to find derivative
		double D[]	Vector in which to store derivative of A

        
	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0 Unported 
	License.  You can use it and modify it any way you like as long as you 
	aren't commercially making money off it - if you are, I want some too!

*/

void diff(int n, double A[], double D[]);
