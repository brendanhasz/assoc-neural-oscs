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

#include <stdio.h>
#include <math.h>
#include "../../fileIO/fileIO.h"

#ifndef MAX
#define MAX(x,y) ( x > y ? x : y )
#endif

void
rateSTDP(int n, int g, double dt, double R[n][g], 
            double W[][g][g], double W_0[g][g], int W_c[g][g])
{

    int t,i,l;
    int tau, ga, gb;  //indexes: tau, presyn group ind, postsyn g ind
    double sum;  //integration sum
    
    //Weight calculation paramters
    int wid = 100e-3/dt; //go out to 100ms on either side
    int step = 10; //how often to apply plasticity rule
    //double tau_w = 10; //Weight change time constant used for pattern separation
    double tau_w = 10; //Weight change time constant

    //STDP rule parameters
    double A_n = -.51;
    //double A_p = 1.13; //1.03 in paper, had to use 1.13
    double A_p = 1.03; //1.03 in paper, had to use 1.13
    double tau_n = 0.036;
    double tau_p = 0.014;
    double tau_d = 2e-3; //nonexact kernel, as suggested by Knoblauch
    double tau_pot = 1e-3; //nonexact kernel in the potentiation direction
    //double tau_d = 4e-3; //nonexact kernel, as suggested by Knoblauch
    //double tau_pot = 2.5e-3; //nonexact kernel in the potentiation direction
    int ne_start = wid-tau_d/dt;
    int ne_end = wid + tau_pot/dt;
    int ne_diff = ne_end-ne_start;

    //Create stdp kernel
    double kernel[2*wid+1];
    for (tau=0; tau<=wid; tau++){ //int post b pre
        kernel[tau] = A_n*exp((-0.1+tau*dt)/tau_n);
    }
    for (tau=wid; tau<=2*wid; tau++){ //int over tau for pre b post
        kernel[tau] = A_p*exp(-dt*(tau-wid)/tau_p);
    }
    for (tau=ne_start; tau<ne_end; tau++){
        kernel[tau] = kernel[ne_start]+(kernel[ne_end]-kernel[ne_start])*(tau-ne_start)/ne_diff;
    }

    //Initialize W[0][g][g] to W_0[g][g]
    for (ga=0; ga<g; ga++){ 
        for (gb=0; gb<g; gb++){
            W[0][ga][gb] = W_0[ga][gb];
        }
    }

    for (t=step; t<n; t+=step){ //integrate over all t
      i = t/step; //this timestep for dw
      l = i-1; //last timestep
      for (ga=0; ga<g; ga++){ for (gb=0; gb<g; gb++){ //for all cnxns
        if ( t-wid < 0 || t+wid >= n ){ //check bounds!
          W[i][ga][gb] = W[l][ga][gb]; //set to last known value @ bounds
        } else { //no boundary troubles
          if ( W_c[ga][gb] ){ //only alter changeable connections
          //if ( W[ga][gb] ){ //only alter changeable connections
            sum = 0;
            for (tau=0; tau<=wid; tau++){ //int post b pre
                sum += kernel[tau]*R[t][ga]*R[t+tau-wid][gb]*dt;
            }
            for (tau=0; tau<=wid; tau++){ //int over tau for pre b post
                sum += kernel[tau+wid]*R[t][gb]*R[t-tau][ga]*dt;
            }
            //W[i][ga][gb] = MAX(0, W[l][ga][gb] + sum*dt/tau_w); //calc weight diff eq
            W[i][ga][gb] = W[l][ga][gb] + sum*dt/tau_w; //calc weight diff eq
          } else { //set non-changeable cnxns to constant value
            W[i][ga][gb] = W[l][ga][gb];
          }
        }
      }}
    }

    //Save STDP kernel
    /*
    char * fname = "rateSTDP_STDPkernel.dat";
    vsave(2*wid+1, kernel, fname);
    */

}

