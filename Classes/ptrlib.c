#include "ptrlib.h"

//Memory management
float **ptrNew(int m, int n){
	if (m < 1 || n < 1)
		return NULL;

	float **self = (float **) malloc(m * sizeof(float *));
	for (unsigned char i = 0; i < m; i++)
		self[i] = (float *) malloc(n * sizeof(float));
	return self;
}
void ptrFree(float **self, int m, int n) {
	if (self == NULL || m < 1 || n < 1)
		return;

	int i;
	for (i = 0; i < m; i++)
		free(self[i]);
	free(self);
	return;
}

/*------------------------------------------------------------------*/

//I/O
float **ptrInitAsId(float **self, int m, int n) {
	if (self == NULL || m < 1 || n < 1)
		return NULL;

	if (m != n)
		return NULL;

	for (unsigned char i = 0; i < m; i++)
		for (unsigned char j = 0; j < n; j++)
				self[i][j] = (i == j)? 1:0;
	return self;
}
float **ptrInitWithScalar(float **self, int m, int n, float scalar) {
	if (self == NULL || m < 1 || n < 1)
		return NULL;

	for (unsigned char i = 0; i < m; i++)
		for (unsigned char j = 0; j < n; j++)
			self[i][j] = scalar;
	return self;
}
float **ptrInitManually(float **self, int m, int n) {
	if (self == NULL || m < 1 || n < 1)
		return NULL;

	for (unsigned char i = 0; i < m; i++)
		for (unsigned char j = 0; j < n; j++) {
			printf("[%d][%d]= ", i, j);
			if (scanf(SCANTYPE, &self[i][j]) == -1) {
				ptrFree(self, m, n);
				return NULL;
			}
		}
	return self;
}
float **ptrPrint(float **self, int m, int n) {
	if (self == NULL || m < 1 || n < 1)
		return NULL;

	for (unsigned char i = 0; i < m; i++) {
		printf("| ");
		for (unsigned char j = 0; j < n; j++)
			printf(PRINTYPE, self[i][j]);
		printf("|\n");
	}
	return self;
}
float **ptrPrintXY(float **self, int m, int n, int x, int y) {
	if (self == NULL || m < 1 || n < 1)
		return NULL;
	if (x > m || y > n)
		return NULL;

	printf(PRINTYPE, self[x][y]);
	return self;
}
float **ptrPrintMinor(float **self, int m, int n, int x, int y, int m0, int n0) {
	if (self == NULL || m < 1 || n < 1)
		return NULL;
	if (x > m || y > n)
		return NULL;
	if (m0 < 1 || n0 < 1 || x + m0 > m || y + n0 > n)
		return NULL;

	for (unsigned char i = x; i < m0; i++) {
		printf("| ");
		for (unsigned char j = y; j < n0; j++)
			printf(PRINTYPE, self[i][j]);
		printf("|\n");
	}
	return self;
}

/*------------------------------------------------------------------*/
//OPERATIONS

