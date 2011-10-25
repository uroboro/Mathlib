#include "onepow.h"

int onepow(int n){

	int i, c=1;

	for(i=0; i<n; i++) c*=-1;

	return c;
}
