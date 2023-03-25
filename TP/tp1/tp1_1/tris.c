#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"tris.h"

int *creerTab(int taille){
	assert(taille > 1);
	int i;
	int *table=(int*)malloc(taille * sizeof(int));
	for(i = 0; i < taille; i++){
		table[i]=rand() % MAXINT;
	}
	return table;
}

int *tabTris(int taille){
	assert(taille>1);
	int i;
	int *table=(int*)malloc(taille*sizeof(int));
	for (i = 0; i < taille; i++)
	{
		table[i]=i;
	}
	return table;
}
int *tabInverse(int taille){
	assert(taille>1);
	int i;
	int *tab =(int*)malloc(taille*sizeof(int));
	for(i=0;i<taille;i++){
		tab[i] = taille - i -1;
	}
	return tab;
}

int *tabDoublons(int taille){
	assert(taille>1);
	int *tab = (int*)malloc(taille*sizeof(int));
	int i,j,val;
	for (i = 0; i<taille ; i++){
		val = rand()%MAXINT;
		for(j=0; j < MAXDOUBLONS && i < taille; i++, j++){
			tab[i]=val;
		}
	}
	return tab;
}
// chon kieu cua bang______________________________________________________________
int *tabChoisir(int taille, int choix){
	int *tab;

	if (choix == NORMAL)
		tab = creerTab(taille);
	else if (choix == TRIE)
		tab =tabTris(taille);
	else if (choix == INVERSE)
		tab = tabInverse(taille);
	else if (choix == DOUBLONS)
		tab = tabDoublons(taille);
	
	return tab;
}
// choisir type de stat_____________________________________________________________
int choisirStat(stat *st, int choix){
	int statistique;
	if (choix == PERMUTATION)
		statistique = st->permutations;
	else if (choix == COMPARAISON)
		statistique = st->comparaisons;
	else if (choix == TOUT)
		statistique = (st->permutations) + (st->comparaisons);
	return statistique;
}
//____________________________________________________________________________________
int testTris(int table[],int taille)
{
	int i;
	assert(taille>1);
	for (int i = 0; i < taille-1; i++)
	{
		 if (table[i]>table[i+1])
		 {
		 	return 0;
		 }
	}
	return 1;
}

// echange_________________________________________________________________
void swap(int table[], int a, int b){
	int n = table[a];
	table[a]=table[b];
	table[b]=n;
}

void permuter(int *x, int *y){
	int aux = *x;
	*x=*y;
	*y=aux;
}
// generation de la stat __________________________________________________

stat *genererStat(tri tr,int taille){
	assert(taille > 1);
	stat *st = (stat*)malloc(sizeof(stat));
	st->nomTri = tr;
	st->taille = taille;
	st->permutations = 0;
	st->comparaisons = 0;
	return st;
}

// generation du tas __________________________________________________

suiteEntiers *genererTas(){
	suiteEntiers *s;
	s = (suiteEntiers*)malloc(sizeof(suiteEntiers));
	s->p = 0;
	return s;
}

//affichages________________________________________________________________
void afficher(int table[], int taille){
	int i=0;
	printf("\n");
	for ( i = 0; i < taille; i++)
	{
		printf("%d ",table[i]);
	}
}

/*void afficherTas(suiteEntiers *s){
	int i;
	for(i=0;i < s->p;i++)
		printf("%d ",s->t[i]);
	printf("\n");
}
*/

// ____tris par selection ________________tim phan tu nho nhat_____________________________________

int chercheIndMin(int tab[],int debut, int taille, stat *st){
	assert((taille > 1)&&(debut>=0));
	int i, mini = debut;
	for(i=1+debut;i<taille;i++){
		(st->comparaisons)++;
		if(tab[i] < tab[mini])
			mini = i;
	}
	
	return mini;
} 


void triSelection(int tab[],int taille, stat *st) {
	assert(taille > 1);
	int i;
	for(i=0; i < taille-1; i++){
		swap(tab, i, chercheIndMin(tab,i,taille, st));
		(st->permutations)++;
	}
}

//tris par insertion_______________________________________________________________
void triInsertion(int tab[], int taille, stat *st){
	assert(taille > 1);
	int pos;
	for(pos=1;pos<taille;pos++){
		while(pos > 0 && tab[pos-1]>tab[pos]){
			swap(tab, pos -1, pos);
			(st->permutations)++;
			pos--;
		}
		if (pos > 0){
			(st->comparaisons)++;
		}
	}
}

