/*
Allocates space for a matrix of order n, float type
*/
#include "newmatrix.h"

void newmatrix(float **dest, int m, int n){

	int i;

	dest=(float **)malloc(m*FLOATP_S);
	for(i=0; i<n; i++) dest[i]=(float *)malloc(n*FLOAT_S);
	
	return matrix;
}
