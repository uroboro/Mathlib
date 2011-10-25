/*
Given a matrix of n by n+1, a square matrix of order orden is created.
This function switches the pos column with the n column.
*/
#include "switchcolumn.h"

void switchcolumn(void **dest, void **ori, int m, int n, int pos){

	if(m+1!=n) return;

	int i, j;

	for(i=0; i<m; i++)
		for(j=0; j<m; j++){
			if(j==pos) dest[i][j]=ori[i][n];
			else dest[i][j]=ori[i][j];
		}

	return;
}
