#include "transpose.h"

void transpose(void **dest, void **ori, int n, int m){

	int i, j;

	for(i=0; i<n; i++)
		for(j=0; j<m; j++)
			dest[i][j]=ori[j][i];

	return;
}

