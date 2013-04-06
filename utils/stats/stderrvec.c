/* stderrvec.c - find the standard error for a vector of vectors

    Takes a 2d array A[num trials][num measurements per trial] and returns
    a vector with the standard errors for each measurement

*/

#include <math.h>
#include <stdio.h>

void stderrvec(int numtrials, int n, double A[numtrials][n], double SE[n]){

    int i, j;
    double thesum, themean;

    for (i=0; i<n; i++){  //for each measurement, find stderr over trials
        //find mean
        thesum = 0;
        for (j=0; j<numtrials; j++){ //find mean
            thesum += A[j][i];
        }        
        themean = thesum/numtrials;
        printf("mean is %f\n", themean);
        //find stderr
        thesum = 0;
        for (j=0; j<numtrials; j++){ //Sum squared error
            thesum += (A[j][i]-themean)*(A[j][i]-themean);
        }
        SE[i] = sqrt(thesum/(numtrials-1))/sqrt(numtrials);
    }

}

