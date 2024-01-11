%{
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

extern int yylex();
void yyerror(string);

typedef struct {
  int row;
  int col;
} ERROR_POS;

extern ERROR_POS errorPos;

enum VarType {
  Integer,
  Double,
  Boolean,
  Error = -1
};

// Symbol table for variables
unordered_map<string, int> symbolTable;

void declare(char*, int);
void checkDeclared(char*);
void checkType(char*, int);
int getType(char*);
void sameTypes(char*, char*);

%}

%define parse.error verbose

%union {
  int         type;
  int         integer_value;
  double      double_value;
  char*       variable_name;
}

%token<variable_name>      IDENTIFIER
%token<integer_value>      INTEGER
%token<double_value>       DOUBLE
%token                     TRUE FALSE

%token          TYPE_INT
%token          TYPE_DOUBLE
%token          TYPE_BOOL

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

%type<type> value

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
    | error SEMICOLON
;

var_declaration:
      TYPE_INT IDENTIFIER SEMICOLON { declare($<variable_name>2, 0); }
    | TYPE_DOUBLE IDENTIFIER SEMICOLON { declare($<variable_name>2, 1); }
    | TYPE_BOOL IDENTIFIER SEMICOLON { declare($<variable_name>2, 2); }
    | TYPE_INT IDENTIFIER ASSIGNMENT_OP expression SEMICOLON { declare($<variable_name>2, 0); checkType($<variable_name>2, getType($<variable_name>4)); }
    | TYPE_DOUBLE IDENTIFIER ASSIGNMENT_OP expression SEMICOLON { declare($<variable_name>2, 1); checkType($<variable_name>2, getType($<variable_name>4)); }
    | TYPE_BOOL IDENTIFIER ASSIGNMENT_OP expression SEMICOLON { declare($<variable_name>2, 2); checkType($<variable_name>2, getType($<variable_name>4)); }
;

var_assignment:
    IDENTIFIER ASSIGNMENT_OP expression SEMICOLON { checkDeclared($<variable_name>1); checkType($<variable_name>1, getType($<variable_name>3)); }
;

expression:
      value
    | OP_ADD expression { $$ = $2; }
    | OP_SUB expression { $$ = $2; }
    | expression OP_ADD expression { sameTypes($1, $3); $$ = $1; }
    | expression OP_SUB expression { sameTypes($1, $3); $$ = $1; }
    | expression OP_MUL expression { sameTypes($1, $3); $$ = $1; }
    | expression OP_DIV expression { sameTypes($1, $3); $$ = $1; }
    | expression OP_MOD expression { sameTypes($1, $3); $$ = $1; }
    | OPEN_PAREN expression CLOSE_PAREN { $$ = $2; }
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
      INTEGER { $$ = 0; }
    | TRUE { $$ = 2; }
    | FALSE { $$ = 3; }
    | DOUBLE { $$ = 1; }
    | IDENTIFIER { checkDeclared($<variable_name>1); $$ = symbolTable.at($1); }
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
  IO_READ OPEN_PAREN IDENTIFIER CLOSE_PAREN SEMICOLON { checkDeclared($<variable_name>3); }
  ;

write_value:
  IO_WRITE OPEN_PAREN expression CLOSE_PAREN SEMICOLON
  

%%

int main() {
  yyparse();

  printf("Parsed!\n");
}

void yyerror(string s) {
  cout << "error in line: " << errorPos.row << ", at charachter: " << errorPos.col
    << " -> " << s << "\n";
}

void declare(char* var, int type) {
  if (symbolTable.find(var) == symbolTable.end()) {
    symbolTable[var] = type;
  } else {
    cout << "Redeclaration for " << var << " in line: " << errorPos.row << ", at charachter: " << errorPos.col << "\n";
  }
}

void checkDeclared(char* var) {
  if (symbolTable.find(var) == symbolTable.end()) {
    cout << "Undeclared variable " << var << " in line: " << errorPos.row << ", at charachter: " << errorPos.col << "\n";
  }
}

int getType(char* var) {
  auto it = symbolTable.find(var);
  if (it != symbolTable.end()) {
    return it->second;
  } else {
    cout << "Variable " << var << " used before declaration in line: " << errorPos.row << ", at charachter: " << errorPos.col << "\n";
    return VarType::Error;
  }
}

void checkType(char* var, int expectedType) {
  int actualType = getType(var);

  if (actualType == VarType::Error) {
    return;  // Error message already printed in getType function
  }

  if (actualType != expectedType) {
    cout << "Type mismatch for variable " << var << " in line: " << errorPos.row << ", at charachter: " << errorPos.col << "\n";
  }
}

void sameTypes(char* a, char* b) {
    int typeA = getType(a);
    int typeB = getType(b);

    if (typeA != typeB) {
        cout << "Type mismatch between " << a << " and " << b << " in line: " << errorPos.row << ", at charachter: " << errorPos.col << "\n";
    }
}
