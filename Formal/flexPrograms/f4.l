%{
#include <iostream>
using namespace std;
%}

%option noyywrap
%x COMMENT

%%

<INITIAL>"/*" { BEGIN(COMMENT); }
<COMMENT>"*/" { BEGIN(INITIAL); }
.|\n {;}
%%

int main() {
    yylex();
    return 0;
}
