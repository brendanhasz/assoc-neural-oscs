/*
	TwoOsc_explorer - Explores X-oscillator syn. weight param space

	Finds phase differences, rates, amplitudes, etc	across
		cross-oscillator synaptic weight parameter space for weights
		between two coupled oscillators.  Uses the rate model in rateN.
		Outputs data to files.  4-dimensional data is flattened and 
		saved as 2D plots.
	
	OUTPUT FILES
	* Dpsi_SS_initIN.dat	Steady-state phase diff, started IN-phase
	* Dpsi_SS_initOUT.dat	S.S. phase diff, started OUT-of-phase
	* Dpsi_SS_diff.dat		Difference between S.S. ph. diffs: IN-OUT
	* Freq_initIN.dat		Oscillation freq, started IN-phase
	* Freq_initOUT.dat		Oscillation freq, started OUT-of-phase
	* Freq_diff.dat			Diff between osc freqs, IN-OUT
	* Amp_initIN.dat		Osc. amplitude, started IN-phase
	* Amp_initOUT.dat		Osc. amplitude, started OUT-of-phase
	* Amp_diff.dat			Diff between osc. amplitudes, IN-OUT
	

	Copyright 2012
	Brendan Hasz
	bhasz@brandeis.edu
	www.cs.brandeis.edu/~bhasz/main.php
	Brandeis University, Waltham, MA, USA

	This work is licensed under a Creative Commons NonCommercial 3.0 
	Unported License.  You can use it and modify it any way you like 
	as long as you aren't commercially making money off it - if you
	are, I want some too!

*/

#include <stdio.h>
#include "../utils/utils.h"

