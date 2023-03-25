#include <stdio.h>
#include <stdlib.h>
#include"fonc.h"

///////////////////////////////////////////////////////
int *listeEntier( int taille)
{	
	int *l =malloc(taille * sizeof(int));
	for(int i =0; i<taille; i++)
	{	
		l[i] = rand()%10;
	}
	return l;
}
////////////////////////////////////////////////////////
void swap(int *l, int a, int b)
{
	int temp = l[a];
	l[a]=l[b];
	l[b]=temp;
}
////////////////////////////////////////////////////////
void afficher(int *l, int taille)
{	printf("\n");
	for (int i = 0; i < taille ; i++)
		printf("%d ",l[i]);
}

/////////////////////////////////////////////////////
void testListe(int *l, int taille)
{
	int i=1, p=0;
	
	while(i<taille)
	{
		if(l[i] < l[i-1])
		{
			p = 1;
		}
		i++;
	}
	if(p==0)
		printf("\n c'est tris\n");
	else 
		printf("\n ce n'est pas tris\n");
}
////////////////////////////////////////////////////
void trisSelection(int *l, int taille)
{
	int i, j, min;

	for(i=0; i<taille-1;i++)
	{
		min = i;
		for(j=i+1; j<taille; j++)
		{
			if (l[j]<l[min])
				min=j;
		}
		swap(l, i,min);
	}

	afficher(l,taille);
}

//////////////////////////////////////////////////////////
void trisInsertion(int *l, int taille)
{
	int i=1;
	while (i<taille)
	{
		int j=i;
		while (j>0 && l[j-1]>l[j])
		{
			swap(l,j,j-1);
			j=j-1;
		}
		i++;
	}
	afficher(l,taille);
}

///////////////////////////////////////////////////////////
void trisBulle(int *l, int taille)
{
	
	for(int i=0; i<taille-1; i++)
	{
		for (int k = 0; k < taille-i-1; k++)
		{
			if(l[k]>l[k+1])
				swap(l,k,k+1);
		}
	}

	afficher(l,taille);
}
/////////////////////////////////////////////////////////////////////////////
void Fusion(int *l, int g, int *l2, int d)
{
	int i,j,k;

	int *new= (int*)malloc((g+d)*sizeof(int));  


	i=0;
	j=0;
	k=0;

	while (i<g && j<d)
	{
		if(l[i]<=l2[j])
		{
			new[k]=l[i];
			i++;
		}
		else
		{
			l[k]=D[j];
			j++;
		}
		k++;
	}

	while(i<n1)
	{
		l[k] = G[i];
		k++;
		i++;
	}
	while(j<n2)
	{
		l[k] = D[j];
		k++;
		j++;
	}
}

void TrisFusion(int *l, int g, int d)
{
	if(g<d)
	{
		int m = +(d-g)/2 ;

		TrisFusion(l,g,m);
		TrisFusion(l,m,d-m);

		Fusion(l,g,l+m,d);
	}
}


////////////////////////////////////////////////////////////////////////////
void plateforme(int taille_mini, int nb_listes, int nb_Expes)
{
	int i,j;
	int *l;
	for(i=1;i<=nb_listes;i++)
	{	for(j=1;j<=nb_Expes;j++)
		{
			
		l=listeEntier(taille_mini*i);
		afficher(l,taille_mini*i);
		TrisFusion(l,0,taille_mini*i-1);
		//trisSelection(l,taille_mini*i);
		//trisInsertion(l,taille_mini*i);
		//trisBulle(l,taille);
		}
	}
}


