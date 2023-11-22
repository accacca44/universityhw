%{
#include <iostream>
using namespace std;
%}

%option noyywrap

%%

[-+]?[0-9]+(\.[0-9]+)? { cout << "Valid floating-point number: " << yytext << endl; }
.|\n { ; }
%%

int main() {
    yylex();
    return 0;
}
