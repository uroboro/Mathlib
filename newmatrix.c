/*
Allocates space for a matrix of order n
*/
#include "newmatrix.h"

float **newmatrix(int orden){

	int i;
	float **matrix=(float **)malloc(orden*FLOATP_S);
	for(i=0; i<orden; i++) matrix[i]=(float *)malloc(orden*FLOAT_S);
	
	return matrix;
}
