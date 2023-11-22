%{
#include <stdio.h>
#include <string>
using namespace std;

string str_builder;
unsigned int yycolumn = 1;

void parse_success(const char*, const char*);
void parse_error();
void parse_string();
void parse_error_str();
%}

%option noyywrap
%option yylineno

%x STRING

LINE_TERMINATOR             \r|\n|\r\n
INPUT_CHARACTER             [^\r\n]
WHITESPACE                  [ \t]+
IDENTIFIER                  [a-zA-Z_][a-zA-Z0-9_]*
BINARY_OPERATOR             [+\-*/]
INTEGER                     [\-+]?([1-9][0-9]*|0)
DECIMAL                     {INTEGER}.[0-9]+

%%

"take"                      { parse_success("keyword", yytext); }
"as"                        { parse_success("keyword", yytext); }
"always"                    { parse_success("keyword", yytext); }
"let"                       { parse_success("keyword", yytext); }
"be"                        { parse_success("keyword", yytext); }
"when"                      { parse_success("keyword", yytext); }
"otherwise"                 { parse_success("keyword", yytext); }
"exit"                      { parse_success("keyword", yytext); }
"while"                     { parse_success("keyword", yytext); }
"increase"                  { parse_success("keyword", yytext); }
"decrease"                  { parse_success("keyword", yytext); }
"write"                     { parse_success("keyword", yytext); }
"read"                      { parse_success("keyword", yytext); }

"is"                        { parse_success("relation_op", yytext); }
"not"                       { parse_success("relation_op", yytext); }
"greater"                   { parse_success("relation_op", yytext); }
"less"                      { parse_success("relation_op", yytext); }
"than"                      { parse_success("relation_op", yytext); }
"or"                        { parse_success("relation_op", yytext); }
"equal"                     { parse_success("relation_op", yytext); }
"to"                        { parse_success("relation_op", yytext); }

"integer"                   { parse_success("type", yytext); }
"decimal"                   { parse_success("type", yytext); }
"bool"                      { parse_success("type", yytext); }
"text"                      { parse_success("type", yytext); }

"["                         { parse_success("block_sep", yytext); }
"]"                         { parse_success("block_sep", yytext); }

"true"|"false"              { parse_success("bool_lit", yytext); }
{DECIMAL}                   { parse_success("decimal_lit", yytext); }
{INTEGER}                   { parse_success("integer_lit", yytext); }

{IDENTIFIER}                { parse_success("identifier", yytext); }

{BINARY_OPERATOR}           { parse_success("binary_op", yytext); }

"'"                         { BEGIN(STRING); str_builder = ""; parse_string(); }
<STRING>"\\'"               { parse_string(); }
<STRING>"'"                 { parse_string(); parse_success("str_lit", str_builder.c_str()); BEGIN(INITIAL); }
<STRING>.                   { parse_string(); }
<STRING>{LINE_TERMINATOR}   { parse_error_str(); BEGIN(INITIAL); }

"#".*                       { /* comment */ }

{LINE_TERMINATOR}           { yycolumn = 1; }
{WHITESPACE}                { yycolumn += yyleng; }
.                           { parse_error(); }

%%

int main() {
	yylex();
}

void parse_success(const char* type, const char* token) {
    printf("[%4d %4d %4d]  TYPE: %-15s  TOKEN: %-15s\n", yylineno, yycolumn, yyleng, type, token);
    yycolumn += yyleng;
}

void parse_error() {
    printf("[%4d %4d %4d]  ERROR: %-15s\n", yylineno, yycolumn, yyleng, yytext);
    yycolumn += yyleng;
}

void parse_error_str() {
    printf("[%4d %4d %4d]  ERROR: unterminated string\n", yylineno, yycolumn, yyleng);
    yycolumn += yyleng;
}

void parse_string() {
    str_builder += string(yytext);
    yycolumn += yyleng;
}