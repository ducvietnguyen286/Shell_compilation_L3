#define MAXINT 1000
#define MAXTAB 100
#define NBTRIS 6
#define MAXTAS 10000
#define MAXSTR 100
#define MAXDOUBLONS 20


//________________________________________________________________________________________
typedef struct {
	int t[MAXTAS];
	int p;
} suiteEntiers;

typedef enum {SELECTION, INSERTION, BULLES, FUSION, RAPIDE, TAS} tri;

typedef enum {NORMAL, TRIE, INVERSE, DOUBLONS} typetab;

typedef enum {PERMUTATION, COMPARAISON, TOUT} typeStat;

typedef struct {
	tri nomTri;
	int taille;
	int permutations;
	int comparaisons;
} stat;

typedef struct {
		int lignes;
		int tab[MAXTAB][NBTRIS + 1];
} tabStats;

//________________________________________________________________________________________
int *creerTab(int taille);
int *tabTris(int taille);
int *tabInverse(int taille);
int *tabDoublons(int taille);
int *tabChoisir(int taille, int choix);
int choisirStat(stat *st, int choix);
int testTris(int table[],int taille);
void swap(int table[], int a, int b);
void permuter(int *x, int *y);
stat *genererStat(tri tr,int taille);
suiteEntiers *genererTas();
void afficher(int table[], int taille);
void afficherTas(suiteEntiers *s);
int chercheIndMin(int tab[],int debut, int taille, stat *st);
void triSelection(int tab[],int taille, stat *st);
void triInsertion(int tab[], int taille, stat *st);
void triBulles(int tab[],int taille, stat *st);
int *fusionner(int tab1[], int tab2[], int taille1, int taille2, stat *st);
int *triFusion(int tab[],int debut,int fin,stat *st);
int partitionner(int tab[],int debut, int fin,stat *st);
void triRapide(int tab[],int debut,int fin,stat *st);
void ajouteElemTas(int x, suiteEntiers *s,stat *st);
int supprimerMax(suiteEntiers *s, stat *st);
int *triTas(int tab[], int taille,stat *st);
void plateForm(int taille_mini, int nb_listes, int nb_Expes,tabStats *tabStat, int choisirTab, int choisirSt);
void statsCSV(tabStats *tabSt, FILE *fichier);
void statsDAT(tabStats *tabSt, FILE *fichier);
void statsGNU(FILE *fichier, int choisirStat);
