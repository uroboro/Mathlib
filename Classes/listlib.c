#include "listlib.h"

mtxnode *listFind(mtxnode *list, char letter) {
	int index;
	char *format = "#Matrix %c(%s): ";
	char *enumeration = mnEnumerate(list);

	do {
		printf(format, letter, enumeration);
		scanf("%d", &index);
	} while (index < 0); //safety
	free(enumeration);

	return mnFindByIndex(list, index);
}
