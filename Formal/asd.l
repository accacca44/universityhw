%{
#include <stdio.h>

unsigned int yycolumn = 1;

void parse_success(const char*);
void parse_error();
%}

%option noyywrap
%option yylineno

%x STRING

LINE_TERMINATOR         \r|\n|\r\n
INPUT_CHARACTER         [^\r\n]
WHITESPACE              [ \t]
DIGIT                   [0-9]
IDENTIFIER              [a-zA-Z_][a-zA-Z0-9_]*

%%

"take"                  { parse_success("keyword"); }
"as"                    { parse_success("keyword"); }
"always"                { parse_success("keyword"); }
"let"                   { parse_success("keyword"); }
"be"                    { parse_success("keyword"); }
"when"                  { parse_success("keyword"); }
"otherwise"             { parse_success("keyword"); }
"exit"                  { parse_success("keyword"); }
"while"                 { parse_success("keyword"); }
"increase"              { parse_success("keyword"); }
"decrease"              { parse_success("keyword"); }
"write"                 { parse_success("keyword"); }
"read"                  { parse_success("keyword"); }

"is"                    { parse_success("relation"); }
"not"                   { parse_success("relation"); }
"greater"               { parse_success("relation"); }
"less"                  { parse_success("relation"); }
"than"                  { parse_success("relation"); }
"or"                    { parse_success("relation"); }
"equal"                 { parse_success("relation"); }
"to"                    { parse_success("relation"); }

{LINE_TERMINATOR}       { yycolumn = 1; }
{WHITESPACE}+           { yycolumn += yyleng; }
.                       { parse_error(); }

%%

int main() {
	yylex();
}

void parse_success(const char* type) {
    printf("[%4d %4d %4d]  TYPE: %-10s TOKEN: %-15s\n", yylineno, yycolumn, yyleng, type, yytext);
    yycolumn += yyleng;
}

void parse_error() {
    printf("[%4d %4d %4d]  ERROR: %-15s\n", yylineno, yycolumn, yyleng, yytext);
    yycolumn += yyleng;
}