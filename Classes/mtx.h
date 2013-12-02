#ifndef MATRIX_H
#define MATRIX_H

#include "bool.h"

typedef struct _matrix {
	//size: m*n
	unsigned char m, n;
	//matrix pointer
	float **mtx;
	//determinant
	float determinant;

		//Boolean properties
		//isPropertySet is TRUE if value is set
		//isProperty is the value itself
		bool isDetSet:1;
		bool isDet:1;
		bool isSquareSet:1;
		bool isSquare:1;
		bool isRegularSet:1;
		bool isRegular:1;
		bool isIdentitySet:1;
		bool isIdentity:1;
		bool isSymmetricSet:1;
		bool isSymmetric:1;
		bool isAntiSymmetricSet:1;
		bool isAntiSymmetric:1;
		bool isOrthogonalSet:1;
		bool isOrthogonal:1;
		bool isOrthonormalSet:1;
		bool isOrthonormal:1;
		bool isTriangularAboveSet:1;
		bool isTriangularAbove:1;
		bool isTriangularBelowSet:1;
		bool isTriangularBelow:1;
		bool isDiagonalSet:1;
		bool isDiagonal:1;
} matrix;

#endif
