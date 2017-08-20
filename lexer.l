%{
#include <stdio.h>
#include "token.h"
%}

whitespace	[ \t]+
num		[0-9]+

%%

{num}		{ return NUM; }
"+"		{ return '+'; }
"-"		{ return '-'; }
"*"		{ return MULT_OP; }
"/"		{ return DIV_OP; }
"("		{ return LPAREN; }
")"		{ return RPAREN; }
{whitespace}	{  }
.		{ printf("Error lexico, '%s' no es un simbolo permitido\n",yytext); exit(1); }
