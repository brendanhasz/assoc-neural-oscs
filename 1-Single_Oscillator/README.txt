NAME
	single_PING_group - simulates a single PING oscillator

DESCRIPTION

	Simulates a single PING oscillator with simple rate models.  The 
	system consists of a single excitatory neuron group coupled to a 
	single inhibitory neuron group.  The rate model used is the simple 
	rate model described in Ch. 7.5 of "Theoretical Neuroscience", by 
	Peter Dayan and L. F. Abbott.

USAGE

	To compile the code, navigate into this folder and run make:
	
	$	make
	
	then run the code by running the program:
	
	$	./single_PING_group
	
	The output is two vertical vectors of rates (sampled @ 10,000 Hz),
	saved in the file "single_PING_group.dat" in this directory.
	The first column is the Excitatory group average rate over time, 
	and the second column is the Inhibitory group rate.  For plotting
	tools, see the /graphing folder.	

COPYRIGHT

	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0 
	Unported License.  You can use it and modify it any way you like as
	long as you aren't making money off it - if you are, I want some 
	too!
