#include "mtxlib.h"

//memory management
matrix *mtxNew(int m, int n) {
	if (m < 1 || n < 1)
		return NULL;

	matrix *self = (matrix *) malloc(sizeof(matrix));
	self->m = m;
	self->n = n;
	self->mtx = NULL;

/*	useless in C
	//functions
	self->set = &mtxScan;
	self->get = &mtxPrint;
	self->det = &mtxDeterminant;
	self->initAsId = &mtxInitAsId;
	self->initWith = &mtxInitWith;
*/
	//Boolean properties
	self->isDetSet = FALSE;
	self->isSquareSet = FALSE;
	self->isRegularSet = FALSE;
	self->isIdentitySet = FALSE;
	self->isSymmetricSet = FALSE;
	self->isAntiSymmetricSet = FALSE;
	self->isOrthogonalSet = FALSE;
	self->isOrthonormalSet = FALSE;
	self->isTriangularAboveSet = FALSE;
	self->isTriangularBelowSet = FALSE;
	self->isDiagonalSet = FALSE;

	return self;
}
void mtxFree(matrix *self) {
	if (self == NULL) {
		printf("#Empty pointer.\n");
		return;
	}

	ptrFree(self->mtx, self->m, self->n);
	free(self);
	return;
}
int mtxMemory(matrix *self) {
	return sizeof(matrix) + self->m * self->n * 4;
}

/*------------------------------------------------------------------*/

//matrix I/O
void mtxInitAsId(matrix *self) {
	if (self == NULL) {
		printf("#Empty pointer.\n");
		return;
	}

	self->mtx = ptrNew(self->m, self->n);
	self->mtx = ptrInitAsId(self->mtx, self->m, self->n);
	mtxUpdate(self);
	return;
}
void mtxInitWithScalar(matrix *self, float scalar) {
	if (self == NULL) {
		printf("#Empty pointer.\n");
		return;
	}

	self->mtx = ptrNew(self->m, self->n);
	self->mtx = ptrInitWithScalar(self->mtx, self->m, self->n, scalar);
	mtxUpdate(self);
	return;
}
void mtxScan(matrix *self) {
	if (self == NULL) {
		printf("#Empty pointer.\n");
		return;
	}

	self->mtx = ptrNew(self->m, self->n);
	self->mtx = ptrInitManually(self->mtx, self->m, self->n);
	mtxUpdate(self);
	return;
}
void mtxPrint(matrix *self) {
	if (self == NULL) {
		printf("#Empty pointer.\n");
		return;
	}

	ptrPrint(self->mtx, self->m, self->n);
	return;
}
void mtxPrintXY(matrix *self, int x, int y) {
	if (self == NULL) {
		printf("#Empty pointer.\n");
		return;
	}
	if (x < 0 || y < 0 || x > self->m || y > self->n) {
		printf("#Wrong parameters.\n");
		return;
	}

	ptrPrintXY(self->mtx, self->m, self->n, x, y);
	return;
}
void mtxPrintMinor(matrix *self, int x, int y, int m, int n) {
	if (self == NULL) {
		printf("#Empty pointer.\n");
		return;
	}

	if (x < 0 || y < 0 || x + m > self->m || y + n > self->n) {
		printf("#Wrong parameters.\n");
		return;
	}

	ptrPrintMinor(self->mtx, self->m, self->n, x, y, m, n);
	return;
}
/*------------------------------------------------------------------*/

//1 matrix functions
//note that these functions allocate new memory, so remember to free the matrices if you are not using them again

matrix *mtxCopyMatrix(matrix *self) {
	if (self == NULL)
		return NULL;

	matrix *copy = mtxNew(self->m, self->n);
	copy->mtx = ptrCopyMatrix(self->mtx, self->m, self->n);
	return copy;
}
matrix *mtxOpposite(matrix *self) {
	if (self == NULL)
		return NULL;

	matrix *opposite = mtxNew(self->m, self->n);
	opposite->mtx = ptrOpposite(self->mtx, self->m, self->n);
	return opposite;
}
matrix *mtxTranspose(matrix *self) {
	if (self == NULL)
		return NULL;

	matrix *transpose = mtxNew(self->n, self->m);
	transpose->mtx = ptrTranspose(self->mtx, self->m, self->n);
	return transpose;
}
matrix *mtxAdjugate(matrix *self) {
	if (self == NULL)
		return NULL;

	mtxIsSquare(self);
	if (self->isSquare == FALSE)
		return NULL;

	matrix *adjugate = mtxNew(self->m, self->n);
	adjugate->mtx = ptrAdjugate(self->mtx, self->m, self->n);
	return adjugate;
}
matrix *mtxInverse(matrix *self) {
	if (self == NULL)
		return NULL;

	mtxDeterminant(self);
	if (self->isDet == FALSE || self->determinant == 0)
		return NULL;

	matrix *inverse = mtxNew(self->m, self->n);
	inverse->mtx = ptrInverse(self->mtx, self->m, self->n);

	return inverse;
}

