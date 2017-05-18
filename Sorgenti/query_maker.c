# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "config_impl.h"

char * displayMenu();
void preprocessingQuery(char * query);

int main(void) {
	int pid;

	char answare[2];
	char * q = displayMenu();
	preprocessingQuery(q);
	execlp(PYTHON, PYTHON, DRIVER, NOMI, CONTESTI, MATRICE, NULL); // performing LSA

	return 0;
}

/* Shows the menu to user */
char * displayMenu() {
	char * query = (char *) xmalloc(MAX * sizeof(char));
	printf("------------------------------ Welcome ------------------------------");
	putchar('\n');
	printf("Insert a query for the dataset\n");
	printf("> ");

	if(fgets(query, MAX, stdin) == NULL) {
		fprintf(stderr, "Impossibile to read the query\n");
		exit(-1);
	}
	if (strcmp(query, "-1\n") == 0) {
		fprintf(stdout, "Bye\n");
		exit(0);
	}

	return query;
}

/* Perform a simple preprocessing on the string read from input */
void preprocessingQuery(char * query) {
	FILE * tmp;
	FILE * mtmp;
	char * modified;
	char * buff;
	int dim;
	int i;
	char ** separated;

	// initialization
	tmp = fopen(TEMPORANEOUNO, "a");
	mtmp = fopen(TEMPORANEODUE, "a");
	modified = (char *) xmalloc(MAX * sizeof(char));
	buff = xmalloc(sizeof(char) * MAX);
	dim = 0;
	separated = split(query, " ", &dim);

	for (i = 0; i < dim; i++) {
		if (fputs(separated[i], tmp) < 0) {
			fprintf(stderr, "Impossible to write \"../Temporanei/tmp1.txt\"");
			exit(-1);
		}
		if (i != dim - 1) { 
			if (fputc('\n', tmp) == EOF) {
				fprintf(stderr, "Problem with \"../Temporanei/tmp1.txt\"");
				exit(-1);
			}
		}
	}

	fclose(tmp);
	tmp = fopen(TEMPORANEOUNO, "r");
	while (fgets(buff, MAX, tmp) != NULL) {
		modified = removeChar(buff, '_');
		fputs(modified , mtmp);
	}
	fclose(tmp);
	fclose(mtmp);

	printf("Preprocessing succesful executed\n");
	return;
}
