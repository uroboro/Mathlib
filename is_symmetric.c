#include "is_symmetric.h"

bool is_symmetric(void **matrix, int n, int m){

	if(n!=m) return FALSE;

	int i, j;

	for(i=0; i<orden; i++)
		for(j=0; j<orden; j++)
			if(matrix[i][j]!=matrix[j][i]) return FALSE;

	return TRUE;
}
