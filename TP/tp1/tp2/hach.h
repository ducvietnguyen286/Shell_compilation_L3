#include <stdio.h>
#define MAXCH 26
#define MAXCLE 26
#define MAXCHAR 1000
# define MAXDOCS 100
#define Nouveau(type) (type*)malloc(sizeof(type));

//structure______________________________________________________________________________________
typedef struct {
	char *nomDoc;
	int nbMots;
} Document;

typedef struct {
	int nbDocs;
	Document* (documents[MAXDOCS]);
} ListeDocs;

typedef struct cel{
	char mot[MAXCH];
	int freq[MAXDOCS];
	struct cel *suivant;
} cellule;

typedef cellule* ListChainee;

typedef ListChainee Table[MAXCLE];
//______________________________________________________________________________________________

int minuscule(char c);
int majuscule(char c);
int estLettre(char c);
char lettreVersMajuscule (char c);
char *motVersMajuscule(char *mot);
FILE *ouvrirFichier(char * chaine);
char *prochainMot(FILE* file);
int hash(char* mot);
void ajouterMotListeChainee(ListChainee *l, char *m, int indDoc);
void ajouterMotsTable(FILE *file, Table t/*,ListeDocs *liste*/);

