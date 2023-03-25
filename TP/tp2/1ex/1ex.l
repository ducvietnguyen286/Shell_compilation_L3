

%%
^" "*	
" "+	printf(" ");
%%

int main(){
	yylex();
}
int yywrap(){
	return 1;
}