int main(void)
{
	
/******************** INITIALIZE SIMULATION ***********************/

double dt = 0.0001;	//Timestep duration - 100 us
int n = 9999;		//Number of timesteps to simulate
int no = 2;			//Number of oscillators

//BETWEEN-OSCILLATOR SYNAPTIC STRENGTH
//EE
int ee_res = 5;
double ee_min = 0;
double ee_max = .1;
//II
int ii_res = 5;
double ii_min = -1;
double ii_max = 0;
//EI
int ei_res = 30;
double ei_min = 0;
double ei_max = 1;
//IE
int ie_res = 30;
double ie_min = -1;
double ie_max = 0;

double ee_vec[ee_res], ii_vec[ii_res], ei_vec[ei_res], ie_vec[ie_res];
linspace(ee_min, ee_max, ee_res, ee_vec);
linspace(ii_min, ii_max, ii_res, ii_vec);
linspace(ei_min, ei_max, ei_res, ei_vec);
linspace(ie_min, ie_max, ie_res, ie_vec);


//Within-oscillator synaptic strength
double wW[g][g];     //Synaptic weights
	wW[0][0]=2;			wW[0][1]=2.873;	//EE	EI
	wW[1][0]=-2.873;	wW[1][1]=-2;	//IE	II


//DETERMINE INITIAL RATES
//Get last period
int p=1000;
double lp_rates[p][2];
get_last_period(&p, lp_rates, W);
double R_i_IN[no][2], R_i_OUT[no][2];
//Initially In-phase
R_i_IN[0][0] = lp_rates[0][0];	R_i_IN[0][1] = lp_rates[0][1]; //osc1
R_i_IN[1][0] = lp_rates[0][0];	R_i_IN[1][1] = lp_rates[0][1]; //osc2
//Initially Out-of-phase
R_i_OUT[0][0] = lp_rates[0][0];	R_i_OUT[0][1] = lp_rates[0][1]; //osc1
R_i_OUT[1][0] lp_rates[p/2][0];	R_i_OUT[1][1]=lp_rates[p/2][1]; //osc2


//Storage arrays
double Re_IN[n][no], Re_OUT[n][no];
double pds[no][no];

double phdiff_IN[ee_res][ii_res][ei_res][ie_res];
double phdiff_OUT[ee_res][ii_res][ei_res][ie_res];
double phdiff_DIFF[ee_res][ii_res][ei_res][ie_res];

double freq_IN[ee_res][ii_res][ei_res][ie_res];
double freq_OUT[ee_res][ii_res][ei_res][ie_res];
double freq_DIFF[ee_res][ii_res][ei_res][ie_res];

double amp_IN[ee_res][ii_res][ei_res][ie_res];
double amp_OUT[ee_res][ii_res][ei_res][ie_res];
double amp_DIFF[ee_res][ii_res][ei_res][ie_res];
	


/******************** LOOP THROUGH PARAM SPACE ********************/
//counters
int ee, ii, ei, ie;

for (ee=0; ee<ee_res; ee++){
  for (ii=0; ii<ii_res; ii++){
	for (ei=0; ei<ei_res; ei++){
	  for (ie=0; ie<ie_res; ie++){
		
		//GET RATE VECTORS
		//Get rate vectors for init-IN
		pingRateN(n, no, Re_IN, R_i_IN, ee_vec[ee], ei_vec[ei], ie_vec[ie], ii_vec[ii], wW, dt);
		
		//Get rate vectors for init-OUT
		pingRateN(n, no, Re_OUT, R_i_OUT, ee_vec[ee], ei_vec[ei], ie_vec[ie], ii_vec[ii], wW, dt);
		
		
		
		//FIND PHASE DIFFS
		//Phase diff: INIT-IN
		phdiff2(n, no, Re_IN, pds);
		phdiff_IN[ee][ii][ei][ie] = pds[0][1];
		
		//Phase diff: INIT-OUT
		phdiff2(n, no, Re_OUT, pds);
		phdiff_OUT[ee][ii][ei][ie] = pds[0][1];

		//Phase diff: DIFF (IN-OUT)
		phdiff_DIFF[ee][ii][ei][ie] = phdiff_IN[ee][ii][ei][ie] - phdiff_OUT[ee][ii][ei][ie];



		//FIND FREQUENCY
		double thel2[2];
		//TODO: copy 1st oscs E rate vec from Re_IN and Re_OUT vecs into own vecs (Re_IN_o1, etc)
		double Re_IN_o1[n], Re_OUT_o1[n];
		//Frequency: INIT-IN
		l2peaks(n, Re_IN_o1, thel2); //get last 2 peaks
		freq_IN[ee][ii][ei][ie] = 10000/(tl2p[1] - tl2p[0]);
		
		//Frequency: INIT-OUT
		l2peaks(n, Re_OUT_o1, thel2); //get last 2 peaks
		freq_OUT[ee][ii][ei][ie] = 10000/(tl2p[1] - tl2p[0]);

		//Frequency: DIFF (IN-OUT)
		freq_DIFF[ee][ii][ei][ie] = freq_IN[ee][ii][ei][ie] - req_OUT[ee][ii][ei][ie];



		//FIND AMPLITUDE
		//Amplitude: INIT-IN
		amp_IN[ee][ii][ei][ie] = amp(n,Re_IN);
		
		//Amplitude: INIT-OUT
		amp_OUT[ee][ii][ei][ie] = amp(n,Re_OUT);

		//Amplitude: DIFF (IN-OUT)
		amp_DIFF[ee][ii][ei][ie]  = amp_IN[ee][ii][ei][ie] - amp_OUT[ee][ii][ei][ie];
		
		
		/* old stuff for reference
		pingRateN(n, no, Re_IN, R_i_IN, ee_vec[ee], ei_vec[ei], ie_vec[ie], ii_vec[ii], wW, dt);

		//Simulate starting IN-phase
		PINGrate2(n, Re_IN, R_i_IN, ee_vec[ee], ei_vec[ei], ie_vec[ie], ii_vec[ii], wW, dt);
		phdiff2(n, no, Re, pds);
		initIN[ee][ii][ei][ie] = pds[0][1];
		
		//Simulate starting OUT-of-phase
		PINGrate2(n, Re_OUT, R_i_OUT, ee_vec[ee], ei_vec[ei], ie_vec[ie], ii_vec[ii], wW, dt);
		phdiff2(n, no, Re, pds);
		initOUT[ee][ii][ei][ie] = pds[0][1];
		
		//Find D phase difference
		DDpsi[ee][ii][ei][ie] = initIN[ee][ii][ei][ie] - initOUT[ee][ii][ei][ie];
		if ( DDpsi[ee][ii][ei][ie] != DDpsi[ee][ii][ei][ie] ){ //check for NaN
			DDpsi[ee][ii][ei][ie] = 0;  //ignore wild behavior
		} 
		
		//Find frequency
		
		//Find Amplitude
		*/
		
		printf("ee=%f, ii=%f, ei=%f, ie=%f: INpd=%f, OUTpd=%f, DDpsi=%f\n", ee_vec[ee], ii_vec[ii], ei_vec[ei], ie_vec[ie], initIN[ee][ii][ei][ie], initOUT[ee][ii][ei][ie], DDpsi[ee][ii][ei][ie]);
		
	  }
	}
  }
}



/************************** SAVE DATA ******************************/
//put 4d initIN, initOUT, and DDpsi matrixes into 2d matrixes
double initIN_2d[ee_res*ei_res][ii_res*ie_res];
double initOUT_2d[ee_res*ei_res][ii_res*ie_res];
double DDpsi_2d[ee_res*ei_res][ii_res*ie_res];

matix4dTo2d(ee_res, ii_res, ei_res, ie_res, initIN, initIN_2d);
char * filenameIN = "find_DDpsi_initIN.dat";
asave2(ee_res*ei_res, ii_res*ie_res, initIN_2d, filenameIN); //Save data
printf("Data saved as %s\n", filenameIN);

matix4dTo2d(ee_res, ii_res, ei_res, ie_res, initOUT, initOUT_2d);
char * filenameOUT = "find_DDpsi_initOUT.dat";
asave2(ee_res*ei_res, ii_res*ie_res, initOUT_2d, filenameOUT); //Save data
printf("Data saved as %s\n", filenameOUT);

matix4dTo2d(ee_res, ii_res, ei_res, ie_res, DDpsi, DDpsi_2d);
char * filenameDDpsi = "find_DDpsi_DDpsi.dat";
asave2(ee_res*ei_res, ii_res*ie_res, DDpsi_2d, filenameDDpsi); //Save data
printf("Data saved as %s\n", filenameDDpsi);



printf("Done!\n");

return 0;

}
