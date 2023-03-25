%{
	int nb, mot;
%}

nsfs	[0-9]+

%%
[a-zA-Z]+	{mot++;}
{nsfs}(","{nsfs})?	{nb++;}	

%%

int main(void){
	yylex();
	printf("mots: %d ; nombre: %d", mot,nb);
	return 0;
}

int yywrap(){
	return 1;
}