/*------------------------------------------------------------------*/

//2 matrix functions

//Linear matrix operations
//sourceA operation sourceB
matrix *mtxLinearOp(matrix *sourceA, char op, matrix *sourceB) {
	if (sourceA == NULL || sourceB == NULL || ! (op == '+' || op == '-' || op == '*' || op == '/'))
		return NULL;

	if (sourceA->m != sourceB->m || sourceA->n != sourceB->n)
		return NULL;

	matrix *temp = mtxNew(sourceA->m, sourceA->n);
	temp->mtx = ptrNew(temp->m, temp->n);
	for (unsigned char i = 0; i < sourceA->m; i++)
		for (unsigned char j = 0; j < sourceA->n; j++)
			switch (op) {
			case '+':
				temp->mtx[j][i] = sourceA->mtx[i][j] + sourceB->mtx[i][j];
				break;
			case '-':
				temp->mtx[j][i] = sourceA->mtx[i][j] - sourceB->mtx[i][j];
				break;
			case '*':
				temp->mtx[j][i] = sourceA->mtx[i][j] * sourceB->mtx[i][j];
				break;
			case '/':
				if (sourceB->mtx[i][j] == 0) {
					mtxFree(temp);
					return NULL;
				}
				temp->mtx[j][i] = sourceA->mtx[i][j] / sourceB->mtx[i][j];
				break;
			}
	return temp;
}

//Traditional matrix multiplication
matrix *mtxVMultiply(matrix *sourceA, matrix *sourceB) {
	if (sourceA == NULL || sourceB == NULL)
		return NULL;

	if (sourceA->n != sourceB->m)
		return NULL;

	matrix *temp = mtxNew(sourceA->m, sourceB->n);
	temp->mtx = ptrVMultiply(sourceA->mtx, sourceA->m, sourceA->n, sourceB->mtx, sourceB->m, sourceB->n);
	return temp;
}

//1 float, 1 matrix functions
matrix *mtxSMultiply(matrix *self, float scalar) {
	if (self == NULL)
		return NULL;

	matrix *temp = mtxNew(self->m, self->n);
	temp->mtx = ptrSMultiply(self->mtx, self->m, self->n, scalar);
	return temp;
}

/*------------------------------------------------------------------*/

//SELF functions
void mtxProperties(matrix *self) {
	if (self == NULL) {
		printf("#Empty pointer.\n");
		return;
	}

	printf("Determinant: ");
	if (self->isDet == TRUE)
		printf(PRINTYPE, self->determinant);
	else
		printf("NAN");
	printf("\n");

	printf("Is square: ");
	ansYesNo(self->isSquare);
	printf("\n");

	printf("Is regular: ");
	ansYesNo(self->isRegular);
	printf("\n");

	printf("Is identity: ");
	ansYesNo(self->isIdentity);
	printf("\n");

	printf("Is symmetric: ");
	ansYesNo(self->isSymmetric);
	printf("\n");

	printf("Is antisymmetric: ");
	ansYesNo(self->isAntiSymmetric);
	printf("\n");

	printf("Is orthogonal: ");
	ansYesNo(self->isOrthogonal);
	printf("\n");

	printf("Is orthonormal: ");
	ansYesNo(self->isOrthogonal);
	printf("\n");

	printf("Is triangular superior: ");
	ansYesNo(self->isTriangularAbove);
	printf("\n");

	printf("Is triangular inferior: ");
	ansYesNo(self->isTriangularBelow);
	printf("\n");

	printf("Is diagonal: ");
	ansYesNo(self->isDiagonal);
	printf("\n");

	return;
}
void mtxUpdate(matrix *self) {
	if (self == NULL) {
		printf("#Empty pointer.\n");
		return;
	}

	self->isDetSet = FALSE;
	mtxDeterminant(self);

	self->isSquareSet = FALSE;
	mtxIsSquare(self);

	self->isRegularSet = FALSE;
	mtxIsRegular(self);

	self->isIdentitySet = FALSE;
	mtxIsIdentity(self);

	self->isSymmetricSet = FALSE;
	mtxIsSymmetric(self);

	self->isAntiSymmetricSet = FALSE;
	mtxIsAntiSymmetric(self);

	self->isOrthogonalSet = FALSE;
	mtxIsOrtogonal(self);

	self->isOrthonormalSet = FALSE;
	mtxIsOrthonormal(self);

	self->isTriangularAboveSet = FALSE;
	self->isTriangularBelowSet = FALSE;
	mtxIsTriangular(self);

	self->isDiagonalSet = FALSE;
	mtxIsDiagonal(self);

	return;
}

