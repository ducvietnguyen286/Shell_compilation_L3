#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAXVILLES 100
#define MAXPERSONNES 100
#define MAXCHAINE 150
#define Nouveau(type) (type*)malloc(sizeof(type))

typedef struct cel cel;
/*
---------------------------------------------------------------------------------------------------
Déclarations de structures et de tableaux
*/

char* (personneTab[MAXPERSONNES]);
int nbPersonneTab = 0;

char* (villes[MAXVILLES]);
int nbVilles = 0;


int distance_villes[MAXVILLES][MAXVILLES];



typedef struct {
	char* nom;
	char* ville;
	struct cel* les_abos;
	struct cel* suivi_par;
} Personne;

struct cel{
	Personne *p;
	struct cel* suiv;
};

Personne* table_personnes[MAXPERSONNES];
int nbPersonne = 0;

int dist_pers[MAXPERSONNES][MAXPERSONNES];

int tab_composantes[MAXPERSONNES];
int nbComposantes = 0;

int tab_composantes_fc[MAXPERSONNES];
int nbComposantesFc = 0;

int tab_composantes_Tarjan[MAXPERSONNES];
Personne* deja_vus_Tarjan[MAXPERSONNES];
int nbVusTarjan = 0;
int numCompoTarjan = 0;
int rTarjan = 0;
int rang_Tarjan[MAXPERSONNES];
int rang_att_Tarjan[MAXPERSONNES];

Personne* pile_Tarjan[MAXPERSONNES];
int nbPileTarjan = 0;

// ham mo file __________________________________________________________
FILE *ouvrir_fichier(char *text){
	FILE *fichier=fopen(text,"r");
	if (fichier==NULL){
		printf("ERREUR : Fichier %s incorrect\n",text);
	}
	return fichier;
}

/*
---------------------------------------------------------------------------------------------------
Ajouter une personne dans le tableau
*/

void ajoute_personne(char* nom, char* ville){
	assert (nbPersonne < MAXPERSONNES);
	Personne *p = Nouveau(Personne);
	p->nom = (char*)malloc(MAXCHAINE * sizeof(char));
	p->ville = (char*)malloc(MAXCHAINE * sizeof(char));
	strcpy(p->nom,nom);
	strcpy(p->ville,ville);
	p->les_abos = NULL;
	p->suivi_par= NULL;
	/*for(int i=0;i<nbPersonne;i++){
		if(table_personnes[i]->nom != nom || ) 
	}*/
	table_personnes[nbPersonne++]= p;
}

Personne* get_personne(char *nom){
	Personne *p;
	int i = 0;
	for (i = 0; i < nbPersonne; i++)
	{
		p = table_personnes[i];
		if(strcmp(p->nom,nom)==0)
			return p;	
	}
	
	return NULL;
}

void ajoute_abo(Personne *p1,Personne *p2){
	cel *new, *courant;
	new = Nouveau(cel);
	new->p=p2;
	new->suiv = NULL;
	courant = p1->les_abos;
	if(courant==NULL){
		p1->les_abos=new;
	}
	else{
		while(courant->suiv != NULL){
			courant=courant->suiv;
		}
		courant->suiv =new;
	}
}

void ajoute_suivi_par(Personne *p1, Personne *p2){
	cel *new, *courant;
	new = Nouveau(cel);
	new->p = p2;
	new->suiv=NULL;
	courant = p1->suivi_par;
	if(courant == NULL){
		p1->suivi_par = new;
	}
	else{
		while(courant->suiv != NULL){
			courant = courant->suiv;
		}
		courant->suiv = new;
	}
}


void enleve_abo(Personne* p1, Personne* p2){
	cel *courant, *precedent;
	int trouve;
	courant = p1->les_abos;
	precedent = NULL;
	trouve = (strcmp(courant->p->nom,p2->nom) == 0);
	while(trouve == 0 && courant != NULL){
		precedent = courant;
		courant = courant->suiv;
		if(courant!= NULL){
			trouve = (strcmp(courant->p->nom,p2->nom)==0);
		}
	}
	if(trouve == 1){
		if(precedent != NULL){
			precedent->suiv = courant->suiv;
		}
		else
			p1->les_abos= courant->suiv;
		free(courant);
	}
}

