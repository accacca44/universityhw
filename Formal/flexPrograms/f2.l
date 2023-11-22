%{
#include <iostream>
using namespace std;	
%}

%option noyywrap

%%

[1-9][0-9]* {printf("%s\n", yytext);}
.|\n {;}
%%

int main() {
	yylex();
}
