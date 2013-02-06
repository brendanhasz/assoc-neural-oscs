/*
	get_init_rates - finds the rate curve over one period for steady-state 
                        PING oscillator with passed within-group cnxn strengths
    
    get_init_rates(n, rates[], wW[4])

    Fills rates[] with rates of 2 groups of cells (E+I) over the last
    oscillation of a 1-second time window.
    
	INPUTS
	n		Timesteps to simulate
	rates   n-by-2 array to fill with 2 rate vectors [0]=E, [1]=I
    wW      Within-group connection strength for this PING oscillator

	OUTPUTS
	n		changes to be the length of the period (in 100s of us)
	rates	fills with rate vectors


	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0 Unported 
	License.  You can use it and modify it any way you like as long as you 
	aren't commercially making money off it - if you are, I want some too!

*/

void get_last_period(int *p, double rates[][2], double wW[4]);