/*
---------------------------------------------------------------------------------------------------
Affichages
*/
void affiche_personne(Personne p){
	cel* courant;
	printf("nom : %s \n ville: %s \n les_abos: ",p.nom, p.ville);
	courant = p.les_abos;
	if(courant == NULL){
		printf("vide");
	}

	while(courant != NULL){
		printf("%s ", courant->p->nom);
		courant = courant->suiv;
	}
	printf("\n suivi par: ");
	courant=p.suivi_par;

	if(courant == NULL){
		printf("vide \n");
	}
	while(courant!=NULL){
		printf("%s ",courant->p->nom);
		courant = courant->suiv;
	}
	printf("\n");
}

void affiche_tout(){
	int i;
	for(i=0;i<nbPersonne;i++){
		printf("\n");
		affiche_personne(*(table_personnes[i]));
	}
}

void affiche_villes(){
	int i;
	for(i=0;i<nbVilles;i++){
		printf("%s\n",villes[i]);
	}
}

/*
---------------------------------------------------------------------------------------------------
Récupérer l'indice d'une personne ou d'une ville
*/
int ind_personne(Personne *p){
	int i;
	for(i=0;(i < nbPersonne) && (p != table_personnes[i]);i++);
	return i;
}

int indVille(char *nomVille){
	int i;
	for (i = 0; (i<nbVilles) && strcmp(villes[i], nomVille) != 0; i++);
	return i;
}

/*
---------------------------------------------------------------------------------------------------
Parser le fichier
*/
void parsePersonnesInfos(char listePersonnes[]){
	char *personne, *personneAjout;
	personne=strtok(listePersonnes," ,[]\n");
	while(personne!=NULL){
		personneAjout = Nouveau(char);
		strcpy(personneAjout,personne);
		personneTab[nbPersonneTab++] = personneAjout;
		personne=strtok(NULL," ,[]\n");
	}

}

void parseVillesInfos(char listeVilles[]){
	char *ville, *villeAjout;
	ville = strtok(listeVilles," ,[]\n");
	while (ville!=NULL){
		villeAjout = (char*)malloc(MAXCHAINE * sizeof(char));
		strcpy(villeAjout,ville);
		villes[nbVilles++] = villeAjout;
		ville=strtok(NULL," ,[]\n");
	}
}
//
void parseAbo(char infosPersonne[]){
	char* pers;
	char* abo;
	char infosAbos[MAXCHAINE];
	Personne *p1, *p2;
	pers =strtok(infosPersonne," :{}[]");
	abo = strtok(NULL, " :{}[]");
	p1= get_personne(pers);
	strcpy(infosAbos, abo);
	abo = strtok(infosAbos, ",");
	while(abo != NULL){
		p2 = get_personne(abo);
		ajoute_abo(p1,p2);
		ajoute_suivi_par(p2,p1);
		abo=strtok(NULL,",");
	}
}


void parsePersonne(char infosPersonne[]){
	char *pers;
	char *abo;
	char *ville;
	//Personne *p1,*p2;

	//char infosAbos[MAXCHAINE];

	pers = strtok(infosPersonne, " :{}[]");
	abo = strtok(NULL, " :{}[]");
	ville = strtok(NULL, " :{}[],");
	ajoute_personne(pers,ville);
	

	// p1=get_personne(pers);
	
	// strcpy(infosAbos,abo);


	// abo = strtok(infosAbos,",");

	// while (abo!=NULL){
	// 	p2=get_personne(abo);
	// 	ajoute_abo(p1,p2);
	// 	abo=strtok(NULL,",");
	// }

}

