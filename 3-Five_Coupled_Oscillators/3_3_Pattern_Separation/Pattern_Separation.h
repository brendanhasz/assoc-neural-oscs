/*
    Pattern_Completion.h

    contains struct definitions for passing data to and from threads

*/

#define NUMTR 40 
#define NUMST 140 //should be from 50-200
#define PERCRES 10 //should theoretically be higher than 100...

typedef struct {
    int id;
    int a;
    int b; 
    int numtr;
    int numsteps;
    int percres;
    double * perccorr; //percent correct for this trial+step
    double * perccorr2; //percent correct for this trial+step
} THREAD_3_2_DAT;

