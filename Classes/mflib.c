#include "mflib.h"

#define MTX_SIZE	"(%d,%d)"

int mfSaveMatrixToFile(matrix *self, char *path) {
	FILE *fp = fopen(path, "r");
	if (fp == NULL)
		return ERROR_NO_FILE;
	fclose(fp);
	fp = fopen(path, "w");

	if (self == NULL)
		return ERROR_NO_MATRIX;
	matrix *aux = self;

	fprintf(fp, MTX_SIZE, aux->m, aux->n);

	fprintf(fp, "{");

	for (unsigned char i = 0; i < aux->m; i++) {
		fprintf(fp, "{");
		for (unsigned char j = 0; j < aux->n; j++) {
			fprintf(fp, "%f", aux->mtx[i][j]);
			if (j < aux->n - 1)
				fprintf(fp, ",");
		}
		fprintf(fp, "}");
	}

	fclose(fp);
	return NO_ERRORS;
}
int mfLoadMatrixFromFile(matrix *self, char *path) {
	FILE *fp = fopen(path, "r");
	if (fp == NULL)
		return ERROR_NO_FILE;

	if (self == NULL)
		return ERROR_NO_MATRIX;

	matrix *aux = self;

	int m, n;
	if (fscanf(fp, MTX_SIZE, &m, &n) == -1)
		return ERROR_WRONG_FORMAT;
	if (m < 1 || m > 255 || n < 1 || n > 255)
		return ERROR_WRONG_FORMAT;
	aux->m = (char) m;
	aux->n = (char) n;

	if (fscanf(fp, "{") == -1)
		return ERROR_WRONG_FORMAT;

	for (unsigned char i = 0; i < aux->m; i++) {
		if (fscanf(fp, "{") == -1)
			return ERROR_WRONG_FORMAT;

		for (unsigned char j = 0; j < aux->n; j++) {
			if (fscanf(fp, "%f", &aux->mtx[i][j]) == -1)
				return ERROR_WRONG_FORMAT;

			if (j < aux->n - 1)
				if (fscanf(fp, ",") == -1)
					return ERROR_WRONG_FORMAT;

		}

		if (fscanf(fp, "}") == -1)
			return ERROR_WRONG_FORMAT;

	}

	if (fscanf(fp, "}") == -1)
		return ERROR_WRONG_FORMAT;

	fclose(fp);
	return NO_ERRORS;
}

int mfSaveMatricesToFile(mtxnode **list, char *path) {
	FILE *fp = fopen(path, "r");
	fclose(fp);
	fp = fopen(path, "w");

	if (*list == NULL)
		return ERROR_NO_MATRIX;

	for (mtxnode *aux = *list; aux != NULL; aux = aux->next) {
//		fprintf(fp, "%d", aux->index);
		fprintf(fp, MTX_SIZE, aux->data->m, aux->data->n);

		fprintf(fp, "{");
		for (unsigned char i = 0; i < aux->data->m; i++) {
			fprintf(fp, "{");
			for (unsigned char j = 0; j < aux->data->n; j++) {
				fprintf(fp, "%f", aux->data->mtx[i][j]);
				if (j < aux->data->n - 1)
					fprintf(fp, ",");
			}
			fprintf(fp, "}");
		}
		fprintf(fp, "}");
		if (aux->next != NULL)
			fprintf(fp, ":");
	}
	fprintf(fp, ";\n");

	fclose(fp);
	return NO_ERRORS;
}
int mfLoadMatricesFromFile(mtxnode **list, char *path) {
	FILE *fp = fopen(path, "r");
	if (fp == NULL)
		return ERROR_NO_FILE;

	if (feof(fp))
		return ERROR_EMPTY_FILE;

	matrix *aux;
	int m, n;
	unsigned char c;

	while (!feof(fp)) {
		if (fscanf(fp, MTX_SIZE, &m, &n) == -1)
			return ERROR_WRONG_FORMAT;
		if (m < 1 || m > 255 || n < 1 || n > 255)
			return ERROR_WRONG_FORMAT;
		aux = mtxNew(m, n);
		aux->mtx = ptrNew(aux->m, aux->n);

		if (fscanf(fp, "{") == -1)
			return ERROR_WRONG_FORMAT;
		for (unsigned char i = 0; i < aux->m; i++) {

			if (fscanf(fp, "{") == -1)
				return ERROR_WRONG_FORMAT;
			for (unsigned char j = 0; j < aux->n; j++) {
				fscanf(fp, "%f", &aux->mtx[i][j]);

				if (j < aux->n - 1)
					if (fscanf(fp, ",") == -1)
						return ERROR_WRONG_FORMAT;
			}

			if (fscanf(fp, "}") == -1)
				return ERROR_WRONG_FORMAT;
		}

		if (fscanf(fp, "}") == -1)
			return ERROR_WRONG_FORMAT;
		mnPush(list, aux);

		fscanf(fp, "%c", &c);
		if (c == ':')
			continue;
		if (c == ';')
			return NO_ERRORS;
		else
			return ERROR_WRONG_FORMAT;
	}

	fclose(fp);
	return NO_ERRORS;
}

int mfListIO(char *path, mtxnode **list, char mode) {
	char *verb, *Verb, *direction;
	unsigned char error;
	char *errorList[] = { "", "Unable to open file.", "Empty list.", "Corrupt format in file.", "Empty file." };
	int (*mfIO)(mtxnode **, char *);
	switch (mode) {
	case 's':
		Verb = "Saving";
		verb = "saving";
		direction = "to";
		mfIO = mfSaveMatricesToFile;
		break;
	case 'l':
		Verb = "Loading";
		verb = "loading";
		direction = "from";
		mfIO = mfLoadMatricesFromFile;
		break;
	default:
		return -1;
	}

	fprintf(stdout, "#%s matrices %s \"%s\"...\n", Verb, direction, path);
	error = mfIO(list, path);

	if (error == NO_ERRORS )
		fprintf(stdout, "#No problems while %s.\n", verb);
	else
		fprintf(stdout, "#Found problems %s %s \"%s\": %s.\n", verb, direction, path, errorList[error]);

	return 0;
}