void parseVille(char infosVille[]){
	char *ville1;
	char *ville2;
	int dist, indVille1, indVille2;
	ville1 = strtok(infosVille," ,()");
	dist = atoi(strtok(NULL," ,()"));
	ville2 = strtok(NULL," ,()");
	indVille1 = indVille(ville1);
	indVille2 = indVille(ville2);
	distance_villes[indVille1][indVille2] = dist;
	distance_villes[indVille2][indVille1] = dist;
}

void parseInfosFile(FILE* file){
	char *ligne =(char*)malloc(MAXCHAINE * sizeof(char));
	char ligneAnalyse[MAXCHAINE];
	fgets(ligne,MAXCHAINE,file);
	fgets(ligne,MAXCHAINE,file);
	fgets(ligne,MAXCHAINE,file);
	strcpy(ligneAnalyse,ligne);
	parseVillesInfos(ligneAnalyse);
	fgets(ligne,MAXCHAINE,file);
	fgets(ligne,MAXCHAINE,file);
	while(strcmp(ligne,"  ],\n") != 0){
		strcpy(ligneAnalyse,ligne);
		parsePersonne(ligneAnalyse);
		fgets(ligne,MAXCHAINE,file);
		//printf("%s\n",ligneAnalyse);
	}
	fgets(ligne,MAXCHAINE,file);
	fgets(ligne,MAXCHAINE,file);
	while(strcmp(ligne,"  ]\n")!=0){
		strcpy(ligneAnalyse,ligne);
		parseVille(ligneAnalyse);
		fgets(ligne,MAXCHAINE,file);
	}
}

void parseAbosFile(FILE* file){
	char *ligne=(char*)malloc(MAXCHAINE * sizeof(char));
	char ligneAnalyse[MAXCHAINE];
	fgets(ligne,MAXCHAINE,file);
	fgets(ligne,MAXCHAINE,file);
	fgets(ligne,MAXCHAINE,file);
	fgets(ligne,MAXCHAINE,file);
	fgets(ligne,MAXCHAINE,file);
	while(strcmp(ligne,"  ],\n") != 0){
		strcpy(ligneAnalyse, ligne);
		parseAbo(ligneAnalyse);
		fgets(ligne,MAXCHAINE,file);
	}
}
/*void parseAbo(char infosPersonne[]){
	char* pers;
	char* abo;
	char infosAbos[MAXCHAINE];
	Personne *p1, *p2;
	pers =strtok(infosPersonne," :{}[]");
	abo = strtok(NULL, " :{}[]");
	p1= get_personne(pers);
	strcpy(infosAbos, abo);
	abo = strtok(infosAbos, ",");
	while(abo != NULL){
		p2 = get_personne(abo);
		ajoute_abo(p1,p2);
		abo=strtok(NULL,",");
	}
}

*/

/*kiem tra xem 1 nguoi co o trong bang table_personnes------------------------*/
int persDansTab(Personne *p, Personne *tabPers[MAXPERSONNES],int indTabPers){
	int trouve = 0, i;
	for(i=0;i<indTabPers && !trouve;i++){
		trouve = (p == tabPers[i]);
	}
	return trouve;
}

/*tinh toan khoang cach cua moi nguoi trong table_personnes----------------------------------*/
int distance_personnes(Personne *p1,Personne *p2){
	int trouve = 0, ind = 0, indTabCourant = 1, indTabFutur = 0, indTraites = 1;
	int i, j, ajout = 0;
	Personne *dejaTraiter[MAXPERSONNES]={p1};
	Personne *courant[MAXPERSONNES] ={p1}, *futur[MAXPERSONNES];
	cel * celCourant;

	if(p1 == p2){
		return 0;
	}
	while(!trouve){
		indTabFutur = 0;
		ajout= 0;
		for(i =0;i<indTabCourant;i++){
			celCourant = courant[i]->les_abos;
			while(celCourant != NULL){
				if(!persDansTab(celCourant->p,dejaTraiter,indTraites)){
					//chung  ta van chua kiem tra nguoi nay_________________
					ajout = 1;
					futur[indTabFutur] = celCourant->p;
					indTabFutur++;
					dejaTraiter[indTraites] = celCourant->p;
					indTraites++;
				}
				celCourant = celCourant->suiv;
			}
		}
		//nguoi 2 chua duoc tim thay_________________________________
		if(ajout == 0){
			return -1;
		}
		//bang futur tro thanh bang courant_________________________
		for(indTabCourant = 0; indTabCourant < indTabFutur;indTabCourant++){
			courant[indTabCourant] = futur[indTabCourant];
		}
		ind++;

		//chung ta tim kiem nguoi p2 trong bang courant
		for(i=0; i < indTabCourant;i++){
			if(courant[i] == p2){
				trouve = 1;
			}
		}
	}
	return ind;
}

