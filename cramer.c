/*
C program that uses Cramer's theorem to calculate the solution of a system of n equations with n variables. To calculate the determinants, Laplace's teorem is used.

Developed by Federico Sandri <uroboro.845@gmail.com>
21/09/11
*/
#include "cramer.h"

float *cramer(float **matrix, int orden){

    int i;
    float *answer=(float *)malloc((orden+1)*FLOAT_S);
    float **temp=newmatrix(orden);
    
    answer[orden]=laplace(matrix, orden);

    for(i=0; i<orden; i++){
        temp=switchcolumn(matrix, i, orden);//switches the variable column with the last column from the original one
        answer[i]=laplace(temp, orden)/answer[orden];
    }

    return answer;
}
