#include "is_symmetric.h"

bool is_symmetric(float **matrix, int m, int n){

	if(m!=n) return FALSE;

	int i, j;

	for(i=0; i<m; i++)
		for(j=0; j<n; j++)
			if(matrix[i][j]!=matrix[j][i]) return FALSE;

	return TRUE;
}
