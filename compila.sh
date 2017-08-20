rm a.out lex.yy.c
flex lexer.l
gcc driver.c lex.yy.c -ll
