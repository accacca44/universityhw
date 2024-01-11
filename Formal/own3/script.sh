flex lexer.l
bison -dtv  akos.y 
g++ lex.yy.c akos.tab.c
./a.out < examples/lnko.akos
