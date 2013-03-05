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

#include "../../utils/vectors/linspace.h"
#include "../../utils/neuro/get_last_period/get_last_period.h"
#include "../../utils/neuro/pingRateN/pingRateN.h"
#include "../../utils/sig_proc/phdiff2.h"
#include "../../utils/sig_proc/l2peaks.h"
#include "../../utils/sig_proc/amp.h"
#include "../../utils/graphing/matrix4dTo2d.h"
#include "../../utils/fileIO/fileIO.h"

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
double wW[2][2];     //Synaptic weights
	wW[0][0]=2;		wW[0][1]=2.873;	//EE	EI
	wW[1][0]=-2.873;	wW[1][1]=-2;	//IE	II


//DETERMINE INITIAL RATES
//Get last period
int p=1000;
double lp_rates[p][2];
get_last_period(&p, lp_rates, wW);
double R_i_IN[no][2], R_i_OUT[no][2];
//Initially In-phase
R_i_IN[0][0] = lp_rates[0][0];	R_i_IN[0][1] = lp_rates[0][1]; //osc1
R_i_IN[1][0] = lp_rates[0][0];	R_i_IN[1][1] = lp_rates[0][1]; //osc2
//Initially Out-of-phase
R_i_OUT[0][0] = lp_rates[0][0];	R_i_OUT[0][1] = lp_rates[0][1]; //osc1
R_i_OUT[1][0]=lp_rates[p/2][0];	R_i_OUT[1][1]=lp_rates[p/2][1]; //osc2


//Storage arrays
double Re_IN[n][no], Re_OUT[n][no];
double pds[no][no];

double phdiff_IN[ee_res][ii_res][ei_res][ie_res];
double phdiff_OUT[ee_res][ii_res][ei_res][ie_res];
double phdiff_DIFF[ee_res][ii_res][ei_res][ie_res];

double freq_IN[ee_res][ii_res][ei_res][ie_res];
double freq_OUT[ee_res][ii_res][ei_res][ie_res];
double freq_DIFF[ee_res][ii_res][ei_res][ie_res];
	int thel2[2];
	double Re_IN_o1[n], Re_OUT_o1[n];

double amp_IN[ee_res][ii_res][ei_res][ie_res];
double amp_OUT[ee_res][ii_res][ei_res][ie_res];
double amp_DIFF[ee_res][ii_res][ei_res][ie_res];
	


/******************** LOOP THROUGH PARAM SPACE ********************/
//counters
int ee, ii, ei, ie, i;

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

		
		//Get single osc's E vector for freq + amp calculations
		for (i=0; i<n; i++){ //copy 1st groups E vec into own vec
			Re_IN_o1[i]=Re_IN[i][0];
			Re_OUT_o1[i]=Re_OUT[i][0];
		}


		//FIND FREQUENCY
		//Frequency: INIT-IN
		l2peaks(n, Re_IN_o1, thel2); //get last 2 peaks
		freq_IN[ee][ii][ei][ie] = 10000/(thel2[1] - thel2[0]);
		
		//Frequency: INIT-OUT
		l2peaks(n, Re_OUT_o1, thel2); //get last 2 peaks
		freq_OUT[ee][ii][ei][ie] = 10000/(thel2[1] - thel2[0]);

		//Frequency: DIFF (IN-OUT)
		freq_DIFF[ee][ii][ei][ie] = freq_IN[ee][ii][ei][ie] - freq_OUT[ee][ii][ei][ie];



		//FIND AMPLITUDE
		//Amplitude: INIT-IN
		amp_IN[ee][ii][ei][ie] = amp(n,Re_IN_o1);
		
		//Amplitude: INIT-OUT
		amp_OUT[ee][ii][ei][ie] = amp(n,Re_OUT_o1);

		//Amplitude: DIFF (IN-OUT)
		amp_DIFF[ee][ii][ei][ie]  = amp_IN[ee][ii][ei][ie] - amp_OUT[ee][ii][ei][ie];
		
		//Print stuff as we loop through
//		printf("ee=%f, ii=%f, ei=%f, ie=%f:\n", ee_vec[ee], ii_vec[ii], ei_vec[ei], ie_vec[ie]);
//		printf("\tPD_IN=%f\tPD_OUT=%f\tPD_DIFF%f\n", phdiff_IN[ee][ii][ei][ie], phdiff_OUT[ee][ii][ei][ie], phdiff_DIFF[ee][ii][ei][ie]);
//		printf("\tFREQ_IN=%f\tFREQ_OUT=%f\tFREQ_DIFF%f\n", freq_IN[ee][ii][ei][ie], freq_OUT[ee][ii][ei][ie], freq_DIFF[ee][ii][ei][ie]);
//		printf("\tAMP_IN=%f\tAMP_OUT=%f\tAMP_DIFF%f\n", amp_IN[ee][ii][ei][ie], amp_OUT[ee][ii][ei][ie], amp_DIFF[ee][ii][ei][ie]);
	  }
		printf("%f percent done\n", 100*((double) (ee*ii_res*ei_res*ie_res+ii*ei_res*ie_res+ei*ie_res+ie+1))/((double)(ee_res*ii_res*ei_res*ie_res)));
	}
  }
}



