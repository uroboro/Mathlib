#include "switchcolumn.h"

float **switchcolumn(float **matrix, int n, int orden){

    int i, j;

    float **smatrix=newmatrix(orden);

    for(i=0; i<orden; i++)
        for(j=0; j<orden; j++){
            if(j==n) smatrix[i][j]=matrix[i][orden];
            else smatrix[i][j]=matrix[i][j];
        }

    return smatrix;
}
