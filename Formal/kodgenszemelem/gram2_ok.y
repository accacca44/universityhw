%{
#include <iostream>
#include <map>
using namespace std;
void yyerror(const char *s);
int yylex();

int i;
%}

%left '+' '-'

%token TIPUS
%token VALT
%token SZAM

%%

program: ut
       | program ut
;

ut: deklaralas
  | ertekadas
;

deklaralas: TIPUS VALT { i = 1; }
          | TIPUS VALT { i = 2; } '=' kif
;

ertekadas: VALT '=' kif
;

kif: VALT
   | SZAM
   | kif '+' kif
   | kif '-' kif
   | '(' kif ')'
   | '-' kif
;

%%

int main() {
    yyparse();
    return 0;
}

void yyerror(const char *s){
    cout << s << endl;
}
