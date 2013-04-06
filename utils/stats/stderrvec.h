/* stderrvec.c - find the standard error for a vector of vectors

    Takes a 2d array A[num trials][num measurements per trial] and returns
    a vector with the standard errors for each measurement

*/

void stderrvec(int numtrials, int n, double A[numtrials][n], double OUT[n]);

