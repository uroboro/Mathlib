#ifndef LISTLIB_H
#define LISTLIB_H

#include "mtxnode.h"
#include "mnlib.h"

/* Prompts an interface asking for a number to search
 * the corresponding matrix with that index.
 * The letter argument allows to indicate, if necessary,
 * a character to identify a matrix.
 * If letter is '\0' or 0, the interface will say
 * "#Matrix (...): "; otherwise, if letter is a valid character
 * the it will say something like "#Matrix 1(...): ". '...'
 * is a list with the indexes of the matrices in list.
 */
mtxnode *listFind(mtxnode *list, char letter);

#endif
