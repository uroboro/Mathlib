#include "newidentity.h"

void newidentity(float **dest, int m, int n){

	if(m!=n) return;

	int i, j;

	for(i=0; i<m; i++)
		for(j=0; j<n; j++){
			if(i==j) dest[i][j]=1.0;
			else dest[i][j]=0.0;
		}

	return;
}
