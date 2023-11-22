%{
#include <iostream>
using namespace std;
%}

%option noyywrap
%x COMMENT
%x STRING

%%

<INITIAL>"//" { BEGIN(COMMENT); }
<COMMENT>"\n" { BEGIN(INITIAL); }
<COMMENT>. { }

<INITIAL>\" { BEGIN(STRING); }
<STRING>\" { BEGIN(INITIAL); }
%%

int main() {
    yylex();
    return 0;
}
