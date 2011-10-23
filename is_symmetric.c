#include "main.h"
#include "is_symmetric.h"

bool is_symmetric(float **matrix, int orden){

int i, j;

for(i=0; i<orden; i++)
for(j=0; j<orden; j++)
if(matrix[i][j]!=matrix[j][i]) return FALSE;
return TRUE;
}