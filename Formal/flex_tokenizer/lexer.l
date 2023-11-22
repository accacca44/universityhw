%{
#include <stdio.h>

int yycol = 1;

void printToken(const char* type);
void printError();
%}

%option noyywrap
%option yylineno

WHITESPACE          [ \t]
NEWLINE             [\n]
DIGIT               [0-9]
INTEGER             [-+]?[1-9][0-9]*|0
DOUBLE              [-+]?[0-9]+[.][0-9]*([eE][-+]?[0-9]+)?
IDENTIFIER          [a-zA-Z_][a-zA-Z0-9_]*
VAR_TYPE            (int|double)
RELATION            (and|or|!=|==|<|>|<=|>=)
SCOPE               (till|test|instead)
ARITHMETIC_OP       [-+*/%]
ASSIGNMENT_OP       (=)
IO                  (get|log)

%%

{WHITESPACE}            { yycol += yyleng; }
{NEWLINE}               { yycol = 1; }

{VAR_TYPE}              { printToken("VAR_TYPE"); }
{RELATION}              { printToken("RELATION"); }
{SCOPE}                 { printToken("SCOPE"); }
{ARITHMETIC_OP}         { printToken("ARITHMETIC_OP"); }
{IO}                    { printToken("IO"); }
{ASSIGNMENT_OP}         { printToken("ASSIGNMENT_OP"); }
{INTEGER}               { printToken("INTEGER"); }
{DOUBLE}                { printToken("DOUBLE"); }
{IDENTIFIER}            { printToken("IDENTIFIER"); }

"{"               { printToken("OPEN_BRACE"); }
"}"               { printToken("CLOSE_BRACE"); }
"("               { printToken("OPEN_PAREN"); }
")"               { printToken("CLOSE_PAREN"); }
";"               { printToken("SEMICOLON"); }
","               { printToken("COMMA"); }

.                 { printError(); }

%%

int main() {
    yylex();
}

void printToken(const char* type) {
    printf("[%4d %4d %4d]  TYPE: %-10s TOKEN: %-15s\n", yylineno, yycol, yyleng, type, yytext);
    yycol += yyleng;
}

void printError() {
    printf("[%4d %4d %4d]  ERROR: %-15s\n", yylineno, yycol, yyleng, yytext);
    yycol += yyleng;
}
