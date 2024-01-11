%{
#include <iostream>
#include <map>
using namespace std;
void yyerror(const char *s);
int yylex();

map<string, int> szimbolumtabla;

void ellenoriz_hivatkozas(char *v);
void deklaralas(char *v, int tip);
string indentalas();

#define max(a, b) ((a > b) ? a : b)

string KOD;
int szint;
%}

%left '+' '-'
%left '*' '/'

%union {
    char *vnev;
    int tipus;
    // int egesz;
    // float valos;
    char *ertek;
}

%token SZAM VSZAM
%token VALT 
%token KI 
%token INT FLOAT
%type <tipus> kif

%%

program: ut
       | program ut
;

ut: deklaralas
  | ertekadas
  | kiiras
;

deklaralas: INT VALT { deklaralas($<vnev>2, 0); KOD += indentalas() + "int " + $<vnev>2 + ";\n"; }
          | FLOAT VALT { deklaralas($<vnev>2, 1); KOD += indentalas() + "float " + $<vnev>2 + ";\n"; }
;

ertekadas: VALT '=' {KOD += indentalas() + $<vnev>1 + " = ";} kif { ellenoriz_hivatkozas($<vnev>1); 
                                                             if (szimbolumtabla[$<vnev>1] < $4) 
                                                                cout << "Adatvesztéses konverzió!" << endl;
                                                             KOD += ";\n";}
;

kiiras: KI { KOD += indentalas() + "cout << "; } kif { KOD += " << endl;\n"; }
;

kif: SZAM { $$ = 0; KOD += $<ertek>1; }
   | VSZAM { $$ = 1; KOD += $<ertek>1; }
   | VALT { ellenoriz_hivatkozas($<vnev>1); $$ = szimbolumtabla[$<vnev>1]; KOD += $<vnev>1; }
   | kif '+' { KOD += "+"; } kif { $$ = max($1, $4); }
   | kif '-' { KOD += "-"; } kif { $$ = max($1, $4); }
;

%%

int main() {
    szint = 0;

    KOD = "#include <iostream>\n\
using namespace std;\n\n\
int main() {\n";
    
    yyparse();
    
    KOD += "\n}";
    cout << KOD << endl;
}

void yyerror(const char *s){
    cout << s << endl;
}

void ellenoriz_hivatkozas(char *v) {
    if (szimbolumtabla.find(v) == szimbolumtabla.end()) {
        cout << "Nem deklaralt valtozo: " << v << endl;
    }
}

void deklaralas(char *v, int tip) {
    if (szimbolumtabla.find(v) == szimbolumtabla.end()) {
        szimbolumtabla[v] = tip;
    } else {
        cout << "Ujradeklaralas: " << v << endl;
    }
}

string indentalas() {
    string t = "";
    for (int i = 0; i <= szint; i++)
        t += "  ";
    return t;
}