float distance_moyenne(){
	int i, j;
	int somme = 0, nbRelations = 0;
	int dist;
	for(i=0;i<nbPersonne;i++){
		for(j=0;j<nbPersonne;j++){
			dist =distance_personnes(table_personnes[i], table_personnes[j]);
			if(dist > 0){
				somme += dist;
				nbRelations++;
				dist_pers[i][j] = dist;
			}
		}
	}
	return ((float)somme / nbRelations);
}
/*tinh toan cac thanh phan lien ket-----------------------------*/
void calcule_une_composante_connexe(int num_compo){
	int indTabCourant = 0, indTabFutur = 0,indTraites =0;
	int i, fin = 0, indPers;
	Personne *dejaTraiter[MAXPERSONNES];
	Personne *courant[MAXPERSONNES], *futur[MAXPERSONNES];
	cel *celCourant;

	//tim kiem su khoi dau cua thanh phan lien ket--------------
	for(i=0;(i<nbPersonne)&&(indTabCourant==0); i++){
		if(tab_composantes[i]==-1){
			courant[indTabCourant]= table_personnes[i];
			indTabCourant++;
			dejaTraiter[indTraites]= table_personnes[i];
			indTraites++;
		}
	}
	i--;
	tab_composantes[i] = num_compo;

	while(!fin){
		indTabFutur = 0;
		for(i=0;i<indTabCourant;i++){
			celCourant = courant[i]->les_abos;
			while(celCourant != NULL){
				if(!persDansTab(celCourant->p, dejaTraiter,indTraites)){
					futur[indTabFutur]= celCourant->p;
					indTabFutur++;
					dejaTraiter[indTraites]=celCourant->p;
					indTraites++;
				}
				celCourant = celCourant->suiv;
			}
			celCourant = courant[i]->suivi_par;
			while(celCourant != NULL){
				if(!persDansTab(celCourant->p,dejaTraiter,indTraites)){

					futur[indTabFutur] = celCourant->p;
					indTabFutur++;
					dejaTraiter[indTraites] = celCourant->p;
					indTraites++;
				}
				celCourant = celCourant->suiv;
			}
		}
		fin = (indTabFutur == 0);
		/*bang table futur tro thanh bang table courant----------------------*/
		for(indTabCourant = 0;indTabCourant<indTabFutur;indTabCourant++){
			courant[indTabCourant] = futur[indTabCourant];
		}
		for(i=0;i<indTabCourant;i++){
			indPers = ind_personne(courant[i]);
		}
	}
}

void calcule_les_composantes_connexes(){
	int i;
	for(i=0; i<nbPersonne; i++){
		tab_composantes[i] = -1;
	}
	for(i=0;i < nbPersonne; i++){
		if(tab_composantes[i] == -1){
			nbComposantes++;
			calcule_une_composante_connexe(nbComposantes);
		}
	}
}

/*
hien thi nhung thanh phan ket noi--------------------------------
*/

void affiche_une_composante(int num_compo){
	int i;
	for(i=0; i < nbPersonne; i++){
		if(tab_composantes[i] == num_compo){
			affiche_personne(*(table_personnes[i]));
			printf("\n");
		}
	}
}

