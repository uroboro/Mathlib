#ifndef PTRLIB_H
#define PTRLIB_H

#include <stdio.h>
#include <stdlib.h>
#include "bool.h"

#define SCANTYPE	"%f"
#define PRINTYPE	"%.2f "

//Memory management
float **ptrNew(int m, int n);
void ptrFree(float **self, int m, int n);

//I/O
float **ptrInitAsId(float **self, int m, int n);
float **ptrInitWithScalar(float **self, int m, int n, float scalar);
float **ptrInitManually(float **self, int m, int n);
float **ptrPrint(float **self, int m, int n);
float **ptrPrintXY(float **self, int m, int n, int x, int y);
float **ptrPrintMinor(float **self, int m, int n, int x, int y, int m0, int n0);

//OPERATIONS

float **ptrCopyMatrix(float **self, int m, int n);
//Creates transpose matrix
float **ptrTranspose(float **self, int m, int n);
//Creates opposite matrix
float **ptrOpposite(float **self, int m, int n);
//Multiplies a matrix by a scalar
float **ptrSMultiply(float **self, int m, int n, float scalar);
//Multiplies two matrices
float **ptrVMultiply(float **selfA, int mA, int nA, float **selfB, int mB, int nB);
//Creates cofactor matrix
float **ptrCofactor(float **self, int m, int n);
//Creates adjugate matrix
float **ptrAdjugate(float **self, int m, int n);
//Creates inverse matrix
float **ptrInverse(float **self, int m, int n);
//Will create a new matrix which is done by subtracting the x row and the y column of the parent matrix.
float **ptrSubmatrix(float **self, int m, int n, int x, int y);
//Calculates determinant of a squared matrix
float ptrLaplace(float **self, int m, int n);
//Will create a new matrix which is done by selecting an m0 by n0 matrix starting at [x][y] of the parent matrix.
float **ptrMinor(float **self, int m, int n, int x, int y, int m0, int n0);

//SOLVE X
//Will create a new matrix which is the solution of a system of equations, being a matrix of size 2 by n. First row will indicate whether the second row has valid solutions. There should be as many equations as there are variables, plus one column for independent values.
float **ptrSolveX(float **self, int m, int n);

//Evaluation
bool ptrIsEqual(float **selfA, int mA, int nA, float **selfB, int mB, int nB);
bool ptrIsIdentity(float **self, int m, int n);
bool ptrIsSymmetric(float **self, int m, int n);
bool ptrIsAntiSymmetric(float **self, int m, int n);
bool ptrIsOrthogonal(float **self, int m, int n);
bool ptrIsTriangularAbove(float **self, int m, int n);
bool ptrIsTriangularBelow(float **self, int m, int n);
bool ptrIsDiagonal(float **self, int m, int n);

#endif
