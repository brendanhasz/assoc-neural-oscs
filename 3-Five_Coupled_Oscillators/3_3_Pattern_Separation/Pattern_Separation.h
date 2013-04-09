/*
    Pattern_Completion.h

    contains struct definitions for passing data to and from threads

*/

#define NUMTR 4
#define NUMST 200
#define PERCRES 50 //should theoretically be higher than 100...

typedef struct {
    int id;
    int a;
    int b; 
    int numtr;
    int numsteps;
    int percres;
    double * perccorr; //percent correct for this trial+step
} THREAD_3_2_DAT;