void affiche_les_composantes(){
	int i;
	for (i = 1; i<= nbComposantes;i++){
		printf("Composante %d: \n\n", i );
		affiche_une_composante(i);
	}
}

// calcul des composantes fortement connexes__________________________
void calcule_une_composante_fortement_connexe(int num_compo){
	int indTabCourant = 0, indTabFutur = 0, indTraites = 0;
	int i, fin=0,indPers;
	Personne *dejaTraiter[MAXPERSONNES];
	Personne *courant[MAXPERSONNES], *futur[MAXPERSONNES];
	cel *celCourant;

	//Recherche le debut de la composante fortement connexe
	for(i=0;(i < nbPersonne) && (indTabCourant == 0); i++){
		if(tab_composantes_fc[i] == -1){
			courant[indTabCourant] = table_personnes[i];
			indTabCourant++;
			dejaTraiter[indTraites] = table_personnes[i];
			indTraites++;
		}
	}
	i--;
	tab_composantes_fc[i] = num_compo;

	//calcule de la composante fortement connexe-----------------------------------------------
	while(!fin){
		indTabFutur =0;
		for(i=0; i<indTabCourant;i++){
			celCourant = courant[i]->les_abos;
			while(celCourant != NULL){
				if(!persDansTab(celCourant->p,dejaTraiter,indTraites)){
					futur[indTabFutur] = celCourant->p;
					indTabFutur++;
					dejaTraiter[indTraites] = celCourant->p;
					indTraites++;
				}
				else{
					indPers = ind_personne(celCourant->p);
					if(tab_composantes_fc[indPers] == -1){
						tab_composantes_fc[indPers] = num_compo;
					}
					indPers=ind_personne(courant[i]);
					if(tab_composantes_fc[indPers] == -1){
						tab_composantes_fc[indPers] = num_compo;
					}
				}
				celCourant = celCourant->suiv;
			}
		}
		fin = (indTabFutur == 0);
		// le tableau futur devient le tableau courant-------------------------------------------------
		for(indTabCourant = 0; indTabCourant < indTabFutur; indTabCourant++){
			courant[indTabCourant] = futur[indTabCourant];
		}
	}
}

void calcule_les_composantes_fortement_connexes(){
	int i;
	for(i=0;i < nbPersonne; i++){
		tab_composantes_fc[i] = -1;
	}
	for(i=0;i< nbPersonne;i++){
		if(tab_composantes_fc[i] == -1){
			nbComposantesFc++;
			calcule_une_composante_fortement_connexe(nbComposantesFc);
		}
	}
}
// affiche des composantes fortement connexes

void affiche_une_cfc(int num_compo){
	int i;
	for(i=0;i<nbPersonne;i++){
		if(tab_composantes_fc[i] == num_compo){
			affiche_personne(*(table_personnes[i]));
			printf("\n");
		}
	}
}

void affiche_les_composantes_fortement_connexes(){
	int i;
	for(i=1;i<=nbComposantesFc;i++){
		printf("Composante fortement connexe %d : \n\n", i );
		affiche_une_cfc(i);
	}
}


