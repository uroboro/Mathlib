#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include "equals.h"

/* Text interface
 *
 * Both functions must be supplied with the number of items
 * and the array of strings from which to check the answer.
 * menu() prompts the user with a list of options.
 * autoMenu() searches for the given answer.
 *
 * Return values:
 * -4		the answer is NULL.
 * -3		the array is NULL.
 * -2		the number is less than 1.
 * -1		the answer is not in the list.
 * an int	which is the index of the option.
 */
int menu(int argc, char **argv);
int autoMenu(int argc, char **argv, char *ans);

#endif
