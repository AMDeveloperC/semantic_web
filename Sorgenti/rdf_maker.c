void genRdf(char * context, char * score, FILE * fileOut);
void rdfMaker(char * file, char * path, char * query);
void removeTemp();

int main(int argc, char * argv[]) {
	printf("%s\n", argv[1]);
	printf("%s\n", argv[2]);
	rdfMaker(argv[1], argv[2], argv[3]);
	removeTemp();
	return 0;
}

/*
 * Generate RDF code for single triples
 * Param fileOut state the file to write code
 */
void genRdf(char * context, char * score, FILE * fileOut) {
	int i;
	char * pContext = xmalloc(MAX * sizeof(char *));
	char * pScore = xmalloc(MAX * sizeof(char *));

	if (sprintf(pContext, "\t\t<ex:has_one rdf:resource=\"#%s\">\n", context) < 0) {
		fprintf(stderr, "Error with context %s\n", context);
		exit(-1);
	}
	if (fputs(pContext, fileOut) == EOF) {
		fprintf(stderr, "Error writing context %s\n", context);
		exit(-1);
	}

	if (sprintf(pScore, "\t\t<ex:has_score rdf:datatype=\"&xsd;decimal\"> %s </ex:has_score>", score) < 0) {
		fprintf(stderr, "Error with score %s\n", score);
		exit(-1);
	}
	if (fputs(pScore, fileOut) == EOF) {
		fprintf(stderr, "Error writing score %s\n", score);
		exit(-1);
	}

	free(pContext);
	free(pScore);

	return;
}


/*
 * Crete the ontology instances file template
 * Require the input file
 * Specify path to state output file
 * Specify query to make the ontology
 */
void rdfMaker(char * file, char * path, char * query) {
	FILE * fileInput;
	FILE * fileOutput;
	char * buff = xmalloc(sizeof(char) * MAX);
	char ** splitted = xmalloc(2 * sizeof(char *));
	char * s = xmalloc(sizeof(char) * MAX);

	char * header = "<rdf:RDF xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns:rdfs=\"http://www.w3.org/2000/01/rdf-schema#\" xml:ex=\"http://query.org/\" xml:base=\"http://example.org/\">";

	int dim = 0;
	int numLine = 0;


	if ((fileInput = fopen(file, "r")) == NULL) {
		fprintf(stderr, "Impossible open \t%s\n", file);
		exit(-1);
	}
	if ((fileOutput = fopen(path, "a")) == NULL) {
		fprintf(stderr, "Impossible open \t%s\n", path);
		exit(-1);
	}

	if (fputs("<?xml version = \"1.0\" encoding = \"utf-8\"?>", fileOutput) == EOF) {
		fprintf(stderr, "Impossible write in %s file", path);
		exit(-1);
	}
	if (fputc('\n', fileOutput) < 0) {
		fprintf(stderr, "Impossible write in %s file", path);
		exit(-1);
	}

	if (fputs(header, fileOutput) == EOF) {
		fprintf(stderr, "Impossible write in %s file", path);
		exit(-1);
	}
	if (fputc('\n', fileOutput) == EOF) {
		fprintf(stderr, "Impossible write in %s file", path);
		exit(-1);
	}

	// read until the end of file is reached
	while (fgets(buff, MAX, fileInput) != NULL) {
		buff[strlen(buff)-1] = '\0';
		if ((numLine++) == THRESHOLD)
			break;
		sprintf(s, "\t<ex:query rdf:ID=\"%s\">\n", query);
		fputs(s, fileOutput);
		splitted = split(buff, "\t", &dim);
		genRdf(splitted[0], splitted[1], fileOutput);
		fputc('\n', fileOutput);
		dim = 0;
		fputs("\t</ex:query>\n", fileOutput);

	}
	fputs("</rdf:RDF>", fileOutput);

	free(buff);
	free(splitted);

	fclose(fileInput);
	fclose(fileOutput);
	return;
}


/*
 * Remove temporary files
 */
void removeTemp() {
	execlp("rm", "rm", TEMPORANEOUNO, TEMPORANEODUE, NULL);
}
