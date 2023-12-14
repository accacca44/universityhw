%{
#include <iostream>
using namespace std;

extern int yylex();
void yyerror(string);

typedef struct {
  int row;
  int col;
} ERROR_POS;

extern ERROR_POS errorPos;
%}

%define parse.error verbose

%union {
  int         integer_value;
  double      double_value;
  char*       variable_name;
}

%token<variable_name>      IDENTIFIER
%token<integer_value>      INTEGER
%token<double_value>       DOUBLE


%token          TYPE_INT
%token          TYPE_DOUBLE

%token          ASSIGNMENT_OP
%token          REL_AND REL_OR REL_NOT REL_NOTEQ REL_EQ REL_LT REL_GT REL_LTE REL_GTE
%token          KEY_WHILE KEY_IF KEY_ELSE
%token          OP_SUB OP_ADD OP_MUL OP_DIV OP_MOD
%token          IO_READ IO_WRITE           
%token          OPEN_BRACE CLOSE_BRACE OPEN_PAREN CLOSE_PAREN SEMICOLON COMMA


%left         REL_OR
%left         REL_AND
%left         OP_MOD 
%left         OP_ADD OP_SUB
%left         OP_MUL OP_DIV
%nonassoc     ASSIGNMENT_OP REL_EQ REL_NOTEQ REL_LT REL_GT REL_LTE REL_GTE

%%

program: 
      %empty
    | program input
;

input:
      SEMICOLON
    | var_declaration
    | var_assignment
    | if_statement
    | while_statement
    | read_value
    | write_value
    | error SEMICOLON   { yyerrok; }
;

var_declaration:
      TYPE_INT IDENTIFIER SEMICOLON
    | TYPE_DOUBLE IDENTIFIER SEMICOLON
    | TYPE_INT IDENTIFIER ASSIGNMENT_OP expression SEMICOLON
    | TYPE_DOUBLE IDENTIFIER ASSIGNMENT_OP expression SEMICOLON
;

var_assignment:
    IDENTIFIER ASSIGNMENT_OP expression SEMICOLON
;

expression:
      value
    | OP_ADD expression
    | OP_SUB expression
    | expression OP_ADD expression
    | expression OP_SUB expression
    | expression OP_MUL expression
    | expression OP_DIV expression
    | expression OP_MOD expression
    | OPEN_PAREN expression CLOSE_PAREN
;

logical_expression:
      expression
    | relational_expression
    | relational_expression REL_AND relational_expression
    | relational_expression REL_OR relational_expression
    | REL_NOT OPEN_PAREN logical_expression CLOSE_PAREN
;

relational_expression:
    expression relation expression
;

relation:
      REL_EQ
    | REL_NOTEQ
    | REL_GT
    | REL_LT
    | REL_GTE
    | REL_LTE 

value: 
      INTEGER
    | DOUBLE
    | IDENTIFIER
;

if_statement:
      KEY_IF OPEN_PAREN logical_expression CLOSE_PAREN OPEN_BRACE program CLOSE_BRACE
    | KEY_IF OPEN_PAREN logical_expression CLOSE_PAREN OPEN_BRACE program CLOSE_BRACE KEY_ELSE OPEN_BRACE program CLOSE_BRACE
    | KEY_IF OPEN_PAREN error CLOSE_PAREN OPEN_BRACE program CLOSE_BRACE
    | KEY_IF OPEN_PAREN error CLOSE_PAREN OPEN_BRACE program CLOSE_BRACE KEY_ELSE OPEN_BRACE program CLOSE_BRACE
;

while_statement:
  KEY_WHILE OPEN_PAREN logical_expression CLOSE_PAREN OPEN_BRACE program CLOSE_BRACE
;

read_value:
  IO_READ OPEN_PAREN IDENTIFIER CLOSE_PAREN SEMICOLON
  ;

write_value:
  IO_WRITE OPEN_PAREN IDENTIFIER CLOSE_PAREN SEMICOLON
  

%%

int main() {
  yyparse();

  printf("Parser runs - OK!\n");
}

void yyerror(string s) {
  cout << "error in line: " << errorPos.row << ", at charachter: " << errorPos.col
    << " -> " << s << "\n";
}