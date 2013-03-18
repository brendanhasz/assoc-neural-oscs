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

#include <math.h>

void
rateSTDPmap(int n, int g, double dt, double R[n][g], 
            double W[][g][g], double W_0[g][g], int W_c[g][g])
{

    int t, tau, ga, gb;  //indexes: time, tau, presyn group ind, postsyn g ind
    double sum;  //integration sum
    
    //Weight calculation paramters
    int width = 100e-3/dt; //go out to 100ms on either side
    int step = 1; //how often to apply plasticity rule
    double tau_w = 

    //STDP rule parameters
    double A_n = -.51;
    double A_p = 1.03;
    double tau_n = 34e-3;
    double tau_p = 14e-3;

    //Save STDP kernel
    //TODO

    //Initialize W[0][g][g] to W_0[g][g]
    //TODO

    for (t=wid; t<n-wid; t+=step){ //integrate over all t
        l = t-1; //last timestep
        i = (t-wid)/step; //this timestep for dw
        for (ga=0; ga<g; ga++){ for (gb=0; gb<g; gb++){ //for all cnxns
        if ( W[ga][gb] ){ //only alter changeable connections
            sum = 0;
            for (tau=-wid; tau<=0; tau++){ //int post b pre
                sum += A_n*exp(tau/tau_n)*R[t][ga]*R[t+tau][gb]*dt;
            }
            for (tau=0; tau<=wid; tau++){ //int over tau for pre b post
                sum += A_p*exp(-tau/tau_p)*R[t][gb]*R[t-tau][ga]*dt;
            }
            W[i][ga][gb] = W[l][ga][gb] + sum*dt/tau_w; //calc weight diff eq
        }}}
    }

}

