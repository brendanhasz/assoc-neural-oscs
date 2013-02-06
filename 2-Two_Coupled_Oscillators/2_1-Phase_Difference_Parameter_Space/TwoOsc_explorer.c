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

//INITIALIZE RESOLUTION AND BOUNDARIES
double dt = 0.0001;  //100 us
int i;

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



double init_rs[]
//TODO: get initial rate vectors



int n = 9999;
int g = 2;
double Re[n][g];
double pds[g][g];
double initIN[ee_res][ii_res][ei_res][ie_res];
double initOUT[ee_res][ii_res][ei_res][ie_res];
double DDpsi[ee_res][ii_res][ei_res][ie_res];
	


/******************** LOOP THROUGH PARAM SPACE ********************/
//loop thru param space
int ee, ii, ei, ie;

for (ee=0; ee<ee_res; ee++){
  for (ii=0; ii<ii_res; ii++){
	for (ei=0; ei<ei_res; ei++){
	  for (ie=0; ie<ie_res; ie++){
		
		//Simulate starting IN-phase
		PINGrate2(n, Re, R_i_IN, ee_vec[ee], ei_vec[ei], ie_vec[ie], ii_vec[ii], wW, dt);
		phdiff2(n, g, Re, pds);
		initIN[ee][ii][ei][ie] = pds[0][1];
		
		//Simulate starting OUT-of-phase
		PINGrate2(n, Re, R_i_OUT, ee_vec[ee], ei_vec[ei], ie_vec[ie], ii_vec[ii], wW, dt);
		phdiff2(n, g, Re, pds);
		initOUT[ee][ii][ei][ie] = pds[0][1];
		
		//Find D phase difference
		DDpsi[ee][ii][ei][ie] = initIN[ee][ii][ei][ie] - initOUT[ee][ii][ei][ie];
		if ( DDpsi[ee][ii][ei][ie] != DDpsi[ee][ii][ei][ie] ){ //check for NaN
			DDpsi[ee][ii][ei][ie] = 0;  //ignore wild behavior
		} 
		
		//Find frequency
		
		//Find Amplitude
		
		
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
