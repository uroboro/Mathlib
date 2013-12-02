#include "equals.h"

bool equals(const char *str, const char *var) {
	if (str == var)
		return TRUE;
	int i;
	//checks if str has the same chars of var up to '\0'
	for (i = 0; var[i] != '\0'; i++)
		if (str[i] != var[i])
			return FALSE;
	//checks if str ends when var does
	if (str[i] != var[i])
		return FALSE;
	return TRUE;
}
