#ifndef MTXNODELIB_H
#define MTXNODELIB_H

#include <stdio.h>
#include <stdlib.h>
#include "mtxnode.h"
#include "mtxlib.h"

/* FindByX
 * These functions will search for a node containing the matrix given by index or the matrix itself.
 * If there is no matrix to be found, they return NULL; otherwise, the node containing it.
 */
mtxnode *mnFindByIndex(mtxnode *node, int index);
mtxnode *mnFindByData(mtxnode *node, matrix *self);

/*
 * mnFindNextAvailable() is used internally by mnPush()
 * It will return:
 * NULL if the list is empty;
 * a mtxnode pointer;
 *
 * If you are going to use it, check if there is another node after it.
 */
mtxnode *mnFindNextAvailable(mtxnode *node);

// Ordered list functions

void mnPush(mtxnode **node, matrix *self);
void mnPop(mtxnode **node, int index);

void mnShow(mtxnode *node);
void mnShowAll(mtxnode *node);

void mnFree(mtxnode *node);
void mnDump(mtxnode **node);

void mnUpdateAll(mtxnode *node);

long int mnMemory(mtxnode *node);
// Returns the number of matrices loaded in a list
char mnCount(mtxnode *node);
/* Returns an array with the indexes of the matrices in a list.
 * The first position is the number of matrices in the list.
 */
char *mnList(mtxnode *node);
// Returns string with the indexes of the matrices in a list.
char *mnEnumerate(mtxnode *node);

//end of ordered list functions

// matrix functions
//1 matrix functions
void mnPrint(mtxnode *node);
void mnProperties(mtxnode *node);
void mnUpdate(mtxnode *node);

//These return the node in which the new matrix is stored.
mtxnode *mnOpposite(mtxnode **list, mtxnode *node);
mtxnode *mnTranspose(mtxnode **list, mtxnode *node);
mtxnode *mnAdjugate(mtxnode **list, mtxnode *node);
mtxnode *mnInverse(mtxnode **list, mtxnode *node);

//2 matrix functions
/* Linear matrix operations
 * sourceA operation sourceB
 * op must be '+', '-', '*' OR '/'.
 *
 * The same way you add and subtract matrices, this funtion
 * will multiply and divide. Watch out for zeroes in sourceB.
 */
mtxnode *mnLinearOp(mtxnode **node, mtxnode *nodeA, char op, mtxnode *nodeB);
//Traditional matrix multiplication.
mtxnode *mnVMultiply(mtxnode **node, mtxnode *nodeA, mtxnode *nodeB);
//Multiplication by a float.
mtxnode *mnSMultiply(mtxnode **node, mtxnode *nodeA, float scalar);

// Evaluation
bool mnEquals(mtxnode *nodeA, mtxnode *nodeB);
//returns TRUE if successful
//ignored
bool mnCopy(mtxnode *nodeA, mtxnode *nodeB);

//end of matrix functions

#endif
