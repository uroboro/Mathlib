#include "list.h"
#include "debug.h"
bool debugL = FALSE;

int mainList() {

	//options; also functions
//if(debugL) dbgInt(sizeof(matrix), "\n");
//if(debugL) dbgInt(sizeof(mtxnode), "\n");
	char *optv[] = {
		"exit",
		"new",
		"pop",
		"enum",
		"show",
		"list",
		"dump",
		"isequal",
		"copy",
		"properties",
		"opposite",
		"scalar",
		"invert",
		"transpose",
		"adjugate",
		"add",
		"subtract",
		"multiply",
		"divide",
		"vmultiply",
		"mem",
		"config"
	};
	int optc = sizeof(optv)/sizeof(char *);

//MATRIX
	//scalar number
	float scalar;
	//matrix
	matrix *mtxSender;
	//list
	mtxnode *list = NULL,
		*sender,
		*senderA,
		*senderB;

//EXTRA
	//option
	bool bOperand;
	char cOperand,
		*string;
	bool exitStatus = FALSE,
		displayAfterPush = FALSE;
	char *path = "./mtx.sav";

	int configc = 3;
	char *configv[] = {
		stringify(displayAfterPush),
		stringify(path),
		stringify(debugL)
	};

//load matrices from 'path' to 'list'
	mfListIO(path, &list, 'l');
	mnUpdateAll(list);
	string = mnList(list);
	if (string != NULL) {
		printf("#%d matrices were loaded.\n", string[0]);
		free(string);
	}


	do{
if(debugL) dbgPointer(list, "\t");
		switch (autoMenu(optc, optv, NULL)) {

		case 0: //EXIT
			exitStatus = TRUE;
			break;

		case 1: //NEW
			mtxSender = mtxInput();
			mnPush(&list, mtxSender);
			if (displayAfterPush == TRUE)
				mnShow(mnFindByData(list, mtxSender));
			// if I didn't want to show the matrix I could just do:
//			mnPush(&list, mtxInput());
			break;

		case 2: //POP
			sender = listFind(list, 0);
			if (sender != NULL)
				mnPop(&list, sender->index);
			break;

		case 3: //ENUMERATE
			string = mnEnumerate(list);
			if (string != NULL) {
				fprintf(stdout, "#%s\n", string);
				free(string);
			}
			break;

		case 4: //SHOW
			sender = listFind(list, 0);
			mnShow(sender);
			break;

		case 5: //LIST
			mnShowAll(list);
			break;

		case 6: //DUMP
			mnDump(&list);
			break;

		case 7: //ISEQUAL
			senderA = listFind(list, 'A');
			senderB = listFind(list, 'B');
			printf("#Is equal: ");
			ansYesNo(mnEquals(senderA, senderB));
			break;

		case 8: //COPY
			senderA = listFind(list, 'A');
			senderB = listFind(list, 'B');
			printf("#Copy successful: ");
			ansYesNo(mnCopy(senderA, senderB));
			mnUpdate(senderA);
			break;

		case 9: //PROPERTIES
			sender = listFind(list, 0);
			mnProperties(sender);
			break;

		case 10: //OPPOSITE
			sender = mnOpposite(&list, listFind(list, 0));
			if (displayAfterPush == TRUE)
				mnShow(mnFindByData(list, sender->data));
			break;

		case 11: //SCALAR
			printf("#Scalar: ");
			scanf(SCANTYPE, &scalar);
			sender = mnSMultiply(&list, listFind(list, 0), scalar);
			if (displayAfterPush == TRUE)
				mnShow(mnFindByData(list, sender->data));
			break;

		case 12: //INVERT
			sender = mnInverse(&list, listFind(list, 0));
			if (displayAfterPush == TRUE)
				mnShow(mnFindByData(list, sender->data));
			break;

		case 13: //TRANSPOSE
			sender = mnTranspose(&list, listFind(list, 0));
			if (displayAfterPush == TRUE)
				mnShow(mnFindByData(list, sender->data));
			break;

		case 14: //ADJUGATE
			sender = mnAdjugate(&list, listFind(list, 0));
			if (displayAfterPush == TRUE)
				mnShow(mnFindByData(list, sender->data));
			break;

		//LINEAROPS
		case 15: //ADD
			if (bOperand == FALSE) {
				cOperand = '+';
				bOperand = TRUE;
			}
		case 16: //SUBTRACT
			if (bOperand == FALSE) {
				cOperand = '-';
				bOperand = TRUE;
			}
		case 17: //MULTIPLY
			if (bOperand == FALSE) {
				cOperand = '*';
				bOperand = TRUE;
			}
		case 18: //DIVIDE
			if (bOperand == FALSE) {
				cOperand = '/';
			}
			bOperand = FALSE;

			senderA = listFind(list, 'A');
			senderB = listFind(list, 'B');
			sender = mnLinearOp(&list, senderA, cOperand, senderB);
			if (displayAfterPush == TRUE)
				mnShow(mnFindByData(list, sender->data));
			break;

		case 19: //VMULTIPLY
			senderA = listFind(list, 'A');
			senderB = listFind(list, 'B');
			sender = mnVMultiply(&list, senderA, senderB);
			if (displayAfterPush == TRUE)
				mnShow(mnFindByData(list, sender->data));
			break;

		case 20:
			printf("#Memory in use by matrices: %ld bytes\n", mnMemory(list));
			break;

		case 21: //OPTIONS
			switch(autoMenu(configc, configv, NULL)) {
			case 0:
				dbgChar(displayAfterPush); printf("\n");
				printf("#New value(0/1): ");
				scanf(" %c", &cOperand);
				displayAfterPush = (cOperand == '1')? TRUE:FALSE;
				break;
			case 1:
				dbgString(path); printf("\n");
				printf("#New value: ");
				scanf("%s", string);
				path = (string != NULL)? string:path;
				break;
			case 2:
				dbgChar(debugL); printf("\n");
				printf("#New value(0/1): ");
				scanf(" %c", &cOperand);
				debugL = (cOperand == '1')? TRUE:FALSE;
				break;
			default:  //ELSE
				printf("#Option not recognised or not implemented yet\nn");
			};
			break;

		default: //ELSE
			printf("#Option not recognised or not implemented yet\n");
			break;
		}
	} while (exitStatus != TRUE);

//save matrices from 'list' to 'path'
	mfListIO(path, &list, 's');
	mnDump(&list);

	return 0;
}