/************************** SAVE DATA ******************************/
//PHASE DIFFERENCES
//2d matrixes in which to put 4D data
double phdiff_IN_2d[ee_res*ei_res][ii_res*ie_res];
double phdiff_OUT_2d[ee_res*ei_res][ii_res*ie_res];
double phdiff_DIFF_2d[ee_res*ei_res][ii_res*ie_res];

//Init-in
matrix4dTo2d(ee_res, ii_res, ei_res, ie_res, phdiff_IN, phdiff_IN_2d);
char * fname_phdiff_IN = "Phdiff_init_IN.dat";
asave(ee_res*ei_res, ii_res*ie_res, phdiff_IN_2d, fname_phdiff_IN); 
printf("Data saved as %s\n", fname_phdiff_IN);

//Init-out
matrix4dTo2d(ee_res, ii_res, ei_res, ie_res, phdiff_OUT, phdiff_OUT_2d);
char * fname_phdiff_OUT = "Phdiff_init_OUT.dat";
asave(ee_res*ei_res, ii_res*ie_res, phdiff_OUT_2d, fname_phdiff_OUT); 
printf("Data saved as %s\n", fname_phdiff_OUT);

//Difference
matrix4dTo2d(ee_res, ii_res, ei_res, ie_res, phdiff_DIFF, phdiff_DIFF_2d);
char * fname_phdiff_DIFF = "Phdiff_DIFF.dat";
asave(ee_res*ei_res, ii_res*ie_res, phdiff_DIFF_2d, fname_phdiff_DIFF);
printf("Data saved as %s\n", fname_phdiff_DIFF);



//FREQUENCIES
//2d matrixes in which to put 4D data
double freq_IN_2d[ee_res*ei_res][ii_res*ie_res];
double freq_OUT_2d[ee_res*ei_res][ii_res*ie_res];
double freq_DIFF_2d[ee_res*ei_res][ii_res*ie_res];

//Init-in
matrix4dTo2d(ee_res, ii_res, ei_res, ie_res, freq_IN, freq_IN_2d);
char * fname_freq_IN = "Freq_init_IN.dat";
asave(ee_res*ei_res, ii_res*ie_res, freq_IN_2d, fname_freq_IN); 
printf("Data saved as %s\n", fname_freq_IN);

//Init-out
matrix4dTo2d(ee_res, ii_res, ei_res, ie_res, freq_OUT, freq_OUT_2d);
char * fname_freq_OUT = "Freq_init_OUT.dat";
asave(ee_res*ei_res, ii_res*ie_res, freq_OUT_2d, fname_freq_OUT); 
printf("Data saved as %s\n", fname_freq_OUT);

//Difference
matrix4dTo2d(ee_res, ii_res, ei_res, ie_res, freq_DIFF, freq_DIFF_2d);
char * fname_freq_DIFF = "Freq_DIFF.dat";
asave(ee_res*ei_res, ii_res*ie_res, freq_DIFF_2d, fname_freq_DIFF);
printf("Data saved as %s\n", fname_freq_DIFF);



//PHASE DIFFERENCES
//2d matrixes in which to put 4D data
double amp_IN_2d[ee_res*ei_res][ii_res*ie_res];
double amp_OUT_2d[ee_res*ei_res][ii_res*ie_res];
double amp_DIFF_2d[ee_res*ei_res][ii_res*ie_res];

//Init-in
matrix4dTo2d(ee_res, ii_res, ei_res, ie_res, amp_IN, amp_IN_2d);
char * fname_amp_IN = "Amp_init_IN.dat";
asave(ee_res*ei_res, ii_res*ie_res, amp_IN_2d, fname_amp_IN);
printf("Data saved as %s\n", fname_amp_IN);

//Init-out
matrix4dTo2d(ee_res, ii_res, ei_res, ie_res, amp_OUT, amp_OUT_2d);
char * fname_amp_OUT = "Amp_init_OUT.dat";
asave(ee_res*ei_res, ii_res*ie_res, amp_OUT_2d, fname_amp_OUT);
printf("Data saved as %s\n", fname_amp_OUT);

//Difference
matrix4dTo2d(ee_res, ii_res, ei_res, ie_res, amp_DIFF, amp_DIFF_2d);
char * fname_amp_DIFF = "Amp_DIFF.dat";
asave(ee_res*ei_res, ii_res*ie_res, amp_DIFF_2d, fname_amp_DIFF);
printf("Data saved as %s\n", fname_amp_DIFF);



printf("DONE!\n");

return 0;

}
