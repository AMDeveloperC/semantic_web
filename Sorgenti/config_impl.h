# include <string.h>
# include "config.h"


/** Remove the character c from string s */
char * removeChar(char * s, char c) {
	char * modified = xmalloc(strlen(s) * sizeof(char));
	int i;

	for (i = 0; i < strlen(s); i++)
		if (s[i] != c)
			modified[i] = s[i];
		else
			modified[i] = ' ';

	return modified;
}


/** Returns an array containing separated token by sep string */
char ** split(char * str, char * sep, int * dim) {
	char * app = strdup(str);
	char * token;
	char ** vect = xmalloc(MAX * sizeof(char *));

	while ((token = strsep(&app, sep)) != NULL)
		vect[(*dim)++] = strdup(token);

	free(token);
	free(app);
	return vect;
}


/**
 * Try to allocate space with malloc functtion
 * An interrupt is generated if an error occurred
 **/
static void * xmalloc(int nbytes) {
	void * result;

	if((result = malloc(nbytes)) == NULL) {
		fprintf(stderr, "malloc(%d) failed. Exiting.\n", nbytes);
		exit(-1);
	}
	return result;
}
