
#define MAXINT 100
#define MAXTAB 100
#define NOMBRETRIS 6
#define MAXTAS 1000
#define MAXSTRING 100
#define MAXDOUBLE 100

//______________________________________________________________________________________
typedef enum {SELECTION, INSERTION, BULLES, FUSION, RAPIDE, TAS} enumTri;

typedef enum {RANDOM, TRIE_MOITIER, TRIE, INVERSE, DOUBLONS} enumTable;

typedef enum {PERMUTATION, COMPARAISON, SOMME} enumStat;

typedef struct {
	int t[MAXTAS];
	int p;
} suiteEntiers;


typedef struct {
	enumTri nomTri;
	int taille;
	int comparaisons;
	int permutations;
} stat;

typedef struct {
		int lignes;
		int table[MAXTAB][NOMBRETRIS + 1];
} tableStats;

//__________________________________________________________________________________________
int *tabTrisRandom(int taille);
int *tabTrisMoitier(int taille);
int *tabTrisTrie(int taille);
int *tabTrisInverse(int taille);
int *tabTrisDouble(int taille);
int *tabChoisir(int taille, int choisir);
int choisirStat(stat *st, int choisir);
int testTris(int table[],int taille);
void swap(int table[], int a, int b);
void permuter(int *a, int *b);
stat *creeStat(enumTri t,int taille);
void afficher(int table[], int taille);
int chercheMin(int table[],int d, int taille, stat *st);
void triSelection(int table[],int taille, stat *st) ;
void triInsertion(int table[], int taille, stat *st);
void triBulles(int table[],int taille, stat *st);
int *fusionner(int table1[], int table2[], int taille1, int taille2, stat *st);
int *triFusion(int table[],int d,int f,stat *st);
int partition(int table[],int d, int f, stat *st);
void triRapide(int table[],int d,int f,stat *st);
suiteEntiers *creeTas();
void ajouterElementTas(int n, suiteEntiers *s,stat *st);
int supprimerMax(suiteEntiers *s, stat *st);
int * triTas(int table[], int taille,stat *st);
void plateForm(int taille_mini, int nb_listes, int nb_Expes,tableStats *tabStat, int choisirTable, int choisirSt);
void statitiqueCSV(tableStats *tabSt, FILE *fichier);
void statitiqueDAT(tableStats *tabSt, FILE *fichier);
void statitiqueGNU(FILE *fichier, int choisirStat);

