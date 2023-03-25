%{
 #include"tp4.h"
%}

%%
"db_type"	return TYPE;
"db_name"	return NAME;
"db_table_prefix"	return TABLE_PREFIX;
"db_port"	return PORT;

[a-zA-Z][a-zA-Z_]*	return IDENT;
[0-9]*		return ENTIER;
[ \t]		;
\n		++yylineno;
.		printf("caractere inattendu\n");

%%

int yywrap(void)
{
	return 1;
}
