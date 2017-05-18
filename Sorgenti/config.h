# define MAX 100
# define THRESHOLD 7
# define NOMI     "../Dataset/nomi.txt"
# define CONTESTI "../Dataset/contesti.txt"
# define MATRICE  "../Dataset/matrice.txt"
# define PATHOUT  "../Risultati/"
# define RDFMAKER "./RdfMaker"
# define DRIVER "./driver.py"
# define PYTHON "python"
# define TEMPORANEOUNO "../Temporanei/tmp1.txt" 
# define TEMPORANEODUE "../Temporanei/tmp2.txt" 

/*
 * Remove the character c from the string s
 * Returns the modified string
 */
char * removeChar(char * s, char c);

/*
 * Splits a string into token separated by sep
 * Returns a vector with separated token
 */
char ** split(char * str, char * sep, int * dim);


/* Check if malloc is return correct value */
static void * xmalloc (int nbytes);
