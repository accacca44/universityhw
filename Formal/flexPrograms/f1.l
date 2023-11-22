%{
#include <iostream>
using namespace std;	

int count = 0;
%}

%option noyywrap

%%

a {count++;}
.|\n {;}

%%

int main() {
	yylex();
	printf("%d\n", count);
}
