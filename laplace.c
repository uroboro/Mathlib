#include "laplace.h"

float laplace(float **matrix, int orden){

	int n;
	float c=0;
	switch(orden){
	case 1:
		c=matrix[0][0];
		free(matrix);
		break;
	case 2:
		c=det(matrix);
		break;
	default:
		for(n=0; n<orden; n++){
			float **submatrix=mksubmatrix(matrix, orden, n);
			c+=matrix[0][n]*onepow(n)*laplace(submatrix, orden-1);
			free(submatrix);
		}
	}

	return c;
}
