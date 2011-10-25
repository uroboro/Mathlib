#include "main.h"
#include "cramer.h"

int main(int argc, char **argv){

	int i, j;
	int orden;
	char letra[3]={ 'x', 'y', 'z' };

	printf("incognitas: ");
	scanf("%d", &orden);

	float **matrix=newmatrix(orden);

	//get the matrix
	for(i=0; i<orden; i++)
		for(j=0; j<orden+1; j++){
			printf("[%d,%d]= ", i, j);
			scanf("%f", &matrix[i][j]);
		}

	//print the matrix
	for(i=0; i<orden; i++){
		for(j=0; j<orden; j++){
			printf("%.2f %c ", matrix[i][j], letra[j]);
			if(j<orden-1) printf("+ ");
		}
		printf("= %.2f\n", matrix[i][orden]);
	}
	printf("\n");
	
	float *answer=cramer(matrix, orden);

	//print the answer
	if(answer[orden]==0) printf("infinitas soluciones!\n");
	for(i=0; i<orden; i++)
		printf("%c = %.2f\n", letra [i], answer[i]);
	printf("\n");
	
	return 0;
}
