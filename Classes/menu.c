#include "menu.h"
/*
int menu(int argc, char **argv) {
	if (argc < 1)
		return -2;
	if (argv == NULL)
		return -3;

	char ans[21];
	printf("#What to do?\n{ ");
	//print each arg
	for (unsigned char i = 0; i < argc; i++) {
		printf("%s", argv[i]);
		if (i < argc-1) printf(", ");
		else printf(" }\n#Op: ");
	}
	scanf("%s", ans);
	//searches for strop in argv, returning its index
	for (unsigned char i = 0; i < argc; i++)
		if (equals(ans, argv[i]) == TRUE)
			return i;
	return -1;
}
*/
//menu() but with the answer already known
int autoMenu(int argc, char **argv, char *ans) {
	if (argc < 1)
		return -2;
	if (argv == NULL)
		return -3;

	if (ans == NULL) {
		printf("#What to do?\n{ ");
		//print each arg
		for (unsigned char i = 0; i < argc; i++) {
			printf("%s", argv[i]);
			if (i == argc-1)
				break;
			printf(", ");
		}
		printf(" }\n#Op: ");
		char answer[21];
		scanf("%s", answer);
		ans = answer;
	}

	//searches for ans in argv, returning its index
	for (unsigned char i = 0; i < argc; i++)
		if (equals(ans, argv[i]) == TRUE)
			return i;
	return -1;
}
