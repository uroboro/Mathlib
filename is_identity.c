#include "is_identity.h"

bool is_identity(void **matrix, int m, int n){

	if(m!=n) return FALSE;

	int i, j;

	for(i=0; i<m; i++)
		for(j=0; j<n; j++){
			if(i==j) if(matrix[i][j]!=1) return FALSE;
			else if(matrix[i][j]!=0) return FALSE;
		}

	return TRUE;
}