//det(mtx)
void mtxDeterminant(matrix *self) {
	if (self == NULL)
		return;

	if (self->isDetSet == FALSE) {
		if (self->isSquare == TRUE) {
			self->determinant = ptrLaplace(self->mtx, self->m, self->n);
			self->isDet = TRUE;
		}
		else {
			self->determinant = 0;
			self->isDet = FALSE;
		}
	self->isDetSet = TRUE;
	}
	return;
}
//m == n
void mtxIsSquare(matrix *self) {
	if (self == NULL)
		return;

	if (self->isSquareSet == FALSE) {
		self->isSquare = (self->m == self->n)? TRUE:FALSE;
		self->isSquareSet = TRUE;
	}
	return;
}
//mtx == id
void mtxIsIdentity(matrix *self) {
	if (self == NULL)
		return;

	if (self->isIdentitySet == FALSE) {
		mtxIsSquare(self);
		self->isIdentity = (self->isSquare == TRUE)? ptrIsIdentity(self->mtx, self->m, self->n):FALSE;
		self->isIdentitySet = TRUE;
	}
	return;
}
//det(mtx)!=0
void mtxIsRegular(matrix *self) {
	if (self == NULL)
		return;

	if (self->isRegularSet == FALSE) {
		mtxIsSquare(self);
		self->isRegular = (self->isSquare == TRUE)? ((self->determinant != 0)? TRUE:FALSE):FALSE;
		self->isRegularSet = TRUE;
	}
	return;
}
//mtx == trn(mtx)
void mtxIsSymmetric(matrix *self) {
	if (self == NULL)
		return;

	if (self->isSymmetricSet == FALSE) {
		mtxIsSquare(self);
		self->isSymmetric = (self->isSquare == TRUE)? ptrIsSymmetric(self->mtx, self->m, self->n):FALSE;
		self->isSymmetricSet = TRUE;
	}
	return;
}
//mtx == -trn(mtx)
void mtxIsAntiSymmetric(matrix *self) {
	if (self == NULL)
		return;

	if (self->isAntiSymmetricSet == FALSE) {
		mtxIsSquare(self);
		self->isAntiSymmetric = (self->isSquare == TRUE)? ptrIsAntiSymmetric(self->mtx, self->m, self->n):FALSE;
		self->isAntiSymmetricSet = TRUE;
	}
	return;
}
//inv(mtx)==trn(mtx)
void mtxIsOrtogonal(matrix *self) {
	if (self == NULL)
		return;

	if (self->isOrthogonalSet == FALSE) {
		mtxIsRegular(self);
		self->isOrthogonal = (self->isRegular == TRUE)? ptrIsOrthogonal(self->mtx, self->m, self->n):FALSE;
		self->isOrthogonalSet = TRUE;
	}
	return;
}
//det(mtx)==1
void mtxIsOrthonormal(matrix *self) {
	if (self == NULL)
		return;

	if (self->isOrthonormalSet == FALSE) {
		mtxIsRegular(self);
		self->isOrthonormal = (self->isRegular == TRUE)? ((self->determinant == 1)? TRUE:FALSE):FALSE;
		self->isOrthonormalSet = TRUE;
	}
	return;
}
void mtxIsTriangular(matrix *self) {
	if (self == NULL)
		return;

	if (self->isTriangularAboveSet == FALSE) {
		mtxIsSquare(self);
		self->isTriangularAbove = (self->isSquare == TRUE)? ptrIsTriangularAbove(self->mtx, self->m, self->n):FALSE;
		self->isTriangularAboveSet = TRUE;
	}
	if (self->isTriangularBelowSet == FALSE) {
		mtxIsSquare(self);
		self->isTriangularBelow = (self->isSquare == TRUE)? ptrIsTriangularBelow(self->mtx, self->m, self->n):FALSE;
		self->isTriangularBelowSet = TRUE;
	}
	return;
}
void mtxIsDiagonal(matrix *self) {
	if (self == NULL)
		return;

	if (self->isDiagonalSet == FALSE) {
		mtxIsTriangular(self);
		self->isDiagonal = (self->isTriangularAbove == TRUE && self->isTriangularBelow == TRUE)? TRUE:FALSE;
		self->isDiagonalSet = TRUE;
	}
	return;
}

/*------------------------------------------------------------------*/

//Evaluation
bool mtxEquals(matrix *dest, matrix *source) {
	if (dest == NULL || source == NULL)
		return FALSE;
	if (dest == source)
		return TRUE;
	return ptrIsEqual(dest->mtx, dest->m, dest->n, source->mtx, source->m, source->n);
}
/*
bool mtxCopy(matrix *dest, matrix *source) {
	if (dest == NULL || source == NULL)
		return FALSE;
	if (dest == source)
		return TRUE;
	if (source->m != dest->m || source->n != dest->n)
		return FALSE;

	int i, j;
	if (dest->mtx == NULL)
		dest->mtx = ptrNew(dest->m, dest->n);
	for (i = 0; i < source->m; i++)
		for (j = 0; j < source->n; j++)
			dest->mtx[i][j] = source->mtx[i][j];
	mtxUpdate(dest);
	return TRUE;
}
*/
