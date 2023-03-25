# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "hach.h"

int minuscule(char c) {
	return ((c >= 'a') && (c <= 'z'));
}


int majuscule(char c) {
	return ((c >= 'A') && (c <= 'Z')); 
}


int estLettre(char c) {
	return (minuscule(c) || majuscule(c));
}

char lettreVersMajuscule (char c) {
	return ((minuscule(c)) ? (c-'a'+'A') : (c));
}

//chuyen chu thuong thanh chu hoa vi du: Truong Thanh = TRUONG THANH
char *motVersMajuscule(char *mot){
	char *motMaj = (char*)malloc(MAXCH*sizeof(char));
	int i;
	for (int i = 0; i < strlen(mot); i++)
	{
		motMaj[i]=lettreVersMajuscule(mot[i]);
	}
	motMaj[i]='\0';
	return motMaj;
}
//MO VA KIEM XEM CO FILE HAY KHONG - TRUYEN DIA CHI VAO
//___________________________________________________________________________________________
FILE *ouvrirFichier(char * chaine){
	FILE *fichier = NULL;
	fichier=fopen(chaine,"r");
	if(fichier!= NULL){
		return fichier;
	}
	else {
		printf("error pour creer fichier");
		return 0;
	}
}
//DOC TAP TIN
//_____________________________________________________________________________________________
char* prochainMot(FILE* file) {
	char *mot = malloc(MAXCH * sizeof(char));
	char z = ' ';
	int ind = 0;
	//idea: xoa di khoang trong o khu vuc dau cua file
	while ((z != EOF) && !estLettre(z)) {
		z = fgetc(file);
	}
	//doc cac ky tu vi du:

	while ((z != EOF) && estLettre(z)) {
		mot[ind] = z;
		ind++;
		z = fgetc(file);
	}
	mot[ind] = '\0';
	return mot;
}
// fonction hash_________________________________________________________________________________
int hash(char* mot){
	int somme = 0, i;
	for (int i = 0; i < strlen(mot); i++)
	{
		somme += mot[i];
	}
	return somme%26;

}
//generer des structure ___________________________________________________

Table* genererTable() {
	Table *t = Nouveau(Table);
	int i;
	for (i = 0; i < MAXCLE; i++) {
		*(t[i]) = NULL;
	}
	return t;
}

//Ajout des mots d'un fichier dans une liste chainée________________________________

void ajouterMotListeChainee(ListChainee *l, char *m, int indDoc){
	ListChainee new;
	ListChainee courant, precedent = NULL;
	if(*l != NULL){
		courant = *l;
		while(courant != NULL && strcmp(m,courant->mot)>0){
			precedent =courant;
			courant=courant->suivant;
		}

		if(courant == NULL || strcmp(m,courant->mot)<0){
			new = Nouveau(cellule);
			strcpy(new->mot,m);
			new->freq[indDoc]=1;
			new->suivant=courant;
			if(precedent != NULL){
				precedent->suivant = new;
			}
			else{
				*l = new;
			}
		}

		else if(strcmp(m,courant->mot)==0){
			(courant->freq[indDoc])++;
		}

	}
	else{
		new = Nouveau(cellule);
		strcpy(new->mot,m);
		new->freq[indDoc]=1;
		new->suivant=NULL;
		*l=new;
	}
}

void ajouterMotsTable(FILE *file, Table t,ListeDocs *liste){
	char *mot=prochainMot(file);
	char *motMaj;
	char *motFin = "\0";
	int e;
	while (strcmp(mot,motFin)){
		//(liste->documents[(liste->nbDocs)-1]->nbMots)++;
		motMaj = motVersMajuscule(mot);
		e=hash(motMaj);
		ajouterMotListeChainee(&t[e], motMaj/*,(liste->nbDocs)-1*/);
		mot = prochainMot(file);
	}
	free(mot);
	free(motMaj);
}

































//========================================================================
