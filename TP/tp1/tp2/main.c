# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "hach.h"
int main(int argc, char const *argv[])
{
	char chain[MAXCHAR] ="";
	

	FILE *fichier = NULL;
	fichier=ouvrirFichier("texte1.txt");

	char *data = prochainMot(fichier);
	printf("%s\n",data);

	data = prochainMot(fichier);
	printf("%s\n",data);


	int hach = hash(data);
	printf("*data %c\n",*data);
	printf("*(data+1) %c\n",*(data+1));
	printf("*(data)+1 %c\n",*(data)+1);
	
	//printf("%s\n",*data);
	printf("%d\n",hach );
	
	
	return 0;



}