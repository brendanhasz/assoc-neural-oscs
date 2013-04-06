/* tests stderrvec.c
*/

#include <stdio.h>
#include "stderrvec.h"

int main(void){

    double A[3][4];
    A[0][0]=1;  A[0][1]=2;  A[0][2]=3;  A[0][3]=4;
    A[1][0]=0.8;  A[1][1]=1.8;  A[1][2]=2.8;  A[1][3]=3.8;
    A[2][0]=1.2;  A[2][1]=2.2;  A[2][2]=3.2;  A[2][3]=4.2;

    double SE[4];

    stderrvec(3, 4, A, SE);

    printf("SE is: %f\t%f\t%f\t%f\n", SE[0], SE[1], SE[2], SE[3]);

    return 0;

}

