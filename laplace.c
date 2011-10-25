#include "laplace.h"

float laplace(float **matrix, int m, int n){

	if(m!=n) return;

	int i;
	float c=0;
	float **submatrix;

	switch(m){
	case 1:
		c=matrix[0][0];
		free(matrix);
		break;
	case 2:
		c=det(matrix);
		break;
	default:
		for(i=0; i<m; i++){
			newmatrix(submatrix, m, n);
			mksubmatrix(submatrix, matrix, m, n, i);
			c+=matrix[0][i]*onepow(i)*laplace(submatrix, m--, n--);
			free(submatrix);
		}
	}

	return c;
}
