%{
#include <stdio.h>
#include <stdlib.h>
using namespace std;

const char* DEBUG_BIS_ENV = "DEBUG_BIS";

bool was_error = false;

typedef struct {
  int row;
  int column;
} error_info;

extern error_info error;

extern int yylex();
void yyerror(const char*);
%}

%define parse.error verbose

%union {
  int         int_val;
  float       dec_val;
  char*       text_val;
  bool        bool_val;
  char*       id_name;
}

%token                TAKE_KEYWORD
%token                AS_KEYWORD
%token                ALWAYS_KEYWORD
%token                LET_KEYWORD
%token                BE_KEYWORD
%token                WHEN_KEYWORD
%token                OTHERWISE_KEYWORD
%token                EXIT_KEYWORD
%token                WHILE_KEYWORD
%token                INCREASE_KEYWORD
%token                DECREASE_KEYWORD
%token                WRITE_KEYWORD
%token                READ_KEYWORD

%token                IS_RELATION
%token                GREATER_RELATION
%token                LESS_RELATION
%token                THAN_RELATION
%token                EQUAL_RELATION
%token                TO_RELATION

%token                AND_LOGICAL
%token                OR_LOGICAL
%token                NOT_LOGICAL

%token                INTEGER_TYPE
%token                DECIMAL_TYPE
%token                BOOL_TYPE
%token                TEXT_TYPE

%token                BLOCK_SEP_OPEN
%token                BLOCK_SEP_CLOSE
%token                PARAM_OPEN
%token                PARAM_CLOSE

%token                PLUS_OPERATOR
%token                MINUS_OPERATOR
%token                MULTI_OPERATOR
%token                DIV_OPERATOR

%token<id_name>       IDENTIFIER

%token<int_val>       INTEGER_LITERAL
%token<dec_val>       DECIMAL_LITERAL
%token<bool_val>      BOOL_LITERAL
%token<text_val>      TEXT_LITERAL

%token                EOL

%left OR_LOGICAL
%left AND_LOGICAL
%left PLUS_OPERATOR MINUS_OPERATOR
%left MULTI_OPERATOR DIV_OPERATOR

%%

program:
    %empty
  | program input
  ;

input:
    EOL
  | variable_declaration
  | variable_assignment
  | if_statement
  | while_statement
  | read_directive
  | write_directive
  | exit
  | error EOL     { yyerrok; }
  ;

variable_declaration:
    TAKE_KEYWORD IDENTIFIER AS_KEYWORD expression EOL
  | TAKE_KEYWORD IDENTIFIER AS_KEYWORD expression ALWAYS_KEYWORD EOL
  | TAKE_KEYWORD IDENTIFIER type EOL
  ;

variable_assignment:
    LET_KEYWORD IDENTIFIER BE_KEYWORD expression EOL
  | LET_KEYWORD IDENTIFIER INCREASE_KEYWORD EOL
  | LET_KEYWORD IDENTIFIER DECREASE_KEYWORD EOL
  ;

expression:
    value
  | PLUS_OPERATOR expression
  | MINUS_OPERATOR expression
  | expression PLUS_OPERATOR expression
  | expression MINUS_OPERATOR expression
  | expression MULTI_OPERATOR expression
  | expression DIV_OPERATOR expression
  | PARAM_OPEN expression PARAM_CLOSE
  ;

logical_expression:
    expression
  | relational_expression
  | relational_expression AND_LOGICAL relational_expression
  | relational_expression OR_LOGICAL relational_expression
  | NOT_LOGICAL logical_expression
  ;

relational_expression:
    expression relation expression
  ;

relation:
    IS_RELATION
  | IS_RELATION LESS_RELATION THAN_RELATION
  | IS_RELATION LESS_RELATION THAN_RELATION EQUAL_RELATION TO_RELATION
  | IS_RELATION GREATER_RELATION THAN_RELATION
  | IS_RELATION GREATER_RELATION THAN_RELATION EQUAL_RELATION TO_RELATION
  ;

value:
    INTEGER_LITERAL
  | DECIMAL_LITERAL
  | BOOL_LITERAL
  | TEXT_LITERAL
  | IDENTIFIER
  ;

type:
    INTEGER_TYPE
  | DECIMAL_TYPE
  | BOOL_TYPE
  | TEXT_TYPE
  ;

if_statement:
    WHEN_KEYWORD logical_expression BLOCK_SEP_OPEN program BLOCK_SEP_CLOSE EOL
  | WHEN_KEYWORD logical_expression BLOCK_SEP_OPEN program BLOCK_SEP_CLOSE OTHERWISE_KEYWORD BLOCK_SEP_OPEN program BLOCK_SEP_CLOSE EOL
  | WHEN_KEYWORD error BLOCK_SEP_OPEN program BLOCK_SEP_CLOSE EOL
  | WHEN_KEYWORD error BLOCK_SEP_OPEN program BLOCK_SEP_CLOSE OTHERWISE_KEYWORD BLOCK_SEP_OPEN program BLOCK_SEP_CLOSE EOL
  ;

while_statement:
    WHILE_KEYWORD logical_expression BLOCK_SEP_OPEN program BLOCK_SEP_CLOSE EOL
  ;

read_directive:
    READ_KEYWORD IDENTIFIER EOL
  ;

write_directive:
    WRITE_KEYWORD expression EOL
  ;

exit:
    EXIT_KEYWORD EOL
  ;

%%

int main() {
  if (getenv(DEBUG_BIS_ENV))
    yydebug = 1;

  yyparse();

  if (was_error) {
    printf("Parser encountered errors.\n");
  } else {
    printf("Parser ran successfully.\n");
  }

  return was_error;
}

void yyerror(const char* msg) {
  printf("error in line %d, at character %d:\n  %s\n", error.row, error.column, msg);
  was_error = true;
}