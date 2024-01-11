%{
#include <algorithm> 
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <unordered_map>

using namespace std;

#define max(a, b) ((a > b) ? a : b)

extern int yylex();

typedef struct {
  int row;
  int col;
} ERROR_POS;

extern ERROR_POS errorPos;

// Symbol table for variables
unordered_map<string, int> symbolTable;

ofstream out;
const int TAB_SIZE = 4;
int depth = 0;

void yyerror(string);
void declare(char*, int);
bool checkDeclared(char*);
void checkType(char*, int);
void checkAssignmentType(int, int);
int getType(char*);
void sameTypes(int, int);
int commonType(int, int);
void printTable();
string indent();

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
%token          OPEN_BRACE CLOSE_BRACE OPEN_PAREN CLOSE_PAREN SEMICOLON

%left         REL_OR
%left         REL_AND
%left         OP_MOD 
%left         OP_ADD OP_SUB
%left         OP_MUL OP_DIV
%nonassoc     ASSIGNMENT_OP REL_EQ REL_NOTEQ REL_LT REL_GT REL_LTE REL_GTE

%type<type> value expression logical_expression relational_expression

%%

program: 
      %empty
    | program input
;

input:
      SEMICOLON { out << ";\n"; }
    | var_declaration
    | var_assignment
    | if_statement
    | while_statement
    | read_value
    | write_value
    | error SEMICOLON
;

var_declaration:
      TYPE_INT IDENTIFIER SEMICOLON { declare($<variable_name>2, 1); out << indent() << "int " << $<variable_name>2 << ";\n"; }
    | TYPE_DOUBLE IDENTIFIER SEMICOLON { declare($<variable_name>2, 2); out << indent() << "double " << $<variable_name>2 << ";\n"; }
    | TYPE_BOOL IDENTIFIER SEMICOLON { declare($<variable_name>2, 0); out << indent() << "bool " << $<variable_name>2 << ";\n"; }
    | TYPE_INT IDENTIFIER ASSIGNMENT_OP { out << indent() << "int " << $<variable_name>2 << "="; } expression SEMICOLON { declare($<variable_name>2, 1); checkAssignmentType(1, $<type>5); out << ";\n";}
    | TYPE_DOUBLE IDENTIFIER ASSIGNMENT_OP { out << indent() << "double " << $<variable_name>2 << "="; } expression SEMICOLON { declare($<variable_name>2, 2); checkAssignmentType(2, $<type>5); out << ";\n"; }
    | TYPE_BOOL IDENTIFIER ASSIGNMENT_OP { out << indent() << "bool " << $<variable_name>2 << "="; } expression SEMICOLON { declare($<variable_name>2, 0); checkAssignmentType(0, $<type>5); out << ";\n"; }
;

var_assignment:
    IDENTIFIER ASSIGNMENT_OP { out << indent() << $<variable_name>1 << "="; } expression SEMICOLON { if(checkDeclared($<variable_name>1) == true) { checkAssignmentType(getType($<variable_name>1), $<type>4); } out << ";\n"; }
;

expression:
      value { $$ = $<type>1; }
    | OP_ADD { out << "+"; } expression { $$ = $3; }
    | OP_SUB { out << "-"; } expression { $$ = $3; }
    | expression OP_ADD { out << "+"; } expression { $$ = commonType($<type>1, $<type>4); }
    | expression OP_SUB { out << "-"; } expression { $$ = commonType($<type>1, $<type>4); }
    | expression OP_MUL { out << "*"; } expression { $$ = commonType($<type>1, $<type>4); }
    | expression OP_DIV { out << "/"; } expression { $$ = commonType($<type>1, $<type>4); }
    | expression OP_MOD { out << "%"; } expression { $$ = commonType($<type>1, $<type>4); }
    | OPEN_PAREN { out << "("; } expression CLOSE_PAREN { $$ = $<type>3; out << ")"; }
;


logical_expression:
      expression { $$ = $<type>1; }
    | relational_expression { $$ = $<type>1; }
    | relational_expression REL_AND { out << "&&"; } relational_expression { $$ = commonType($<type>1, $<type>4); }
    | relational_expression REL_OR { out << "||"; } relational_expression { $$ = commonType($<type>1, $<type>4); }
    | REL_NOT OPEN_PAREN { out << "!("; } logical_expression CLOSE_PAREN { $$ = $<type>4; out << ")"; }
;

relational_expression:
    expression relation expression { $$ = 0; }
;

relation:
      REL_EQ { out << "=="; }
    | REL_NOTEQ { out << "!="; }
    | REL_GT { out << ">"; }
    | REL_LT { out << "<"; }
    | REL_GTE { out << ">="; }
    | REL_LTE { out << "<="; }

value: 
      INTEGER { $$ = 1; out << $<integer_value>1; }
    | TRUE { $$ = 0; out << "true"; }
    | FALSE { $$ = 0; out << "false"; }
    | DOUBLE { $$ = 2; out << $<double_value>1; }
    | IDENTIFIER { checkDeclared($<variable_name>1); $$ = getType($<variable_name>1); out << $<variable_name>1; }
;

if_statement:
      KEY_IF OPEN_PAREN { out << indent() << "if("; } logical_expression CLOSE_PAREN OPEN_BRACE { out << ") {\n"; depth++; } program CLOSE_BRACE { checkAssignmentType(0, $<type>4); depth--; out << indent() << "}\n"; }
    | KEY_IF OPEN_PAREN { out << indent() << "if("; } logical_expression CLOSE_PAREN OPEN_BRACE { out << ") {\n"; depth++; } program CLOSE_BRACE KEY_ELSE OPEN_BRACE { depth--; out<< indent() << "} else {\n"; depth++; } program CLOSE_BRACE { checkAssignmentType(0, $<type>4); depth--; out << indent() << "}\n"; }
    | KEY_IF OPEN_PAREN error CLOSE_PAREN OPEN_BRACE program CLOSE_BRACE
    | KEY_IF OPEN_PAREN error CLOSE_PAREN OPEN_BRACE program CLOSE_BRACE KEY_ELSE OPEN_BRACE program CLOSE_BRACE
;

while_statement:
  KEY_WHILE OPEN_PAREN { out << indent() << "while("; } logical_expression CLOSE_PAREN OPEN_BRACE { out <<") {\n"; depth++; } program CLOSE_BRACE { checkAssignmentType(0, $<type>4); depth--; out << indent() << "}\n"; }
;

read_value:
  IO_READ OPEN_PAREN IDENTIFIER CLOSE_PAREN SEMICOLON { checkDeclared($<variable_name>3); out << indent() << "cin >> " << $<variable_name>3 << ";\n"; }
  ;

write_value:
  IO_WRITE OPEN_PAREN {out << indent() << "cout << "; } expression CLOSE_PAREN SEMICOLON { out << " << endl;\n"; }
  

%%

int main() {
  out.open("akos.cpp");
  out << "#include <iostream>\n" 
      << "using namespace std;\n"
      << '\n' 
      << "int main()\n"
      << "{\n";
  depth++;
  yyparse();
  printf("Parsed!\n");

  out << indent() << "return 0;\n"
    << "}\n"
    << '\n';
  out.close();

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
  printTable();
}

bool checkDeclared(char* var) {
  if (symbolTable.find(var) == symbolTable.end()) {
    cout << "Undeclared variable " << var << " in line: " << errorPos.row << ", at charachter: " << errorPos.col << "\n";
    return false;
  }
  printTable();
  return true;
}

int getType(char* var) {
  auto it = symbolTable.find(var);
  if (it != symbolTable.end()) {
    return it->second;
  } else {
    return -1;
  }
}

void checkType(char* var, int expectedType) {
  int actualType = getType(var);

  if (actualType == -1) {
    cout << "Variable " << var << " used before declaration in line: " << errorPos.row << ", at charachter: " << errorPos.col << "\n";
    return;  
  }

  if (actualType != expectedType) {
    cout << "Type mismatch for variable " << var << " in line: " << errorPos.row << ", at charachter: " << errorPos.col << "\n";
  }
}

int commonType(int a, int b) {
  if(a == -1 || b == -1) return a;
  else if(a == b) return a;
  else return max(a,b);
}


void checkAssignmentType(int a, int b) {
  cout << " Types: " << a << " " << b << endl;
  if (a < b) {
    cout << "Warning, data loss in conversion in line: " << errorPos.row << ", at charachter: " << errorPos.col << "\n";
  }
}

void printTable() { 
  cout << "==START==" << endl;
   std::for_each(symbolTable.begin(), symbolTable.end(), 
                  [](std::pair<std::string, int> p) { 
                      std::cout << p.first 
                                << " :: " << p.second 
                                << std::endl; 
                  }); 
  cout << "==END==" << endl;
}

string indent() {
    string t = "";
    for (int i = 0; i < depth; i++)
        t += "  ";
    return t;
}