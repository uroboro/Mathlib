#ifndef MTXNODE_H
#define MTXNODE_H

#include "mtx.h"

typedef struct mtxnode {
	int index;
	matrix *data;
	struct mtxnode *prev, *self, *next;
} mtxnode;

#endif
