#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXCH 255
#define K 37
#define Noveau(type) (type*)malloc(sizeof(type));

typedef char mot[MAXCH];

typedef struct cel{
	mot m;
	struct cel* suiv;
} cellule;

typedef cellule* Liste;

typedef Liste table[K];

int valeur(mot m){
	int som = 0,i;
	for(i=0; i<strlen(m);i++){
		som += m[i];
	}
	return som;
}

int h(mot m){
	return valeur(m)%K;
}

void initTable(table t){
	int i;
	for(i=0;i<K;i++)
		t[i]=NULL;
}

void insererMotListe(mot m,table t){
	int e=h(m);
	Liste p = Noveau(cellule);
	strcpy(p->m,m);
	p->suiv=t[e];
	t[e]=p;
}

int rechercheMot(mot m, table t){
	int trouve = 0;
	int e=h(m);
	Liste p = t[e];
	while((!trouve)&&(p)){
		trouve = strcmp(m,p->m) == 0 ;
		p=p->suiv;
	}
	return trouve;

}

int rechercherMotRec(mot m, table t){
int e = h(m);
Liste p=t[e];
if(!p)
	return 0;
else if(strcmp(m,p->m)==0)
	return 1;
else
	return rechercherMotRec(m,p->suiv);
}

void affichage(table t){
	int i;
	Liste l;
	for(i=0;i<K;i++){
		printf("cle %d: \n",i);
		l=t[i];
		while(l){
			printf("%s \n",l->m);
			l=l->suiv;

		}
	printf("----------------------------\n");
	}
}
int main(int argc, char const *argv[])
{
	table *t = (table*)malloc(sizeof(table));
	int n;
	insererMotListe("toto",*t);
	insererMotListe("otot",*t);
	insererMotListe("viet",*t);
	n= rechercherMotRec("toto",*t);
	printf("%d\n",n );
	affichage(*t);
	return 0;
}