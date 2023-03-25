#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<assert.h>
#include"trie.h"
// cree table ____________________________________________________________________________________
int *tabTrisRandom(int taille){
	assert(taille > 1);
	int *table=(int*)malloc(taille * sizeof(int));
	int i;
	for(i = 0; i < taille; i++)
		table[i]=rand() % MAXINT;
	return table;
}

int *tabTrisMoitier(int taille){
	int i;
	int j= (taille-1)/2;
	int *table = (int*)malloc(taille*sizeof(int));
	for(i=0; i<taille; i++){
		table[i]=rand()%MAXINT;
		if(i>0 && i<=j && table[i]<table[i-1]){
			swap(table,i,i-1);
		}				
	}
	return table;
}

int *tabTrisTrie(int taille){
	assert(taille>1);
	int *table=(int*)malloc(taille*sizeof(int));
	int i;
	for (i = 0; i < taille; i++)
		table[i]=i;
	return table;
}

int *tabTrisInverse(int taille){
	assert(taille>1);
	int *table =(int*)malloc(taille*sizeof(int));
	int i;

	for(i=0;i<taille;i++)
		table[i] = taille - i -1;

	return table;
}

int *tabTrisDouble(int taille){
	assert(taille>1);
	int *table = (int*)malloc(taille*sizeof(int));
	int i,j,v;
	for (i = 0; i<taille ; i++){
		v = rand()%MAXINT;
		for(j=0; j < MAXDOUBLE && i < taille; i++, j++){
			table[i]=v;
		}
	}
	return table;
}

//choisir la type de la table______________________________________________________________
int *tabChoisir(int taille, int choisir){
	int *table;

	if (choisir == RANDOM)
		table = tabTrisRandom(taille);
	if (choisir == TRIE_MOITIER)
		table = tabTrisMoitier(taille);
	else if (choisir == TRIE)
		table =tabTrisTrie(taille);
	else if (choisir == INVERSE)
		table = tabTrisInverse(taille);
	else if (choisir == DOUBLONS)
		table = tabTrisDouble(taille);
	
	return table;
}

// choisir type de stat_________________________________________________________________________
int choisirStat(stat *st, int choisir){
	int statistique;
	if (choisir == PERMUTATION)
		statistique = st->permutations;
	else if (choisir == COMPARAISON)
		statistique = st->comparaisons;
	else if (choisir == SOMME)
		statistique = (st->permutations) + (st->comparaisons);
	return statistique;
}

//test trie______________________________________________________________________________________
int testTris(int table[],int taille)
{
	assert(taille>1);
	int i;
	
	for (int i = 0; i < taille-1; i++)
	{
		 if (table[i]>table[i+1])
		 	return 0;
	}
	return 1;
}

//echqnger_______________________________________________________________________________________
void swap(int table[], int a, int b){
	int i = table[a];
	table[a]=table[b];
	table[b]=i;
}

void permuter(int *a, int *b){
	int i = *a;
	*a=*b;
	*b=i;
}

//cree de la stat _____________________________________________________________________________________
stat *creeStat(enumTri t,int taille){
	assert(taille > 1);
	stat *st = (stat*)malloc(sizeof(stat));
	st->nomTri = t;
	st->taille = taille;
	st->permutations = 0;
	st->comparaisons = 0;
	return st;
}

//afficher__________________________________________________________________________________
void afficher(int table[], int taille){
	int i=0;
	printf("\n");
	for ( i = 0; i < taille; i++)
		printf("%d ",table[i]);
}

// ____tris par selection ________________tim phan tu nho nhat_____________________________________

int chercheMin(int table[],int d, int taille, stat *st){
	assert((taille > 1)&&(d>=0));
	int i, mini = d;
	for(i=1+d;i<taille;i++){
		(st->comparaisons)++;
		if(table[i] < table[mini])
			mini = i;
	}
	
	return mini;
} 


void triSelection(int table[],int taille, stat *st) {
	assert(taille > 1);
	int i;
	for(i=0; i < taille-1; i++){
		swap(table, i, chercheMin(table,i,taille, st));
		(st->permutations)++;
	}
}

//tris par insertion_______________________________________________________________
void triInsertion(int table[], int taille, stat *st){
	assert(taille > 1);
	int p;
	for(p=1;p<taille;p++){
		while(p > 0 && table[p-1]>table[p]){
			swap(table, p -1, p);
			(st->permutations)++;
			p--;
		}
		if (p > 0)
			(st->comparaisons)++;
	}
}

//tris bulle _____________________________________________________________
void triBulles(int table[],int taille, stat *st){
	assert(taille>1);
	int permute = 1, i;
	while(permute){
		permute=0;
		for(i=0; i<taille-1;i++){
			(st->comparaisons)++;
			if(table[i]>table[i+1]) {
				swap(table,i,i+1);
				(st->permutations)++;
				permute=1;
			}
		}
	}
}

