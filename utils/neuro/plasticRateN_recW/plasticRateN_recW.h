/*
    plasticRateN - Simulates a system of coupled groups of neurons
        using simple rate models, and allows the initial synaptic
        weights to change over time according to synaptic plasticity
        rules.
    
    plasticRateN_recW(g, n, R[g][n], R_i[g], W[g][g], gamma[g], tau[g], dt)

    Simulates a system of coupled groups of neurons using the simple rate
    model described in Ch. 7.5 of "Theoretical Neuroscience", by Peter Dayan
    and L. F. Abbott.  Allows the initial synaptic weights to change over
    time according to the BCM Rule (Bienenstock, Cooper, Munro, 1982).

    INPUTS
    int g            Number of groups to simulate
    int n            Number of timesteps to simulate
    double R[g][n]   Rate vectors of each group over time
    double R_i[g]    Initial rates for each group
    double W[n/100][g][g]  Weight vectors of each synapse over time
    int W_c[g][g]    Do the weights change over time? 0 (no) or nonzero (y)
    double W_i[g][g] Initial synaptic weights between groups (W[i][j]: i->j)
    double t_w[g][g]      Time constants for syn. weight change
    double th[g][g]    Inital sliding thresh values
    double t_th[g][g]  Sliding thesh time constants
    double gamma[g]  Constant input to each group
    double tau[g]    Time constant of each group
    double dt        Timestep duration
	
	
    Copyright 2013
    Brendan Hasz
    bhasz@brandeis.edu
    www.cs.brandeis.edu/~bhasz/main.php
    Brandeis University, Waltham, MA, USA

*/


void
plasticRateN_recW(int g, int n, double R[n][g], double R_i[], 
    double W_t[n/100][g][g], int W_c[g][g], double W[g][g], double W_b[g][g],
    double t_w, double th[g][g], double t_th,
    double gamma[], double tau[], double dt);

