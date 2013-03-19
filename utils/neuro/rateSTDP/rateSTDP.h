/*
    rateSTDPmap.c

    Returns weight changes for a set of rate vectors, where weights
    change according to a mapping of the classical STDP rule to rate 
    models.

    Brendan Hasz
    bhasz@brandeis.edu
    http://www.cs.brandeis.edu/~bhasz/main.php
    Brandeis University, Waltham, MA, USA

*/

void rateSTDP(int n, int g, double dt, double R[n][g], double W[][g][g], double W_0[g][g], int W_c[g][g]);

