#include "array.h"

int mainArray(){

	//counters
	int i, count = 0;

	//options; also functions
	int optc = 24;
	char *optv[] = {
		"exit",
		"new",
		"show",
		"free",
		"isequal",
		"copy",
		"determinant",
		"isidentity",
		"isinversible",
		"issymmetric",
		"isantisymmetric",
		"istriangular",
		"isdiagonal",
		"isorthogonal",
		"opposite",
		"scalar",
		"invert",
		"transpose",
		"adjugate",
		"add",
		"subtract",
		"multiply",
		"divide",
		"vmultiply"
	};

//MATRIX
	//scalar number
	float scalar;
	//array
	matrix *sender,
		*senderA,
		*senderB;
	matrix **matrices = (matrix **) malloc(sizeof(matrix *));

//EXTRA
	//option
	bool bOperand;
	char cOperand;
	bool exitStatus = FALSE;
//printf("%ld", sizeof(matrix)); //84

	do{
		switch (autoMenu(optc, optv, NULL)) {

		case 0: //EXIT
			exitStatus = TRUE;
			break;

		case 1: //NEW
			matrices = (matrix **) realloc(matrices, (count + 1) * sizeof(matrix *));
			sender = matrices[count] = mtxInput();
			arrayShow(sender, &count);
			break;

		case 2: //SHOW
			for (i = 0; i < count; i++) {
				sender = matrices[i];
				if ( sender != NULL) {
					printf("#Matrix %d:\n", i);
					mtxPrint(sender);
					mtxUpdate(sender);
					mtxProperties(sender);
				}
				else
					printf("#Empty pointer.\n");
			}
			break;

		case 3: //FREE
			sender = arrayFind(matrices, 0, count);
			if (sender != NULL) {
				mtxFree(sender);
				sender = NULL;
			}
			else
				printf("#Empty pointer.\n");
			break;

		case 4: //ISEQUAL
			senderA = arrayFind(matrices, 'A', count);
			senderB = arrayFind(matrices, 'B', count);
			printf("#");
			ansYesNo(mtxEquals(senderA, senderB));
			break;

		case 5: //COPY
			senderA = arrayFind(matrices, 'A', count);
			senderB = arrayFind(matrices, 'B', count);
			printf("#");
			ansYesNo(senderB = mtxCopyMatrix(senderA));
			mtxUpdate(senderA);
			break;

		case 6: //DETERMINANT
			sender = arrayFind(matrices, 0, count);
			printf("#Determinant: ");
			if (sender->isDet == TRUE)
				printf(PRINTYPE, sender->determinant);
			else
				printf("NAN");
			printf("\n");
			break;

		case 7: //ISIDENTITY
			sender = arrayFind(matrices, 0, count);
			printf("#");
			ansYesNo(sender->isIdentity);
			break;

		case 8: //ISINVERSIBLE
			sender = arrayFind(matrices, 0, count);
			printf("#");
			ansYesNo(sender->isRegular);
			break;

		case 9: //ISSYMMETRICAL
			sender = arrayFind(matrices, 0, count);
			printf("#");
			ansYesNo(sender->isSymmetric);
			break;

		case 10: //ISANTISYMMETRICAL
			sender = arrayFind(matrices, 0, count);
			printf("#");
			ansYesNo(sender->isAntiSymmetric);
			break;

		case 11: //ISTRIANGULAR
			sender = arrayFind(matrices, 0, count);
			printf("#");
			ansYesNo(sender->isTriangularAbove || sender->isTriangularBelow);
			break;

		case 12: //ISDIAGONAL
			sender = arrayFind(matrices, 0, count);
			printf("#");
			ansYesNo(sender->isDiagonal);
			break;

		case 13: //ISORTHOGONAL
			sender = arrayFind(matrices, 0, count);
			printf("#");
			ansYesNo(sender->isOrthogonal);
			break;

		case 14: //OPPOSITE
			sender = arrayFind(matrices, 0, count);
			sender = matrices[count] = mtxOpposite(sender);
			arrayShow(sender, &count);
			break;

		case 15: //SCALAR
			sender = arrayFind(matrices, 0, count);
			printf("#Scalar: ");
			scanf(SCANTYPE, &scalar);
			sender = matrices[count] = mtxSMultiply(sender, scalar);
			arrayShow(sender, &count);
			break;

		case 16: //INVERT
			sender = arrayFind(matrices, 0, count);
			sender = matrices[count] = mtxInverse(sender);
			arrayShow(sender, &count);
			break;

		case 17: //TRANSPOSE
			sender = arrayFind(matrices, 0, count);
			sender = matrices[count] = mtxTranspose(sender);
			arrayShow(sender, &count);
			break;

		case 18: //ADJUGATE
			sender = arrayFind(matrices, 0, count);
			sender = matrices[count] = mtxAdjugate(sender);
			arrayShow(sender, &count);
			break;

		//LINEAROPS
		case 19: //ADD
			if (bOperand != TRUE) {
				cOperand = '+';
				bOperand = TRUE;
			}
		case 20: //SUBTRACT
			if (bOperand != TRUE) {
				cOperand = '-';
				bOperand = TRUE;
			}
		case 21: //MULTIPLY
			if (bOperand != TRUE) {
				cOperand = '*';
				bOperand = TRUE;
			}
		case 22: //DIVIDE
			if (bOperand != TRUE) {
				cOperand = '/';
				bOperand = TRUE;
			}
			senderA = arrayFind(matrices, 'A', count);
			senderB = arrayFind(matrices, 'B', count);
			sender = matrices[count] = mtxLinearOp(senderA, cOperand, senderB);
			arrayShow(sender, &count);
			bOperand = FALSE;
			break;

		case 23: //VMULTIPLY
			senderA = arrayFind(matrices, 'A', count);
			senderB = arrayFind(matrices, 'B', count);
			sender = matrices[count] = mtxVMultiply(senderA, senderB);
			arrayShow(sender, &count);
			break;

		default: //ELSE
			printf("#Option not recognised or not implemented yet\n");
			break;
		}
	} while (exitStatus != TRUE);

	arrayFree(matrices, count);
	printf("#Done!\n");

	return 0;
}
