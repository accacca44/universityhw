%{
#include <stdio.h>
#include <string.h>
#include "akos.tab.h"
using namespace std;

typedef struct {
  int row;
  int col;
} ERROR_POS;

ERROR_POS errorPos = {1,1};
int yycol = 1;

void printToken(const char* type);
void printError();
%}

%option noyywrap
%option yylineno

WHITESPACE          [ \t]
NEWLINE             [\n]

INTEGER             [1-9][0-9]*|0
DOUBLE              [0-9]+[.][0-9]*([eE][-+]?[0-9]+)?
IDENTIFIER          [a-zA-Z_][a-zA-Z0-9_]*

TYPE_INT            (int)
TYPE_DOUBLE         (double)
TYPE_BOOL           (bool)
ASSIGNMENT_OP       (=)
%%

{WHITESPACE}            { yycol += yyleng; errorPos.col = yycol; }
{NEWLINE}               { yycol = 1; errorPos.col = 1; errorPos.row = yylineno; }

{TYPE_INT}              { printToken("TYPE_INT"); return TYPE_INT; }
{TYPE_DOUBLE}           { printToken("TYPE_DOUBLE"); return TYPE_DOUBLE; }
{TYPE_BOOL}             { printToken("TYPE_BOOL"); return TYPE_BOOL; }

"and"                   { printToken("REL_AND"); return REL_AND;}
"or"                    { printToken("REL_OR"); return REL_OR;}
"!"                     { printToken("REL_NOT"); return REL_NOT; }
"!="                    { printToken("REL_NOTEQ"); return REL_NOTEQ;}
"=="                    { printToken("REL_EQ"); return REL_EQ;}
"<"                     { printToken("REL_LT"); return REL_LT;}
">"                     { printToken("REL_GT"); return REL_GT;}
"<="                    { printToken("REL_LTE"); return REL_LTE;}
">="                    { printToken("REL_GTE"); return REL_GTE;}

"till"                  { printToken("KEY_WHILE"); return KEY_WHILE;}
"test"                  { printToken("KEY_IF"); return KEY_IF;}
"instead"               { printToken("KEY_ELSE"); return KEY_ELSE;}

"-"                     { printToken("OP_SUB"); return OP_SUB;}
"+"                     { printToken("OP_ADD"); return OP_ADD;}
"*"                     { printToken("OP_MUL"); return OP_MUL;}
"/"                     { printToken("OP_DIV"); return OP_DIV;}
"%"                     { printToken("OP_MOD"); return OP_MOD;}

"get"                   { printToken("IO_READ"); return IO_READ; }
"log"                   { printToken("IO_WRITE"); return IO_WRITE;}

{ASSIGNMENT_OP}         { printToken("ASSIGNMENT_OP"); return ASSIGNMENT_OP;}
{INTEGER}               { printToken("INTEGER"); yylval.integer_value = atoi(yytext); return INTEGER;}
{DOUBLE}                { printToken("DOUBLE"); yylval.double_value = atof(yytext); return DOUBLE;}
"true"                  { printToken("TRUE"); return TRUE; }
"false"                 { printToken("FALSE"); return FALSE; } 
{IDENTIFIER}            { printToken("IDENTIFIER"); yylval.variable_name = strdup(yytext); return IDENTIFIER;}

"{"               { printToken("OPEN_BRACE"); return OPEN_BRACE;}
"}"               { printToken("CLOSE_BRACE"); return CLOSE_BRACE;}
"("               { printToken("OPEN_PAREN"); return OPEN_PAREN;}
")"               { printToken("CLOSE_PAREN"); return CLOSE_PAREN;}
";"               { printToken("SEMICOLON"); return SEMICOLON;}
","               { printToken("COMMA"); return COMMA;}
\#.*			  { printToken("ONE_LINE_COMMENT");}

.                 { printError(); }

%%

void printToken(const char* type) {
    // printf("[%4d %4d %4d]  TYPE: %-10s TOKEN: %-15s\n", yylineno, yycol, yyleng, type, yytext);
    errorPos.col = yycol;
    yycol += yyleng;
}

void printError() {
    errorPos.col = yycol;
    printf("[%4d %4d %4d]  ERROR: %-15s\n", yylineno, errorPos.col, yyleng, yytext);
    yycol += yyleng;
}

