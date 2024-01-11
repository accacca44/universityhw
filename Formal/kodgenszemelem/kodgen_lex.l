%{
#include "grammar.tab.h"
#include <iostream>
#include <cstring>
using namespace std;
%}

%option noyywrap

%%

"//".* {}

[0-9]+ { 
    // yylval.egesz = atoi(yytext);
    yylval.ertek = strdup(yytext);
    return SZAM; 
}

[0-9]+\.[0-9]+ { 
    // yylval.valos = atof(yytext);
    yylval.ertek = strdup(yytext);
    return VSZAM; 
}

int { return INT; }

float { return FLOAT; }

ki { return KI; }

[a-z]+ { 
    yylval.vnev = strdup(yytext);
    return VALT;
}

[+\-=()] { return yytext[0]; }

[ \t\r\n] {}

. { cout << "Lex. hiba: " << yytext << endl; }

%%

