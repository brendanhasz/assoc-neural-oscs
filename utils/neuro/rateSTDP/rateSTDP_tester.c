/*
    rateSTDP_tester.c

    Tests rateSTDP

    Brendan Hasz
    bhasz@brandeis.edu
    http://www.cs.brandeis.edu/~bhasz/main.php
    Brandeis University, Waltham, MA, USA

*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "../get_last_period/get_last_period.h"
#include "../../fileIO/fileIO.h"
#include "../../basic_math/basic_math.h"
#include "../rateN/rateN.h"
#include "rateSTDP.h"

int main(void){
    
    /*
    // Initialize random seed
    time_t randseed = time(NULL);
    srand( randseed );
    printf("Seeded with %lld\n", (long long) randseed);
    */

    //Simulation parameters
    int i,j;  //counters
    int n = 10000;  //timesteps
    double dt = 1e-4;   //timestep duration
    int g = 4;      //number of groups
    int no = 2;     //number of oscillators
    double R[n][g]; //Rate vectors
    double gamma[g];
        for (i=0; i<g; i+=2){
            gamma[i] = 10;      //E cells
            gamma[i+1] = -10;   //I cells
        }
    double tau[g];
        for (i=0; i<g; i+=2){
            tau[i] = 0.002;      //E cells
            tau[i+1] = 0.010;   //I cells
        }

    //Weights
    double wee=2, wei=2.873, wie=-2.873, wii=-2; //Within-oscillator weights
        double wW[2][2];
        wW[0][0]=wee;   wW[0][1]=wei;   //EE    EI
        wW[1][0]=wie;   wW[1][1]=wii;   //IE    II
    double W_0[g][g];
        double xee=0, xei=0, xie=0, xii=0;  //no ss
        assignPingW(no, W_0, wee, wei, wie, wii, xee, xei, xie, xii);
    double W_0i[g][g];
        double ixee=0.15, ixei=0, ixie=0, ixii=0;  //SS in cross osc weights
        assignPingW(no, W_0i, wee, wei, wie, wii, ixee, ixei, ixie, ixii);
    double W_0o[g][g];
        double oxee=0, oxei=1, oxie=0, oxii=0;  //SS in cross osc weights
        assignPingW(no, W_0o, wee, wei, wie, wii, oxee, oxei, oxie, oxii);
    int step = 10;
    double W_t[n/step][g][g];
    int W_c[g][g]; //Which synapses have plasticity?
        for (i=0; i<g; i++){ for (j=0; j<g; j++){  W_c[i][j] = 0; }}
        W_c[0][2] = 1;  W_c[2][0] = 1;  //Only xee ones

    //Get init rates
    double R_i[g];
    int p=1000;
    double rates[p][2];
    get_last_period(&p, rates, wW);

    //Filenames
    char * fname_rI = "rateSTDP_tester_rI.dat";
    char * fname_wI = "rateSTDP_tester_wI.dat";
    char * fname_rO = "rateSTDP_tester_rO.dat";
    char * fname_wO = "rateSTDP_tester_wO.dat";
    
    /******************* SIMULATE INIT IN-PHASE ********************/
    //Get init in-phase rates
    for (i=0; i<g; i+=2){
        R_i[i] = rates[0][0] + gen_rand();
        R_i[i+1] = rates[0][1] + gen_rand();
    }

    //Simulate
    rateN(g, n, R, R_i, W_0, gamma, tau, dt);
    //rateN(g, n, R, R_i, W_0i, gamma, tau, dt);
    //rateN(g, n, R, R_i, W_0o, gamma, tau, dt);
    asave(n, g, R, fname_rI);

    //Find weight change over time
    rateSTDP(n, g, dt, R, W_t, W_0, W_c);
    //rateSTDP(n, g, dt, R, W_t, W_0i, W_c);
    //rateSTDP(n, g, dt, R, W_t, W_0o, W_c);
    
    //convert weights -> 2d matrix + save
    double Wt_2d[n/step][2];
    for (i=0; i<n/step; i++){
        Wt_2d[i][0] = W_t[i][0][2];
        Wt_2d[i][1] = W_t[i][2][0];
    }
    asave(n/step, no, Wt_2d, fname_wI);
    


    /******************* SIMULATE INIT OUT-PHASE ********************/
    //Get init out-phase rates
    R_i[2] = rates[p/2][0] + gen_rand();
    R_i[3] = rates[p/2][1] + gen_rand();

    //Simulate
    rateN(g, n, R, R_i, W_0, gamma, tau, dt);
    //rateN(g, n, R, R_i, W_0i, gamma, tau, dt);
    //rateN(g, n, R, R_i, W_0o, gamma, tau, dt);
    asave(n, g, R, fname_rO);

    //Find weight change over time
    rateSTDP(n, g, dt, R, W_t, W_0, W_c);
    //rateSTDP(n, g, dt, R, W_t, W_0i, W_c);
    //rateSTDP(n, g, dt, R, W_t, W_0o, W_c);
    
    //convert weights -> 2d matrix + save
    for (i=0; i<n/step; i++){
        Wt_2d[i][0] = W_t[i][0][2];
        Wt_2d[i][1] = W_t[i][2][0];
    }
    asave(n/step, no, Wt_2d, fname_wO);


    return 0;

}

