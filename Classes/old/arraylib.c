#include "arraylib.h"

matrix *arrayFind(matrix **matrices, char letter, int max){
	int i;
	char *format = "#Matrix %c(0-%d): ";
	do {
		printf(format, letter, max-1);
		scanf("%d", &i);
	} while (i < 0 && i > max); //safety
	return matrices[i];
}
matrix *arrayShow(matrix *sender, int *count) {
	char *format = "#Matrix %d:\n";
	if (sender != NULL) {
		mtxUpdate(sender);
		printf(format, *count);
		mtxPrint(sender);
		mtxProperties(sender);
		count[0]++;
	}
	else
		printf("#Empty pointer.\n");
	return sender;
}
void arrayFree(matrix **matrices, int count) {
	for (unsigned char i = 0; i < count; i++)
		if (matrices[i] != NULL)
			mtxFree(matrices[i]);
	if (matrices != NULL)
		free(matrices);
	return;
}
