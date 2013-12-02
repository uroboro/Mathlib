#ifndef MTXLIB_H
#define MTXLIB_H

#include "mtx.h"
#include "ptrlib.h"
#include "ansyesno.h"

//memory management
#include <stdlib.h>
matrix *mtxNew(int, int);
void mtxFree(matrix *sender);
int mtxMemory(matrix *sender);

//matrix I/O
void mtxInitAsId(matrix *sender);
void mtxInitWithScalar(matrix *sender, float scalar);
#include <stdio.h>
void mtxScan(matrix *sender);
void mtxPrint(matrix *sender);
void mtxPrintXY(matrix *sender, int x, int y);
void mtxPrintMinor(matrix *sender, int x, int y, int m, int n);

//1 matrix functions
matrix *mtxCopyMatrix(matrix *sender);
matrix *mtxOpposite(matrix *sender);
matrix *mtxTranspose(matrix *sender);
matrix *mtxAdjugate(matrix *sender);
matrix *mtxInverse(matrix *sender);

matrix *mtxMinor(matrix *sender, int x, int y, int m, int n);

matrix *mtxSolveX(matrix *sender);

//Linear matrix operations
//sourceA operation sourceB
//op must be '+', '-', '*' OR '/'.
matrix *mtxLinearOp(matrix *senderA, char, matrix *senderB);
//Traditional matrix multiplication
matrix *mtxVMultiply(matrix *senderA, matrix *senderB);

//1 float, 1 matrix functions
//Scalar matrix multiplication
matrix *mtxSMultiply(matrix *sender, float);


//self functions
void mtxProperties(matrix *sender);
void mtxUpdate(matrix *sender); 			//all of below

void mtxDeterminant(matrix *sender);		//det(mtx)
void mtxIsSquare(matrix *sender);
void mtxIsRegular(matrix *sender);			//m == n
void mtxIsIdentity(matrix *sender); 		//mtx == id
void mtxIsSymmetric(matrix *sender);		//mtx == trn(mtx)
void mtxIsAntiSymmetric(matrix *sender);	//mtx == -trn(mtx)
void mtxIsOrtogonal(matrix *sender);		//inv(mtx) == trn(mtx)
void mtxIsOrthonormal(matrix *sender);		//inv(mtx) == trn(mtx)
void mtxIsTriangular(matrix *sender);		//mtx has triangle of 0s
void mtxIsDiagonal(matrix *sender); 		//mtx has both triangles of 0s (only its diagonal numbers are != 0 (at least one))

//2 matrix functions
bool mtxEquals(matrix *senderA, matrix *senderB);
//ignored
//bool mtxCopy(matrix *senderA, matrix *senderB);	  //returns TRUE if successful

#endif
