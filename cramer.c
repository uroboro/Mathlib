/*
C program that uses Cramer's theorem to calculate the solution of a system of n equations with n variables. To calculate the determinants, Laplace's teorem is used.

Developed by Federico Sandri <uroboro.845@gmail.com>
21/09/11
*/
#include "cramer.h"

float *cramer(float **matrix, int orden){

	int i;
	float **temp;
	float *answer=(float *)malloc((orden+1)*FLOAT_S);

	newmatrix(temp, orden, orden);
	answer[orden]=laplace(matrix, orden, orden);

	for(i=0; i<orden; i++){
		//switches the i column with the last column from the original matrix:
		switchcolumn(temp, matrix, orden, orden, i);
		answer[i]=laplace(temp, orden, orden)/answer[orden];
	}

	return answer;
}