float **ptrCopyMatrix(float **self, int m, int n) {
	if (self == NULL || m < 1 || n < 1)
		return NULL;

	float **copy = ptrNew(m, n);
	for (unsigned char i = 0; i < m; i++)
		for (unsigned char j = 0; j < n; j++)
			copy[i][j] = self[i][j];
	return copy;
}
float **ptrTranspose(float **self, int m, int n) {
	if (self == NULL || m < 1 || n < 1)
		return NULL;

	float **transpose = ptrNew(n, m);
	for (unsigned char i = 0; i < m; i++)
		for (unsigned char j = 0; j < n; j++)
			transpose[j][i] = self[i][j];
	return transpose;
}
float **ptrOpposite(float **self, int m, int n) {
	if (self == NULL || m < 1 || n < 1)
		return NULL;

	return ptrSMultiply(self, m, n, -1);
}
float **ptrSMultiply(float **self, int m, int n, float scalar) {
	if (self == NULL || m < 1 || n < 1)
		return NULL;

	float **product = ptrNew(m, n);
	for (unsigned char i = 0; i < m; i++)
		for (unsigned char j = 0; j < n; j++)
			product[i][j] = scalar * self[i][j];
	return product;
}
float **ptrVMultiply(float **selfA, int mA, int nA, float **selfB, int mB, int nB) {
	if (selfA == NULL || selfB == NULL)
		return NULL;
	if (mA < 1 || mB < 1 || nA < 1 || nB < 1 || nA != mB)
		return NULL;

	float **product = ptrNew(mA, nB);
	for (unsigned char i = 0; i < mA; i++)
		for (unsigned char j = 0; j < nB; j++) {
			product[i][j] = 0;
			for (unsigned char k = 0; k < nA; k++)
				product[i][j] += selfA[i][k] * selfB[k][j];
		}
	return product;
}
float **ptrCofactor(float **self, int m, int n) {
	if (self == NULL || m < 1 || n < 1)
		return NULL;
	if (m != n)
		return NULL;

	float **cofactor = ptrNew(m, n);
	for (unsigned char i = 0; i < m; i++)
		for (unsigned char j = 0; j < n; j++) {
			//create a submatrix such that skips row i and column j
			float **submatrix = ptrSubmatrix(self, m, n, i, j);
			cofactor[i][j] = (1 - 2 * ((i + j) % 2)) * ptrLaplace(submatrix, m - 1, n - 1);
			ptrFree(submatrix, m - 1, n - 1);
		}
	return cofactor;
}
float **ptrAdjugate(float **self, int m, int n) {
	if (self == NULL || m < 1 || n < 1)
		return NULL;
	if (m != n)
		return NULL;

	float **cofactor = ptrCofactor(self, m, n);
	float **adjugate = ptrTranspose(cofactor, m, n);
	ptrFree(cofactor, m, n);
	return adjugate;
}
float **ptrInverse(float **self, int m, int n) {
	if (self == NULL || m < 1 || n < 1)
		return NULL;
	if (m != n)
		return NULL;

	//get determinant
	float determinant = ptrLaplace(self, m, n);
	if (determinant < 0.000001 )
		return NULL;
	//get adjugate
	float **adjugate = ptrAdjugate(self, m, n);

	float **inverse = ptrSMultiply(adjugate, m, n, 1/determinant);
	ptrFree(adjugate, m, n);

	return inverse;
}
//This function will create a new matrix which is done by subtracting the first row of the parent matrix and subtracting the skip column.
float **ptrSubmatrix(float **self, int m, int n, int iSkip, int jSkip){
	if (self == NULL || m < 1 || n < 1)
		return NULL;

	if (m != n)
		return NULL;
	if (0 > iSkip || iSkip > m || 0 > jSkip || jSkip > n)
		return NULL;

	unsigned char iSelf, jSelf, iSubmatrix, jSubmatrix;
	//Alloc a new squared matrix 1 row and 1 column smaller
	float **submatrix = ptrNew(m - 1, n - 1);
	for (iSelf = iSubmatrix = 0; iSelf < m - 1; iSelf++, iSubmatrix++) {
		//skip the iSkip row
		if (iSelf == iSkip)
			iSubmatrix++;
		for (jSelf = jSubmatrix = 0; jSelf < n - 1; jSelf++, jSubmatrix++) {
			//skip the iSkip column
			if (jSubmatrix == jSkip)
				jSubmatrix++;
			submatrix[iSelf][jSelf] = self[iSubmatrix][jSubmatrix];
		}
	}
	return submatrix;
}
float ptrLaplace(float **self, int m, int n){
	if (self == NULL || m < 1 || n < 1)
		return 0;
	if (m != n)
		return 0;

	float determinant = 0.0;
	switch (m) {
	//1x1 matrix
	case 1:
		determinant = self[0][0];
		break;
	//2x2 matrix
	case 2:
		determinant = (self[0][0] * self[1][1] - self[0][1] * self[1][0]);
		break;
	//3x3 matrix and beyond
	default:
		for (unsigned char column = 0; column < n; column++) {
			//create a submatrix
			float **submatrix = ptrSubmatrix(self, m, n, 0, column);
			/* for each iteration, add to determinant:
			 * the top item in the current column, multiplied by
			 * 1 || -1, being '(1 - 2 * (column % 2))' the result of refining (-1)^(i+j)
			 * the recursive function using the submatrix
			 */
			determinant += self[0][column] * (1 - 2 * (column % 2)) * ptrLaplace(submatrix, m - 1, n - 1);
			ptrFree(submatrix, m - 1, n - 1);
		}
	}
	return determinant;
}
float **ptrMinor(float **self, int m, int n, int x, int y, int m0, int n0) {
	if (self == NULL || m < 1 || n < 1)
		return NULL;
	if (x > m || y > n)
		return NULL;
	if (m0 < 1 || n0 < 1 || x + m0 > m || y + n0 > n)
		return NULL;

	float **minor = ptrNew(m0, n0);
	for (unsigned char i = 0; i < m0; i++)
		for (unsigned char j = 0; j < n0; j++)
			minor[i][j] = self[i + x][j + y];
	return minor;
}

