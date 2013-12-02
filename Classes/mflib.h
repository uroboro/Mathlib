#ifndef MTXFILE_H
#define MTXFILE_H

#include <stdio.h>
#include <stdlib.h>

#include "mtx.h"
#include "mtxnode.h"
#include "mnlib.h"

/*
 * Files where matrices are saved will contain a readable format:
 * (%d,%d){{%f,%f}{%f,%f}}
 * As long as this format is maintained, it will be possible to edit matrices from outside the program.
 */

/* Possible return values:
 * 0 if no errors,
 * 1 if no file at "path",
 * 2 if no matrix in file or matrix is NULL.
 * 3 if the file contains a wrong format
 */

#define NO_ERRORS			0
#define ERROR_NO_FILE		1
#define ERROR_NO_MATRIX 	2
#define ERROR_WRONG_FORMAT	3
#define ERROR_EMPTY_FILE	4


//save and load individual matrices
int mfSaveMatrixToFile(matrix *self, char *path);
int mfLoadMatrixFromFile(matrix *self, char *path);

void mfMatrixIO(char *path, matrix **self, char mode);

//save and load lists of matrices
int mfSaveMatricesToFile(mtxnode **list, char *path);
int mfLoadMatricesFromFile(mtxnode **list, char *path);

int mfListIO(char *path, mtxnode **list, char mode);

#endif
