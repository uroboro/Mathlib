MatrixLib
=========

Brief overview:
Matrix library written in C that is able to manage bidimensional matrices and provide information about them. It is possible to operate with the basic functions such as inversion, transposition, multiplication and determinant.

Features:
+ single matrix struct containing:
 - float matrix
 - size
 - properties in Boolean format
+ ordered list manager:
 - add matrices with the following options:
  * input manually
  * initialise as identity
  * initialise with one number
 - remove them from memory
 - show single matrices
 - show the complete list of matrices
+ autosave and autoload matrices for later usage
+ functions that inform if a matrix is:
 - symmetrical
 - antisymmetrical
 - triangular
 - diagonal
 - identity
 - orthogonal
+ functions that operate with a single matrix:
 - opposite
 - transpose
 - adjugate
 - invert
 - multiply (by a scalar number)
+ functions that operate with two matrices
 - add/subtract
 - multiply
 - multiply/divide like addition/subtraction
 - copy
 - check equality

History:
I began coding this library in July 2011, when I had half a year of coding in C experience. But back then I started with a program that only calculated the determinant of any given square matrix. It used float pointers and an int to know the size.
In September I decided to go a step further and incorporate other matrix functions, as well as structs for ease of use, having the pointer and size in a single variable.

To-do list:

- "translate" into Obj-C, into iPhone app.
- functions for column and row spaces.
- resolve n eqs with n vars (using Cramer and the inverse of A in A*X=B, X=Inv(A)*B.
- make mflib.c into dylib, opening the way to a plugin system.
- modify mtxlib.c functions so that they take an int and a matrix array. then, functions like addition can add several matrices at a time.
- add a zero sign checker so as to not have -0 values
- make mtxnode have (void*)data so it is reusable