//Tris fusion_________________________________________________________________________________
int *fusionner(int table1[], int table2[], int taille1, int taille2, stat *st)
{
	assert((taille1>=1)&&(taille2>=1));
	int in1 =0, in2 =0;
	int *fu=(int*) malloc((taille1+taille2)*sizeof(int));
	
	while(in1 < taille1 && in2 < taille2){
	
		if (table1[in1]<table2[in2]){
			fu[in1+in2]=table1[in1];
			in1++;
		}

		else{
			fu[in1+in2]=table2[in2];
			in2++;
		}
		(st->permutations)++;
		(st->comparaisons)++;

	}

	if(in2 == taille2){
		while(in1<taille1){
			fu[in1+in2]=table1[in1];
			(st->permutations)++;
			in1++;
		}

	}
	else if(in1==taille1){
		while(in2 < taille2){	
			fu[in1+in2]=table2[in2];
			(st->permutations)++;
			in2++;
		}
	}
	return fu;
}

int *triFusion(int table[],int d,int f,stat *st){
	assert((d >=0) && (f >= 0));
	int *s, *in1, *in2;
	int m = (d + f)/2;
	if(d == f){
		s = (int*)malloc(sizeof(int));
		s[0] = table[d];
		return s;
	}
	else{
		in1 = triFusion(table, d, m,st);
		in2 = triFusion(table, m+1, f,st);
		return fusionner(in1, in2, m -d +1,f-m, st);
	}
}

//Tris rapide ________________________________________________________________
int partition(int table[],int d, int f, stat *st)
{
	assert((d>=0) && (f>=0));
	int pivot = table[d];
	int gauche = d +1, droite = f;
	int fini = 0;
	while(!fini){
		while (gauche <= droite && table[gauche]<=pivot){
			(st->comparaisons)++;
			gauche++;
		}
		while (droite >= gauche && table[droite]>=pivot){
			(st->comparaisons)++;
			droite--;
		}
		if(droite<gauche){
			fini = 1;
		}
		else{
			
			swap(table, gauche,droite);
			(st->permutations)++;
			(st->comparaisons)++;
			
		}
	}
	swap(table,d,droite);
	(st->permutations)++;
	return droite;
}

void triRapide(int table[],int d,int f,stat *st)
{
	assert((f >= -1)&&(d >= -1) );
	int pivot;
	if (d < f){
		pivot = partition(table, d,f, st);
		triRapide(table, d,pivot -1, st);
		triRapide(table, pivot + 1, f,st);
	}
}

//Tri par tas_________________________________________________________________________
suiteEntiers *creeTas(){
	suiteEntiers *s;
	s = (suiteEntiers*)malloc(sizeof(suiteEntiers));
	s->p = 0;
	return s;
}

void ajouterElementTas(int n, suiteEntiers *s,stat *st){
	int i;

	s->t[s->p] = n;
	(s->p)++;

	i = (s->p) - 1;

	while (i > 0 && s->t[i] > s->t[(i-1) / 2]){
		permuter(&(s->t[i]), &(s->t[(i-1) / 2]));
		i = (i - 1) / 2;
		(st->comparaisons)++;
		(st->permutations)++;
	}
	if(i>0)
		(st->comparaisons)++;
}

int supprimerMax(suiteEntiers *s, stat *st){
	int i = 0, j, max, deplace, f = 0;

	max = s->t[0];

	s->t[0] = s->t[(s->p) - 1];
	(s->p)--;

	deplace = s->t[0];

	while (f != 1 && 2*i+1 < s->p){
		j = 2*i + 1;
		if(j+1 < s->p && s->t[j+1] > s->t[j]){
			(st->comparaisons)++;
			j++;
		}
		if(j < s->p)
			(st->comparaisons)++;

		if(deplace > s->t[j])
			f = 1;
		
		if(f == 0){
			s->t[i] = s->t[j];
			i = j;
			(st->permutations)++;
		}
	}

	s->t[i] = deplace;

	(st->permutations)++;

	return max;
}

