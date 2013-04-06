/*
    STDP_Learned_Synchrony.h

    contains struct definitions for passing data to and from threads

*/

#define NUMTR 10
#define NUMST 90
#define PDRES 100

typedef struct {
    int id;
    int a;
    int b; 
    int numtr;
    int numsteps;
    int pdres;
    double initphdiff;
    //double * Wxee_tr[NUMTR][2][NUMST];
    //double * Wxee_tr[NUMTR*2*NUMST];
    double * Wxee_tr;
    //double * pd_tr[NUMTR][PDRES][NUMST];
    //double * pd_tr[NUMTR*PDRES*NUMST];
    double * pd_tr;
} THREAD_2_4_DAT;

