#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "listechainee.c"

#define MAX 25
#define MAX_FICHIER 10

typedef struct {
  char *nom;
  int nbMots;
} infoFichier;
typedef infoFichier * ListeInfoF;

int estMinuscule(char c)
{
  return (c >= 'a' && c <= 'z');
}

int estMajuscule(char c)
{
  return (c >= 'A' && c <= 'Z');
}

int estLettre(char c)
{
  return (estMajuscule(c) || estMinuscule(c));
}

void enMajuscule(char * c)
{
  if (estMinuscule(*c)) {
    *c = *c - 'a' + 'A';
  }
}

FILE* ouvrirFichier(char *text)
{
  FILE* f = NULL;
  f=fopen(text,"r");
  if(f != NULL) printf("Fichier Ouvert\n");
  else printf("ERREUR : Fichier %s incorrect\n",text);
  return f;
}

char * lireMot(FILE * f)
{
  char *chaine = (char*)malloc(sizeof(char)*26);
  //cpt = 0;
  chaine[0] = '\0';
  char c = fgetc(f);
  while(isspace(c) || ispunct(c)) c = fgetc(f);
  while(c != EOF && !isspace(c) && estLettre(c))
  {
      strncat(chaine,&c,1);
      c = fgetc(f);
      //cpt++;
  }
  return chaine;
}

void afficheMotFichier(FILE *f) {
  char *ch = lireMot(f);
  while (strcmp(ch,"") != 0) {
    printf("Mot : '%s'\n",ch);
    ch = lireMot(f);
  }
}

void rempliTable(Table t, FILE *f, int posF, int nbDoc, ListeInfoF l){
  char *ch = lireMot(f);

  while (strcmp(ch,"") != 0) {
    l[posF].nbMots++;
    insererMot(ch,t,posF,nbDoc);
    ch = lireMot(f);
  }
}

void afficheTable(Table t, int nbDoc) {
  int i = 0,esp = 0, j;
  cellule *r;
  while (i < k) {
    r = t[i];
    if (r != NULL) {
      printf("IND %d : ",i);
      esp = 1;
    }
    while (r != NULL) {
      for (j = 0; j < nbDoc; j++) {
        if (r->nbOccu[j*3] != 0) printf("'%s' & nbOccu = %d (text %d) | ",r->m,r->nbOccu[j*3],j);
      }
      r = r->suivant;
    }
    if (esp) {
      printf("\n");
      esp = 0;
    }
    i++;
  }
}
float tf(char * mot, int posF, Table t, ListeInfoF l) {
  int i,j;
  cellule *c;
  i = h(mot);
  j = rechercherMot(mot,t);
  printf("I : %d\n",i);
  c = t[i];
  for (i = 0; i < j; i++) {
    c = c->suivant;
  }
  if (c->nbOccu[posF*3] > 0) {

    printf("NbOccu %s : %d\n",mot,c->nbOccu[posF*3]);
    printf("Nbmot de %s : %d\n",l[posF].nom,l[posF].nbMots);
    return ((float)c->nbOccu[posF*3]/(float)(l[posF].nbMots));
  }
  return 0;
}

float idf(char *mot, int nbDoc, Table t) {
  int i,j;
  cellule *c;
  i = h(mot);
  j= rechercherMot(mot,t);
  c = t[i];
  for (i = 0; i <j; i++) {
    c= c->suivant;
  }
  j = 0;
  for (i = 0; i < nbDoc; i++) {
    if (c->nbOccu[i*3] > 0) j++;
  }
  return (float)nbDoc/(float)j;
}

ListeInfoF creerListeInfoF(char * argv[],int sz) {
  ListeInfoF l = (ListeInfoF) calloc(sz,sizeof(infoFichier));
  int i = 0;
  while (i < sz) {
    infoFichier info;
    info.nom = argv[i+1];
    info.nbMots = 0;
    l[i] = info;
    i++;
  }
  return l;
}
void afficheListeInfoF(ListeInfoF l, int sz) {
  infoFichier info;
  int i;
  for (i = 0; i < sz; i++) {
    info = l[i];
    printf("Nom : %s | Nbmot : %d\n",info.nom,info.nbMots);
  }
}



int main (int argc, char * argv[]){
  ListeInfoF l= creerListeInfoF(argv,argc-1);
  afficheListeInfoF(l,argc-1);
  FILE* f;
  // if (f == NULL) return 1;
  // afficheMotFichier(f);
  // fclose(f);
  //
  // f = ouvrirFichier(argv[1]);
  // if (f == NULL) return 1;
  Table t;
  initTable(t);
  // rempliTable(t,f);
  // afficheTable(t);
  int i = 1;
  while (i < argc) {
    f = ouvrirFichier(argv[i]);
    if (f != NULL) {
      rempliTable(t,f,i-1,argc-1,l);
      printf("remplie\n");
      fclose(f);
    }
    i++;
  }
  afficheTable(t,argc-1);
  afficheListeInfoF(l,argc-1);

  float fi;
  fi = tf("otto",1,t,l);
  printf("F : %f\n",fi);
  fi = tf("toot",0,t,l);
  printf("F : %f\n",fi);

  printf("IDF : \n");
  fi = idf("otto",argc-1,t);
  printf("otto : %f\n",fi);
  fi = idf("Pouloulou",argc-1,t);
  printf("Pouloulou : %f\n",fi);

  //char * ch = lireMot(f);
  //printf("Mot : %s\n",ch);
  return 0;
}