int * triTas(int table[], int taille,stat *st){
	assert(taille > 1);
	int i, j;
	suiteEntiers *s = creeTas();
	int *trie = (int*)malloc(taille * sizeof(int));
	for(i=0; i < taille; i++)
	{
		ajouterElementTas(table[i],s,st);
	}
	for(j = taille -1; j>= 0; j--){
		trie[j] = supprimerMax(s,st);
	}
	return trie;

}
//creation du table plateForm________________________________________________________________
void plateForm(int taille_mini, int nb_listes, int nb_Expes,tableStats *tabStat, int choisirTable, int choisirSt){
	assert((taille_mini > 1)&&(nb_listes > 0)&&(nb_Expes > 0));
	int i, j, k, taille;

	for (int i = 0; i < nb_listes; i++)
	{
		taille = taille_mini + i * taille_mini;
		tabStat->table[i][0]=taille;
		for(j=1;j<=NOMBRETRIS;j++){
			tabStat->table[i][j]=0;
		}

		for (int k = 0; k < nb_Expes; k++)
		{
			int *tabSelection = tabChoisir(taille, choisirTable);
			int *tabInsertion = tabChoisir(taille, choisirTable);
			int *tabBulles = tabChoisir(taille, choisirTable);
			int *tabRapide = tabChoisir(taille, choisirTable);
			int *tabFusion = tabChoisir(taille, choisirTable);
			int *tabTas = tabChoisir(taille, choisirTable);


			stat *statSelection = creeStat(SELECTION,taille);
			stat *statInsertion = creeStat(INSERTION,taille);
			stat *statBulles = creeStat(BULLES,taille);
			stat *statFusion = creeStat(FUSION,taille);
			stat *statRapide = creeStat(RAPIDE,taille);
			stat *statTas = creeStat(TAS,taille);

			

			//tri des table
			triSelection(tabSelection,taille,statSelection);
			assert(testTris(tabSelection,taille));

			triInsertion(tabInsertion,taille,statInsertion);
			assert(testTris(tabInsertion,taille));

			triBulles(tabBulles,taille,statBulles);
			assert(testTris(tabBulles,taille));

			assert(testTris(triFusion(tabFusion ,0 ,taille-1, statFusion),taille));

			triRapide(tabRapide,0,taille-1,statRapide);
			assert(testTris(tabRapide,taille));

			assert(testTris(triTas(tabTas, taille, statTas), taille));

			// lay so lieu stat_____________________________________________________________
			tabStat->table[i][SELECTION + 1] += choisirStat(statSelection,choisirSt);
			tabStat->table[i][INSERTION + 1] += choisirStat(statInsertion,choisirSt);
			tabStat->table[i][BULLES + 1] += choisirStat(statBulles,choisirSt);
			tabStat->table[i][FUSION + 1] += choisirStat(statFusion,choisirSt);
			tabStat->table[i][RAPIDE + 1] += choisirStat(statRapide,choisirSt);
			tabStat->table[i][TAS + 1] += choisirStat(statTas,choisirSt);

			free(tabSelection);
			free(tabInsertion);
			free(tabBulles);
			free(tabFusion);
			free(tabRapide);
			free(tabTas);

			free(statSelection);
			free(statInsertion);
			free(statBulles);
			free(statFusion);
			free(statRapide);
			free(statTas);
			

		}

		for(j=1; j <=  NOMBRETRIS;j++)
			tabStat->table[i][j] /= nb_Expes;
	}
	tabStat->lignes =nb_listes;
}

//test tris____________________________________________________________________________________________________________________
/*void plateforme(int taille_mini, int nb_listes, int nb_Expes)
{
	int i,j;
	int *l;
	for(i=1;i<=nb_listes;i++)
	{	for(j=1;j<=nb_Expes;j++)
		{
			
		l=creerTab(taille_mini*i);
		afficher(l,taille_mini*i);
		l = triFusion(l,0,taille_mini*i-1);
		afficher(l,taille_mini*i);
		//trisSelection(l,taille_mini*i);
		//trisInsertion(l,taille_mini*i);
		//trisBulle(l,taille);
		}
	}
}
*/

//creation des fichier CSV, DAT, GNU __________________________________________________________________

void statitiqueCSV(tableStats *tabSt, FILE *fichier){
	int i,j;
	char str[MAXSTRING];
	for (i = 0; i < tabSt->lignes; i++){
		for(j = 0; j<= NOMBRETRIS; j++){
			sprintf(str,"%-9d|", tabSt->table[i][j]);
			printf("%s ",str);
			fputs(str, fichier);
		}
		printf("\n");
		fputs("\n",fichier);
	}
}

void statitiqueDAT(tableStats *tabSt, FILE *fichier){
	int i, j;
	char str[MAXSTRING];
	for(i=0; i<tabSt->lignes; i++)
	{
		for(j = 0; j<= NOMBRETRIS; j++){
			sprintf(str,"%-10d",tabSt->table[i][j]);
			fputs(str, fichier);
		}
		fputs("\n",fichier);
	}
}

void statitiqueGNU(FILE *fichier, int choisirStat){
	fputs("set title 'Comparaison des algorithmes de tris'\n",fichier);
	fputs("set xlabel 'Taille de la liste'\n",fichier);
	if (choisirStat = 0){
		fputs("set ylabel 'Nombre permutations'\n", fichier);
	}
	else if (choisirStat=1){
		fputs("set ylabel 'Nombre comparaisons'\n", fichier);
	}
	else if(choisirStat=2){
		fputs("set ylabel 'Nombre opérations'\n", fichier);
	}
	fputs("plot 'resultat.dat' using 1:2 title 'Tri par Selection' with linespoints\n",fichier);
	fputs("replot 'resultat.dat' using 1:3 title 'Tri par insertion' with linespoints\n", fichier);
	fputs("replot 'resultat.dat' using 1:4 title 'Tri à Bulles' with linespoints\n", fichier);
	fputs("replot 'resultat.dat' using 1:5 title 'Tri Fusion' with linespoints\n", fichier);
	fputs("replot 'resultat.dat' using 1:6 title 'Tri Rapide' with linespoints\n", fichier);
	fputs("replot 'resultat.dat' using 1:7 title 'Tri par Tas' with linespoints\n", fichier);
	fputs("pause -1\n", fichier);
}