/*
---------------------------------------------------------------------------------------------------
Algorithme de Tarjan
*/
void parcours_descendants(Personne *p, int ind) {
	int indPers;
	Personne *pers;
	cel *celCourant;
	pile_Tarjan[nbPileTarjan] = p;
	nbPileTarjan++;
	deja_vus_Tarjan[nbVusTarjan] = p;
	nbVusTarjan++;
	rTarjan++;
	rang_Tarjan[ind] = rTarjan;
	rang_att_Tarjan[ind] = rTarjan;
	celCourant = p->les_abos;
	while (celCourant != NULL) {
		indPers = ind_personne(celCourant->p);
		if (!persDansTab(celCourant->p, deja_vus_Tarjan, nbVusTarjan)) {
			parcours_descendants(celCourant->p, indPers);
			if (rang_att_Tarjan[ind] > rang_att_Tarjan[indPers]) {
				rang_att_Tarjan[ind] = rang_att_Tarjan[indPers];
			}
		}
		else if (persDansTab(celCourant->p, pile_Tarjan, nbPileTarjan)) {
			if (rang_att_Tarjan[ind] > rang_Tarjan[indPers]) {
				rang_att_Tarjan[ind] = rang_Tarjan[indPers];
			}
		}
		celCourant = celCourant->suiv;
	}
	if (rang_att_Tarjan[ind] == rang_Tarjan[ind]) {
		numCompoTarjan++;
		do {
			nbPileTarjan--;
			pers = pile_Tarjan[nbPileTarjan];
			indPers = ind_personne(pers);
			tab_composantes_Tarjan[indPers] = numCompoTarjan;
		} while (ind != indPers);
	}
}

void calcule_les_cfc_Tarjan() {
	int ind = 0;
	Personne *p = table_personnes[ind];
	while (nbVusTarjan < nbPersonne) {
		while (ind < nbPersonne && persDansTab(p, deja_vus_Tarjan, nbVusTarjan)) {
			ind++;
			p = table_personnes[ind];
		}
		parcours_descendants(p, ind);
	}
}


void affiche_une_cfc_Tarjan(int num_compo){
	int i;
	for (i = 0; i < nbPersonne; i++){
		if (tab_composantes_Tarjan[i] == num_compo) {
			affiche_personne(*(table_personnes[i]));
			printf("\n");
		}
	}
}

void affiche_les_cfc_Tarjan(){
	int i;
	for (i = 1; i <= numCompoTarjan; i++){
		printf("Composante fortement connexe Tarjan %d : \n\n", i);
		affiche_une_cfc_Tarjan(i); 
	}
}

int main(void){
	//int i,n;
	//char c[MAXCHAINE];
	//char*l;
	//Personne *p1, *p2, *p3;

	FILE *file =ouvrir_fichier("reseau1.txt");
	parseInfosFile(file);
	fclose(file);

	file =ouvrir_fichier("reseau1.txt");
	parseAbosFile(file);
	fclose(file);
	printf("-----------------------------------------------\n");
	affiche_tout();
	/* p1=table_personnes[1];
	 p2=table_personnes[6];

	 printf("ville p1: %s nom p1: %s\n",p1->ville,p1->nom);

	 printf("ville p2: %s nom p2: %s\n",p2->ville,p2->nom);
	
	 printf("%f\n", distance_moyenne());
	 n = distance_personnes(p1,p2);
	
	 printf("so khoang cach: %d\n", n);*/
	printf("-----------------------------------------------\n");
	 calcule_les_composantes_connexes();
	 affiche_les_composantes();

	printf("-----------------------------------------------\n");
	 calcule_les_composantes_fortement_connexes();
	 affiche_les_composantes_fortement_connexes();
	printf("-----------------------------------------------\n");
	
	 calcule_les_cfc_Tarjan();
	 affiche_les_cfc_Tarjan();
	// for(i=0,i<strlen(personneTab))
	// printf("%s\n", );

	// char n[]="[kevin,karim,alice,paul,charlotte,gabriel,dalila]," ;
	
	// char v[]="[lille,lens,arras,douai,carvin,seclin],";

	// char a[]="kevin:{[gabriel,:dalila,alonso],lille},";

	
	
	// ajoute_personne("viet","Hanoi");
	// ajoute_personne("Duc Anh","Arras");
	// ajoute_personne("Vincent","Nante");

	// p1=get_personne("viet");
	// p2=get_personne("Duc Anh");
	// p3=get_personne("Vincent");

	// ajoute_abo(p1,p2);
	// ajoute_abo(p1,p3);

	// affiche_personne(p1);
	// affiche_tout();
	// printf("----------------------------\n");
	// enleve_abo(p1,p3);
	// affiche_personne(p1);

return 0;

}