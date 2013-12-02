#include "ansyesno.h"

void ansYesNo(bool b) {
/*
	switch(b) {
	case TRUE:
		printf("Yes");
		break;
	case FALSE:
		printf("No");
	}

*/
	printf("%s", (b == TRUE)? "Yes":"No");
	return;
}
