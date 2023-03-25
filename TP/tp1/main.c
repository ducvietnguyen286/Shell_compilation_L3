#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "fonc.h"


int main(int argc, char const *argv[])

{
	int  taille_mini, nb_listes,nb_Expes;
	//int *l; 


/*	printf("\n saissiez la taille de la tableau: ");
	scanf("%d", &taille);
	printf("\n saissiez la max de chaque element: ");
	scanf("%d", &max);

	srand(time(NULL));

	l = listeEntier(taille,max);

	afficher(l, taille);
	
	testListe(l, taille);
	
	trisSelection(l,taille);

	trisInsertion(l,taille);

	trisBulle(l, taille);

	testListe(l, taille);
*/

	printf("\n Entrez le taille mini: ");
	scanf("%d",&taille_mini);
	printf("\n Entrez nombre liste: ");
	scanf("%d",&nb_listes);
	printf("\n Entrez exps:");
	scanf("%d",&nb_Expes);

	plateforme(taille_mini, nb_listes, nb_Expes);

	return 0;
}


