#include "mtx2.h"

#ifndef MATRIX_H
#define MATRIX_H

#include "bool.h"

typedef struct matrix {

	//size: m*n
	unsigned char m, n;

	//matrix pointer
	float **mtx;

	//determinant
	float determinant;

/*	deprecated
	//functions
	void (*set)(struct matrix *);
	void (*get)(struct matrix *);
	void (*det)(struct matrix *);
	void (*initAsId)(struct matrix *);
	void (*initWith)(struct matrix *, float);
*/
	//Boolean properties
	//[0] is TRUE if value is set
	//[1] is the value itself
	bool isDet[2];
	bool isSquare[2];		//m==n
	bool isRegular[2];		//det(mtx)!=0
	bool isIdentity[2];		//mtx==id
	bool isSymmetric[2];		//mtx==trn(mtx)
	bool isAntiSymmetric[2];	//mtx==-trn(mtx)
	bool isOrthogonal[2];		//trn(mtx)==inv(mtx)
	bool isOrthonormal[2];		//det(mtx)==1
	bool isTriangularAbove[2];	//mtx[i,j]==0 Vi+j>1
	bool isTriangularBelow[2];	//mtx[i,j]==0 Vi+j<1
	bool isDiagonal[2];		//both triangles

} matrix;

#endif
