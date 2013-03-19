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
#include "../../fileIO/fileIO.c"

void
rateSTDP(int n, int g, double dt, double R[n][g], 
            double W[][g][g], double W_0[g][g], int W_c[g][g])
{

    int t,i,l;
    int tau, ga, gb;  //indexes: tau, presyn group ind, postsyn g ind
    double sum;  //integration sum
    
    //Weight calculation paramters
    int wid = 100e-3/dt; //go out to 100ms on either side
    int step = 1; //how often to apply plasticity rule
    double tau_w = 10;

    //STDP rule parameters
    double A_n = -.51;
    double A_p = 1.03;
    double tau_n = 34e-3;
    double tau_p = 14e-3;

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
          if ( W[ga][gb] ){ //only alter changeable connections
            sum = 0;
            for (tau=-wid; tau<=0; tau++){ //int post b pre
                sum += A_n*exp(tau/tau_n)*R[t][ga]*R[t+tau][gb]*dt;
            }
            for (tau=0; tau<=wid; tau++){ //int over tau for pre b post
                sum += A_p*exp(-tau/tau_p)*R[t][gb]*R[t-tau][ga]*dt;
            }
            W[i][ga][gb] = W[l][ga][gb] + sum*dt/tau_w; //calc weight diff eq
          } else { //set non-changeable cnxns to constant value
            W[i][ga][gb] = W[l][ga][gb];
          }
        }
      }}
    }

    //Save STDP kernel
    char * fname = "rateSTDP_STDPkernel.dat";
    double kernel[2*wid+1];
    for (tau=0; tau<=wid; tau++){ //int post b pre
        kernel[tau] = A_n*exp(tau/tau_n);
    }
    for (tau=wid; tau<=2*wid; tau++){ //int over tau for pre b post
        kernel[tau] = A_p*exp(-tau/tau_p);
    }
    vsave(2*wid+1, kernel, fname);

}

