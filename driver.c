/* driver.c - Programa para guiar un parser predictivo de descenso recursivo */
/* Escrito por Egdares Futch H. - 2017 */

#include <stdio.h>
#include <stdlib.h>
#include "token.h"

extern FILE *yyin;
extern int yylex();

int lookahead;

void error(char *message)
{
	printf("Error: %s\n",message);
	exit(1);
}

int main(int argc, char**argv)
{
	FILE *fp; 

	if (argc < 2)
		yyin = stdin;
	else
	{
		fp = fopen(argv[1],"r");
		if (!fp)
			error("File not found");
		else
			yyin = fp;
	}
	lookahead = yylex();
	expr();
}

int consume(int token_leido,int token_esperado)
{
	if (token_leido == token_esperado)
	{
		lookahead = yylex();
		printf("Nuevo lookahead = %d\n",lookahead);
	}
	else error("Error de sintaxis, token leido no es lo esperado");
}

void expr()
{
	puts("TERM");
	term();
	puts("EXPR_PRIMA");
	expr_prima();
}

void expr_prima()
{
	if (lookahead == '+')
	{
		puts("+");
		consume(lookahead,'+');
		puts("TERM");
		term();
		puts("EXPR_PRIMA");
		expr_prima();
	}
	else if (lookahead == '-')
	{
		consume(lookahead,'-');
		term();
		expr_prima();
	}
}

void term()
{
	puts("FACTOR");
	factor();
	puts("TERM_PRIMA");
	term_prima();
}

void term_prima()
{
	if (lookahead == MULT_OP)
	{
		puts("*");
		consume(lookahead,MULT_OP);
		puts("FACTOR");
		factor();
		puts("TERM_PRIMA");
		term_prima();
	}
	else if (lookahead == DIV_OP)
	{
		consume(lookahead,DIV_OP);
		factor();
		term_prima();
	}
}

void factor()
{
	if (lookahead == NUM)
	{
		puts("NUM");
		consume(lookahead,NUM);
	}
	else if (lookahead == LPAREN)
	{
		consume(lookahead,LPAREN);
		expr();
		consume(lookahead,RPAREN);
	}
	else error("Error sintactico");
}
