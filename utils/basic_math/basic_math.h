/*
	basic_math - basic math functions

	FUNCTIONS
	****************************************************************
	
	*** BASIC MATH AND DATA GENERATION FUNCTIONS ***
	log2 - Find the log2 of a number
	max - Find the larger of two numbers
	min - Find the smaller of two numbers
	round - Round a number to the nearest integer
	gen_rand - Generate a random number (double) from 0 to 1
	gen_randn - Generate a single number drawn from a gaussian distribution
	nextpow2 - Calculates the next power of 2


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

// log2 - Calculate the log base 2 of a number
#ifndef log2
#define log2(x) ( log(x) / log(2) )
#endif

// max - Return the greater of two numbers
#ifndef max
#define max(x,y) ( x > y ? x : y )
#endif

// min - Return the lesser of two numbers
#ifndef min
#define min(x,y) ( x < y ? x : y )
#endif

// round - Round a number to the nearest integer
#ifndef round
#define round(x) ( x-floor(x) < 0.5 ? floor(x) : ceil(x) )
#endif

// gen_rand - Generate a random number (double) from 0 to 1
#ifndef gen_rand
#define gen_rand() ( rand() / (1.0 + RAND_MAX) )
#endif

// gen_randn - Generate a random value drawn from a normal dist. using Box–Muller transform
#ifndef gen_randn
#define gen_randn() ( sqrt(-2*log(gen_rand())) * sin(2*M_PI*gen_rand()) )
#endif

// nextpow2 - Finds the next power of 2 for a number
#ifndef nextpow2
#define nextpow2(a) ((int) pow(2,ceil(log2(a))))
#endif
