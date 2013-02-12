/*
	EE_Attractor_worker.h

	Stores the struct for passing info to and from the thread

*/

typedef struct {
	int n;
	int no;
	int p;
	int trials;
	double dt;
	int ee_res;
	int ee_a;
	int ee_b;
	int ipd_res;
	double (*lp_rates)[][2];
	double (*ee_vec)[];
	double ei;
	double ie;
	double ii;
	double wW[2][2];
	double (*phdiffs)[ee_res][ipd_res];
} thread_struct;
