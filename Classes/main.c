#include "menu.h"
#include "list.h"

int main(int argc, char **argv){
/*
	char *aptv[] = { "array", "stack", "queue", "list", "-h", "--help" };
	int aptc = sizeof(aptv) / sizeof(char *);;
	char *optv[] = { "array", "stack", "queue", "list" };
	int optc = sizeof(optv) / sizeof(char *);

	if (argc != 1)
		switch(autoMenu(aptc, aptv, argv[1])) {
		case 0:
			mainArray();
			break;
		case 1:
			//stack();
			break;
		case 2:
			//queue();
			break;
		case 3:
			mainList();
			break;
		case 4:
		case 5:
			printf("#Help\n");
			break;
		}
	else
		switch(autoMenu(optc, optv, NULL)) {
		case 0:
			mainArray();
			break;
		case 1:
			//stack();
			break;
		case 2:
			//queue();
			break;
		case 3:
			mainList();
			break;
		}
*/

	mainList();

	return 0;
}