//tris bulle _____________________________________________________________
void triBulles(int tab[],int taille, stat *st){
	assert(taille>1);
	int permute = 1, i;
	while(permute){
		permute=0;
		for(i=0; i<taille-1;i++){
			(st->comparaisons)++;
			if(tab[i]>tab[i+1]) {
				swap(tab,i,i+1);
				(st->permutations)++;
				permute=1;
			}
		}
	}
}

//Tris fusion_______________________________________________________________________
int *fusionner(int tab1[], int tab2[], int taille1, int taille2, stat *st)
{
	assert((taille1>=1)&&(taille2>=1));
	int *fus=(int*) malloc((taille1+taille2)*sizeof(int));
	int ind1 =0, ind2 =0;
	while(ind1 < taille1 && ind2 < taille2){
		(st->comparaisons)++;
		(st->permutations)++;

		if (tab1[ind1]<tab2[ind2]){
			fus[ind1+ind2]=tab1[ind1];
			ind1++;
		}

		else{
			fus[ind1+ind2]=tab2[ind2];
			ind2++;
		}
	}

	if(ind2 == taille2){
		while(ind1<taille1){
			(st->permutations)++;
			fus[ind1+ind2]=tab1[ind1];
			ind1++;
		}

	}
	else if(ind1==taille1){
		while(ind2 < taille2){
			(st->permutations)++;
			fus[ind1+ind2]=tab2[ind2];
			ind2++;
		}
	}
	return fus;
}

int *triFusion(int tab[],int debut,int fin,stat *st){
	assert((debut >=0) && (fin >= 0));
	int milieu = (debut + fin)/2;
	int *seul, *inter1, *inter2;
	if(debut == fin){
		seul = (int*)malloc(sizeof(int));
		seul[0] = tab[debut];
		return seul;
	}
	else{
		inter1 = triFusion(tab, debut, milieu,st);
		inter2 = triFusion(tab, milieu+1, fin,st);
		return fusionner(inter1, inter2, milieu -debut +1,fin-milieu, st);
	}
}

//Tris rapide ________________________________________________________________
int partitionner(int tab[],int debut, int fin, stat *st)
{
	assert((debut>=0) && (fin>=0));
	int pivot = tab[debut];
	int gauche = debut +1, droite = fin;
	int fini = 0;
	while(!fini){
		while (gauche <= droite && tab[gauche]<=pivot){
			gauche++;
			(st->comparaisons)++;
		}
		while (droite >= gauche && tab[droite]>=pivot){
			droite--;
			(st->comparaisons)++;
		}
		if(droite<gauche){
			fini = 1;
		}
		else{
			(st->comparaisons)++;
			swap(tab, gauche,droite);
			(st->permutations)++;
		}
	}
	swap(tab,debut,droite);
	(st->permutations)++;
	return droite;
}

void triRapide(int tab[],int debut,int fin,stat *st)
{
	assert((debut >= -1) && (fin >= -1));
	int pivot;
	if (debut < fin){
		pivot = partitionner(tab, debut,fin, st);
		triRapide(tab, debut,pivot -1, st);
		triRapide(tab, pivot + 1, fin,st);
	}
}

//Tri par tas_________________________________________________________________________
void ajouteElemTas(int x, suiteEntiers *s,stat *st){
	int i;

	s->t[s->p] = x;
	(s->p)++;

	i = (s->p) - 1;

	while (i > 0 && s->t[i] > s->t[(i-1) / 2]){
		(st->comparaisons)++;
		permuter(&(s->t[i]), &(s->t[(i-1) / 2]));
		(st->permutations)++;
		i = (i - 1) / 2;
	}
	if(i>0){
		(st->comparaisons)++;
	}
}

int supprimerMax(suiteEntiers *s, stat *st){
	int i = 0, j, max, deplace, fin = 0;

	max = s->t[0];

	s->t[0] = s->t[(s->p) - 1];
	(s->p)--;

	deplace = s->t[0];
	while (fin != 1 && 2*i+1 < s->p){
		j = 2*i + 1;
		if(j+1 < s->p && s->t[j+1] > s->t[j]){
			(st->comparaisons)++;
			j++;
		}
		if(j < s->p)
			(st->comparaisons)++;

		if(deplace > s->t[j]){
			fin = 1;
		}
		if(fin == 0){
			(st->permutations)++;
			s->t[i] = s->t[j];
			i = j;
		}
	}
	s->t[i] = deplace;
	(st->permutations)++;
	return max;
}

