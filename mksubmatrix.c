/*
This function will create a new matrix which is done by subtracting the first row of the parent matrix and subtracting the n column.
*/
#include "mksubmatrix.h"

void mksubmatrix(void **dest, void **ori, int m, int n, int pos){

	if(m!=n) return;
	
	int mi, mj, si, sj;
	for(si=0; si<m-1; si++){
		mi=si+1; //skip the first row
		for(sj=0; sj<n-1; sj++){
			if(sj==0) mj=0; //return mj to 0 only if we start a new for loop for si
			if(mj==pos) mj=sj+1; //skip the n column
			dest[si][sj]=ori[mi][mj];
			mj++; //jump to next column
		}
	}

	return;
}
