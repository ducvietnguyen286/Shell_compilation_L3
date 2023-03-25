#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define MaxCh 25
#define k 37

typedef char mot[MaxCh];

typedef struct cel {
  mot m;
  int *nbOccu;
  struct cel *suivant;
} cellule;

typedef cellule * Liste;
typedef Liste Table[k];

int valeur(mot m) {
  int somme = 0, i;
  for(i = 0; i < strlen(m); i++) {
    somme+=m[i];
  }
  return somme;
}

int h(mot m) {
  return valeur(m)%k;
}

void initTable(Table t) {
  int i;
  for (i = 0; i < k; i++){
    t[i] = NULL;
  }
}

int rechercherMot(mot m, Table t) {
  int i = h(m), cpt = 0;
  cellule *c = t[i];
  while ( c != NULL) {
    if (strcmp(m, c->m) == 0) {
      return cpt;
    }
    cpt++;
    c = c->suivant;
  }
  return -1;
}
// void ajouteTblOccu(cellule *c, int nbDoc) {
//   printf("Ajouttbloccu nbdoc : %d\n",nbDoc);
//   int * tblOccu = (int *) malloc(nbDoc*sizeof(int));
//   printf("ok ajouteTbloccu\n");
//   c->nbOccu = tblOccu;
// }
void insererMot(mot m, Table t, int posF, int nbDoc) {
  int i = h(m), pos = rechercherMot(m,t);
  //printf("POS : %d\n",pos);
  cellule *c = t[i];
  if (pos == -1) {//Si le mot n'existe pas
    cellule *new_c = (cellule*) malloc(sizeof(cellule));
    strcpy(new_c->m,m);
    new_c->nbOccu = (int *) calloc(nbDoc*3,sizeof(int));
    new_c->nbOccu[posF*3] = 1;
    //printf("NEW_C : Mot : '%s' | nbOccu : %d\n",new_c->m,new_c->nbOccu);
    if (c == NULL || (strcmp(m,c->m) < 0)) { //Si il n'y a aucun mot a cette valeur ou m > c->m
      new_c->suivant = c;
      t[i] = new_c;
    }
    else {
      while (c->suivant != NULL && (strcmp(m,c->suivant->m) > 0) ) {//Tantq que le mot suivant est sup
        c = c->suivant;
      }
      new_c->suivant = c->suivant;
      c->suivant = new_c;
    }
  }
  else {
    while (pos != 0) {
      c=c->suivant;
      pos--;
    }
    //printf("C : Mot : '%s' | nbOccu : %d\n",c->m,c->nbOccu);
    c->nbOccu[posF*3]++;
  }
}

// int main(void) {
//   Table t;
//   initTable(t);
//   insererMot("toto",t);
//   printf("nbOccu : %d\n",t[h("toto")]->nbOccu);
//   insererMot("toto",t);
//   printf("nbOccu : %d\n",t[h("toto")]->nbOccu);
//   insererMot("otto",t);
//   printf("nbOccu : %d\n",t[h("toto")]->nbOccu);
//   insererMot("oott",t);
//   insererMot("oott",t);
//   insererMot("oott",t);
//   insererMot("oott",t);
//
//   printf("nbOccu : %d\n",t[h("toto")]->nbOccu);
//
//
//   return 1;
//
