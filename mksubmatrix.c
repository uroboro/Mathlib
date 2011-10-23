/*
This function will create a new matrix which is done by subtracting the first row of the parent matrix and subtracting the n column.
*/
#include "mksubmatrix.h"

float **mksubmatrix(float **matrix, int orden, int n){

	int mi, mj, si, sj;
	float **submatrix=newmatrix(orden-1);

	for(si=0; si<orden-1; si++){
		mi=si+1; //skip the first row
		for(sj=0; sj<orden-1; sj++){
			if(sj==0) mj=0; //return mj to 0 only if we start a new for loop for si
			if(mj==n) mj=sj+1; //skip the n column
			submatrix[si][sj]=matrix[mi][mj];
			mj++; //jump to next column
		}
	}

	return submatrix;
}
