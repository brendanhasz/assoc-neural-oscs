/* pat_rec_tester.c

    tester for the "pattern recognition" algorithm in 
    Pattern_Completion_worker.c

*/

#include <stdio.h>
#include <math.h>

//Define the "within" function
#ifndef WI
#define WI(x,v,t) ( ((x<v+t) && (x>v-t)) ? 1 : 0 )
#endif

int main(void){

    int no=5, gr;
    double withresh = 0.5;
    double pat_score;
    double diff_train, diff_ss;

    double train_pat[2][no];
        train_pat[0][0] = 0;
        train_pat[0][1] = 0;
        train_pat[0][2] = 0;
        train_pat[0][3] = M_PI;
        train_pat[0][4] = M_PI;
        //****************
        train_pat[1][0] = M_PI;
        train_pat[1][1] = M_PI;
        train_pat[1][2] = 0;
        train_pat[1][3] = 0;
        train_pat[1][4] = 0;

    double ss_pat_good[no];
        ss_pat_good[0] = 0;
        ss_pat_good[1] = 0;
        ss_pat_good[2] = 0;
        ss_pat_good[3] = M_PI;
        ss_pat_good[4] = M_PI;

    double ss_pat_bad[no];
        ss_pat_bad[0] = 0;
        ss_pat_bad[1] = M_PI;
        ss_pat_bad[2] = 0;
        ss_pat_bad[3] = M_PI;
        ss_pat_bad[4] = M_PI;

    double ss_pat_ter[no];
        ss_pat_ter[0] = M_PI;
        ss_pat_ter[1] = M_PI;
        ss_pat_ter[2] = M_PI;
        ss_pat_ter[3] = 0;
        ss_pat_ter[4] = 0;


    //Compare train patt to good pat
    printf("Compare train patt to good pat:\n");
    pat_score = 0;
    for (gr=0; gr<no; gr++){
        diff_train = train_pat[0][gr]-train_pat[0][0];
        diff_ss = ss_pat_good[gr]-ss_pat_good[0];
        printf("diff_train: %f\tdiff_ss: %f\n", diff_train, diff_ss);
        if ( WI(diff_train,0,withresh) == WI(diff_ss,0,withresh) ){
            printf("\tmatch in ind: %d !\n", gr);
            pat_score++;
        }
    }
    pat_score = pat_score/no;
    printf("pat_score: %f\n\n\n", pat_score);



    //Compare train patt to good pat
    printf("Compare train patt to bad pat:\n");
    pat_score = 0;
    for (gr=0; gr<no; gr++){
        diff_train = train_pat[0][gr]-train_pat[0][0];
        diff_ss = ss_pat_bad[gr]-ss_pat_bad[0];
        printf("diff_train: %f\tdiff_ss: %f\n", diff_train, diff_ss);
        if ( WI(diff_train,0,withresh) == WI(diff_ss,0,withresh) ){
            printf("\tmatch in ind: %d !\n", gr);
            pat_score++;
        }
    }
    pat_score = pat_score/no;
    printf("pat_score: %f\n\n\n", pat_score);



    //Compare train patt to good pat
    printf("Compare train patt to terrible pat:\n");
    pat_score = 0;
    for (gr=0; gr<no; gr++){
        diff_train = train_pat[0][gr]-train_pat[0][0];
        diff_ss = ss_pat_ter[gr]-ss_pat_ter[0];
        printf("diff_train: %f\tdiff_ss: %f\n", diff_train, diff_ss);
        if ( WI(diff_train,0,withresh) == WI(diff_ss,0,withresh) ){
            printf("\tmatch in ind: %d !\n", gr);
            pat_score++;
        }
    }
    pat_score = pat_score/no;
    printf("pat_score: %f\n\n\n", pat_score);



    return 0;

}

