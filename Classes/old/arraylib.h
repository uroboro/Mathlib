#ifndef ARRAYLIB_H
#define ARRAYLIB_H

#include "mtxlib.h"

matrix *arrayFind(matrix **matrices, char letter, int max);
matrix *arrayShow(matrix *sender, int *count);
void arrayFree(matrix **matrices, int count);

#endif
