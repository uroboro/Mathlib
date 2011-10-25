/*
This is a header file containing commonly used headers and type sizes for ease of use.

Developed by Federico Sandri <uroboro.845@gmail.com>
*/
#ifndef MAIN_H_
#define MAIN_H_

//standard headers
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//open()
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

//read(), write(), close()
#include <unistd.h>

//time
#include <time.h>

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long ulong;

//sizeof(type)
#define INT_S   	sizeof(int)
#define UINT_S  	sizeof(uint)
#define CHAR_S  	sizeof(char)
#define UCHAR_S 	sizeof(uchar)
#define LONG_S  	sizeof(long)
#define ULONG_S 	sizeof(ulong)
#define FLOAT_S 	sizeof(float)
#define DOUBLE_S	sizeof(double)

//sizeof(pointer type)
#define INTP_S  	sizeof(int *)
#define UINTP_S 	sizeof(uint *)
#define CHARP_S 	sizeof(char *)
#define UCHARP_S	sizeof(uchar *)
#define LONGP_S 	sizeof(long *)
#define ULONGP_S	sizeof(ulong *)
#define FLOATP_S	sizeof(float *)
#define DOUBLEP_S	sizeof(double *)

//BOOL
typedef enum { FALSE, TRUE } bool;

//cartesian coordinates
typedef struct {
	float x, y, z;
	} cartesian;

//matrix
typedef struct {
	int m;//rows
	int n;//columns
	int o;//shelves?
	} dimension;// para R mxn

typedef struct{
	void **ptr;
	dimension order;
	char *type;
} matrix;

#endif /*MAIN_H_*/
