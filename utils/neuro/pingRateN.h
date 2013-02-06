/*
	pingRateN - Simulates a system of coupled neural PING oscillators

	Simulates coupled PING oscillators - you specify the cross-group
	connectivity and initial rates for each group. Uses the simple rate
    model described in Ch. 7.5 of "Theoretical Neuroscience", by 
    Peter Dayan and L. F. Abbott.

	INPUTS
	int n				Number of timesteps to simulate
	int no				Number of oscillators
	double Re[n][no]	Rate vectors to return Excit. group rates in
	double R_i[no][2]	Initial rates for groups
	double xEE			Cross-oscillator E->E syn strength
	double xEI			Cross-oscillator E->E syn strength
	double xIE			Cross-oscillator E->E syn strength
	double xII			Cross-oscillator E->E syn strength
	double wW[2][2]		Within-oscillator strength {{EE, EI},{IE, II}}
	double dt			Timestep duration in seconds


	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0 
	Unported License.  You can use it and modify it any way you like as
	long as you aren't commercially making money off it - if you are, 
	I want some too!

*/

void pingRateN(int n, int no, double Re[n][no], double R_i[no][2], double xEE, double xEI, double xIE, double xII, double wW[2][2], double dt);
	