int * triTas(int tab[], int taille,stat *st){
	assert(taille > 1);
	int i, j;
	suiteEntiers *s = genererTas();
	int *trie = (int*)malloc(taille * sizeof(int));
	for(i=0; i < taille; i++)
	{
		ajouteElemTas(tab[i],s,st);
	}
	for(j = taille -1; j>= 0; j--){
		trie[j] = supprimerMax(s,st);
	}
	return trie;

}


//creation du table plateForm________________________________________________________________
void plateForm(int taille_mini, int nb_listes, int nb_Expes,tabStats *tabStat, int choisirTab, int choisirSt){
	assert((taille_mini > 1)&&(nb_listes > 0)&&(nb_Expes > 0));
	int i, j, k, taille;

	for (int i = 0; i < nb_listes; i++)
	{
		taille = taille_mini + i * taille_mini;
		tabStat->tab[i][0]=taille;
		for(j=1;j<=NBTRIS;j++){
			tabStat->tab[i][j]=0;
		}

		for (int k = 0; k < nb_Expes; k++)
		{
			stat *stSelection = genererStat(SELECTION,taille);
			stat *stInsertion = genererStat(INSERTION,taille);
			stat *stBulles = genererStat(BULLES,taille);
			stat *stFusion = genererStat(FUSION,taille);
			stat *stRapide = genererStat(RAPIDE,taille);
			stat *stTas = genererStat(TAS,taille);

			int *tabSelection = tabChoisir(taille, choisirTab);
			int *tabInsertion = tabChoisir(taille, choisirTab);
			int *tabBulles = tabChoisir(taille, choisirTab);
			int *tabRapide = tabChoisir(taille, choisirTab);
			int *tabFusion = tabChoisir(taille, choisirTab);
			int *tabTas = tabChoisir(taille, choisirTab);


			//tri des table
			triSelection(tabSelection,taille,stSelection);
			assert(testTris(tabSelection,taille));

			triInsertion(tabInsertion,taille,stInsertion);
			assert(testTris(tabInsertion,taille));

			triBulles(tabBulles,taille,stBulles);
			assert(testTris(tabBulles,taille));

			assert(testTris(triFusion(tabFusion ,0 ,taille-1, stFusion),taille));

			triRapide(tabRapide,0,taille-1,stRapide);
			assert(testTris(tabRapide,taille));

			assert(testTris(triTas(tabTas, taille, stTas), taille));

			// lay so lieu stat_____________________________________________________________
			tabStat->tab[i][SELECTION + 1] += choisirStat(stSelection,choisirSt);
			tabStat->tab[i][INSERTION + 1] += choisirStat(stInsertion,choisirSt);
			tabStat->tab[i][BULLES + 1] += choisirStat(stBulles,choisirSt);
			tabStat->tab[i][FUSION + 1] += choisirStat(stFusion,choisirSt);
			tabStat->tab[i][RAPIDE + 1] += choisirStat(stRapide,choisirSt);
			tabStat->tab[i][TAS + 1] += choisirStat(stTas,choisirSt);

			free(stSelection);
			free(stInsertion);
			free(stBulles);
			free(stFusion);
			free(stRapide);
			free(stTas);
			free(tabSelection);
			free(tabInsertion);
			free(tabBulles);
			free(tabFusion);
			free(tabRapide);
			free(tabTas);

		}

		for(j=1; j <=  NBTRIS;j++)
			tabStat->tab[i][j] /= nb_Expes;
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

void statsCSV(tabStats *tabSt, FILE *fichier){
	int i,j;
	char str[MAXSTR];
	for (i = 0; i < tabSt->lignes; i++){
		for(j = 0; j<= NBTRIS; j++){
			sprintf(str,"%-9d|", tabSt->tab[i][j]);
			//puts(str);
			printf("%s ",str);
			fputs(str, fichier);
		}
		printf("\n");
		fputs("\n",fichier);
	}
}

void statsDAT(tabStats *tabSt, FILE *fichier){
	int i, j;
	char str[MAXSTR];
	for(i=0; i<tabSt->lignes; i++)
	{
		for(j = 0; j<= NBTRIS; j++){
			sprintf(str,"%-10d",tabSt->tab[i][j]);
			//puts(str);
			fputs(str, fichier);
		}
		fputs("\n",fichier);
	}
}



void statsGNU(FILE *fichier, int choisirStat){
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
