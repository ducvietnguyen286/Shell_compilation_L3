#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"tris.h"

int main(void){
	int taille_mini, nb_listes, nb_expes, choisirTab, choisirStat;
	tabStats *tabSt = (tabStats*)malloc(sizeof(tabStats));
	srand(time(NULL));

	//demander parametre

	printf("\n Entrez le taille mini: " );
	scanf("%d",&taille_mini);
	printf("\n Entrez le nombre liste: " );
	scanf("%d",&nb_listes);
	printf("\n Entrez le nombre expes: " );
	scanf("%d",&nb_expes);

	do{
		printf("Choisissez du type de tableau (0: Normal, 1:Trié, 2:Inversé, 3:Doublons)\n");
		scanf("%d",&choisirTab);
	}while((choisirTab<0)||(choisirTab>3));

	do{
		printf("choisissez de la statistiques (0: permutations, 1:comparaisons, 2:tout) \n");
		scanf("%d",&choisirStat);
	}while((choisirStat<0)||(choisirStat>2));

	puts("Talle    |Selection |Insertion | Bulles   | Fusion   | Rapide   | Tas      |");
	puts("----------------------------------------------------------------------------");

// creation des fichiers__________________________________________________________________________________

	FILE * fichierCSV = NULL;
	fichierCSV = fopen("resultat.csv","w");

	if(fichierCSV != NULL){
		fputs("Talle    |Selection|Insertion| Bulles  | Fusion  | Rapide  | Tas     |\n",fichierCSV);
		fputs("----------------------------------------------------------------------\n",fichierCSV);
		plateForm( taille_mini, nb_listes, nb_expes, tabSt, choisirTab, choisirStat);
		statsCSV(tabSt,fichierCSV);
		fclose(fichierCSV);
	}

	FILE *fichierDAT = NULL;
	fichierDAT = fopen("resultat.dat","w");

	if(fichierDAT != NULL){
		fputs("  Talle  |Selection|Insertion| Bulles  | Fusion  | Rapide  | Tas     |\n",fichierDAT);
		fputs("----------------------------------------------------------------------\n",fichierCSV);
		statsDAT(tabSt,fichierDAT);
		fclose(fichierDAT);
	}

	FILE *fichierGNU = NULL;
	fichierGNU=fopen("resultat.gnu","w");

	if(fichierGNU != NULL){
		statsGNU(fichierGNU,choisirStat);
	}
	return 0;
}
