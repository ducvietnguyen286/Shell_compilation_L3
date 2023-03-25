#include<stdio.h>
#include"tp4.h"

char *name = {NULL,"db_type", "db_name", "db_table_prefix", "db_port"};

int main(void){

int ntoken, vtoken;
ntoken = yylex();

while(ntoken){
	vtoken=yylex();
	switch(ntoken){
	case TYPE:
	case NAME:
	case TABLE_PREFIX:
		if(ntoken!=IDENT)
			{
				printf("Syntaxe error en ligne %d, exepted a: mais %s\n ",yylineno,yytex);
				return 1;
			}
		printf("%s is set to %s\n"name[ntoken],yytext);
		break; 
	case POST:
		if(vtoken!=INTEGER){
			printf("syntaxe error in line %d, Excepted a identifier but found %s\n", yylineno,yytext);
			return 1;
		}
		printf("%s is set to %s\n",name[ntoken],yytext);
		break;
	default:
		printf("Syntaxe error in line %d\n",yylineno); 
	}	
	ntoken = yylex();	
}

return 0;

}
