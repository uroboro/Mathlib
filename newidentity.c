#include "newidentity.h"

float **newidentity(int orden){

    int i, j;

    float **matrix=(float **)malloc(orden*FLOATP_S);
    for(i=0; i<orden; i++) matrix[i]=(float *)malloc(orden*FLOAT_S);

    for(i=0; i<orden; i++)
        for(j=0; j<orden; j++)
            matrix[i][j]=0.0;
            
    for(i=0; i<orden; i++)
        matrix[i][i]=1.0;

    return matrix;
}
