#include "mtxinput.h"

matrix *mtxInput() {
	int m, n;
	float scalar;
	int minSize = 1, maxSize = 8;
	char *buf = (char *) malloc(16 * sizeof(char));
	matrix *sender;// = (matrix *) malloc(sizeof(matrix));

	do {
		printf("#Is squared(y/n): ");
		scanf("%s", buf);
	} while ( ! equals(buf, "y") && ! equals(buf, "n")); //safety

	do {
		printf("#Width(1-%d): ", maxSize);
		scanf("%d", &m);
	} while (m < minSize || m > maxSize); //safety

	if (equals(buf, "y"))
		n = m;
	else
		do {
			printf("#Hight(1-%d): ", maxSize);
			scanf("%d", &n);
		} while (n < minSize || n > maxSize); //safety

	sender = mtxNew(m, n);

	do {
		printf("#Start initialized or set manually (i/m): ");
		scanf("%s", buf);
	} while ( ! equals(buf, "i") && ! equals(buf, "m")); //safety

	if (equals(buf, "i")) {
		do {
			printf("#As identity or same numbers (i/n): ");
			scanf("%s", buf);
		} while ( ! equals(buf, "i") && ! equals(buf, "n")); //safety
		if (equals(buf, "i"))
			mtxInitAsId(sender);
		else {
			printf("#Scalar: ");
			scanf(SCANTYPE, &scalar);
			mtxInitWithScalar(sender, scalar);
			}
		}
	else
		mtxScan(sender);

	mtxUpdate(sender);
	return sender;
}
