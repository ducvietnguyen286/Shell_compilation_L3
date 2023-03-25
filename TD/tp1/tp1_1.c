#include <stdio.h>
#include <stdlib.h>

void listeEntier(int taille);

int main(int argc, char const *argv[])
{
	liste(5);
	return 0;
}
void listeEntier(int taille)
{
	int liste[taille];
	for (int i = 0; i < taille; ++i)
	{
		liste[i] =  (rand() %(taille));
		printf("%d ", liste[i] );
	}
}