float **ptrSolveX(float **self, int m, int n) {
	if (self == NULL || m < 1 || n < 1)
		return NULL;
	if (m != n - 1)
		return NULL;

	// m variables
	float **answer = ptrNew(1, m + 1);
	answer[1][m] = ptrLaplace(self, m, m);

	float **temp = ptrNew(m, m);
	for (unsigned char i = 0; i < m; i++) {
		//switches the i column with the last column from the original matrix:
		temp = ptrCopyMatrix(self, m, m);
		for (unsigned char j = 0; j < m; j++)
			temp[j][i] = self[j][m];
		answer[1][i] = ptrLaplace(temp, m, m) / answer[1][m];
		ptrFree(temp, m, m);
	}

	return answer;
}
float **ptrLinearOp(float **selfA, int mA, int nA, char op, float **selfB, int mB, int nB) {
	if (selfA == NULL || selfB == NULL || ! (op == '+' || op == '-' || op == '*' || op == '/'))
		return NULL;

	if (mA != mB || nA != nB)
		return NULL;

	float **temp = ptrNew(mA, nB);
	for (unsigned char i = 0; i < mA; i++)
		for (unsigned char j = 0; j < nA; j++)
			switch (op) {
			case '+':
				temp[j][i] = selfA[i][j] + selfB[i][j];
				break;
			case '-':
				temp[j][i] = selfA[i][j] - selfB[i][j];
				break;
			case '*':
				temp[j][i] = selfA[i][j] * selfB[i][j];
				break;
			case '/':
				if (selfB[i][j] == 0) {
					ptrFree(temp, mA, nA);
					return NULL;
				}
				temp[j][i] = selfA[i][j] / selfB[i][j];
				break;
			}
	return temp;
}

/*------------------------------------------------------------------*/

//EVALUATION
bool ptrIsEqual(float **selfA, int mA, int nA, float **selfB, int mB, int nB) {
	if (selfA == NULL || selfB == NULL)
		return FALSE;
	if (mA != mB || nA != nB)
		return FALSE;

	for (unsigned char i = 0; i < mA; i++)
		for (unsigned char j = 0; j < nA; j++)
			if (selfA[i][j] != selfB[i][j])
				return FALSE;
	return TRUE;
}
bool ptrIsIdentity(float **self, int m, int n) {
	if (self == NULL || m < 1 || n < 1)
		return FALSE;

	if (m != n)
		return FALSE;

	for (unsigned char i = 0; i < m; i++)
		for (unsigned char j = 0; j < n; j++) {
			if (i == j) {
				if (self[i][j] != 1)
					return FALSE;
			}
			else
				if (self[i][j] != 0)
					return FALSE;
		}
	return TRUE;
}
bool ptrIsSymmetric(float **self, int m, int n) {
	if (self == NULL || m < 1 || n < 1)
		return FALSE;

	if (m != n)
		return FALSE;

	float **transpose = ptrTranspose(self, m, n);
	bool b = ptrIsEqual(self, m, n, transpose, m, n);
	ptrFree(transpose, m, n);
	return b;
}
bool ptrIsAntiSymmetric(float **self, int m, int n) {
	if (self == NULL || m < 1 || n < 1)
		return FALSE;

	if (m != n)
		return FALSE;

	for (unsigned char i = 0; i < m; i++)
		if (self[i][i] != 0)
			return FALSE;
	float **transpose = ptrTranspose(self, m, n);
	float **opposite = ptrOpposite(transpose, m, n);
	ptrFree(transpose, m, n);
	bool b = ptrIsEqual(self, m, n, opposite, m, n);
	ptrFree(opposite, m, n);
	return b;
}
bool ptrIsOrthogonal(float **self, int m, int n) {
	if (self == NULL || m < 1 || n < 1)
		return FALSE;

	if (m != n)
		return FALSE;

	float **transpose = ptrTranspose(self, m, n);
	float **inverse = ptrInverse(self, m, n);
	bool b = ptrIsEqual(transpose, m, n, inverse, m, n);
	ptrFree(transpose, m, n);
	ptrFree(inverse, m, n);
	return b;
}
bool ptrIsTriangularAbove(float **self, int m, int n) {
	if (self == NULL || m < 1 || n < 1)
		return FALSE;

	if (m != n)
		return FALSE;

	int i, j;
	for (i = 0; i < m; i++)
		for (j = i + 1; j < n; j++)
			if (self[i][j] != 0)
				return FALSE;
	return TRUE;
}
bool ptrIsTriangularBelow(float **self, int m, int n) {
	if (self == NULL || m < 1 || n < 1)
		return FALSE;

	if (m != n)
		return FALSE;

	for (unsigned char i = 0; i < m; i++)
		for (unsigned char j = 0; j < i; j++)
			if (self[i][j] != 0)
				return FALSE;
	return TRUE;
}
bool ptrIsDiagonal(float **self, int m, int n) {
	if (self == NULL || m < 1 || n < 1)
		return FALSE;

	return ptrIsTriangularAbove(self, m, n) && ptrIsTriangularBelow(self, m, n);
}
