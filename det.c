/*
Given: | a b |
	   | c d |

This function returns (a*d-b*c), which is the determinant of a 2x2 matrix.
*/
#include "det.h"

float det(float **matrix){

	return (matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0]);
}
