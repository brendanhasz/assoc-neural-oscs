/*
    STDP_Learned_Synchrony.h

    contains struct definitions for passing data to and from threads

*/

#define NUMTR 4
#define NUMST 200
#define PDRES 100

typedef struct {
    int id;
    int a;
    int b; 
    int numtr;
    int numsteps;
    int pdres;
    double initphdiff;
    double * Wxee_tr;
    double * pd_tr;
} THREAD_3_2_DAT;

