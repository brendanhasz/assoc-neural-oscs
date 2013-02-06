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
	and the second column is the Inhibitory group rate.  To plot the
	data, use your own plotting software, or if you have python, numpy,
	and matlibplot, you can run plotter.sh to plot the data:
	
	$	./plotter.sh
	
	To compile, run, and plot, simply run
	
	$	./run.sh
	

COPYRIGHT

	Copyright (C) 2012 Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA
