%{
#include "common.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;

int yyerror(string);
extern int yylex();

extern ParsePosition parsePosition;

template <typename K, typename V>
class MapWithContainsFuncDarnCPlusPlus20 : public map<K, V> {
  public:
  bool contains(K key) {
    return this->count(key) != 0;
  }
};

MapWithContainsFuncDarnCPlusPlus20<string, VarType> symTable;

bool inLocal = false;
MapWithContainsFuncDarnCPlusPlus20<string, VarType> localSymTable;

ofstream out;
int depth = 0, TAB_SIZE = 4;

string pad(int addToDepth = 0) {
  depth += addToDepth;
  if (depth < 0) depth = 0;
  return string(depth * TAB_SIZE, ' ');
}

string boolVar(string varName) {
  return varName.erase(0, 1).insert(0, "__bool__");
}

/* Helper functions */
const char* varTypeStr(VarType var) {
  switch(var) {
    case Integer:
      return "Integer";
    case Real:
      return "Real";
    case Boolean:
      return "Boolean";
    default:
      return "InvalidType";
  }
}

void printSymTable() {
  cout << "Symbol Table contents:" << endl;
  for (auto itr = symTable.begin(); itr != symTable.end(); itr++) 
      cout << itr->first << " -> " << varTypeStr(itr->second) << endl;
}

bool isDeclaredVar(const char* varName) {
  if (symTable.contains(varName) || (inLocal && localSymTable.contains(varName))) return true;
  yyerror("Undeclared variable: " + string(varName));
  return false;
}

bool isSameType(VarType a, VarType b, string elementName) {
  if (a == b) return true;
  yyerror(elementName + " left and right sides differ in type");
  return false;
}

bool _declareVar(MapWithContainsFuncDarnCPlusPlus20<string, VarType>& map, string varName, VarType type) {
  if (map.contains(varName)) {
      yyerror("Redeclaration of variable: " + varName);
      return false;
    }
    map[varName] = type;
    return true;
}

bool declareVar(string varName, VarType type) {
  if (inLocal) return _declareVar(localSymTable, varName, type);
  return _declareVar(symTable, varName, type);
}

%}

%error-verbose

%union {
    bool boolean_value;
    int integer_value;
    double real_value;
    char* string_value;
    VarType variable_type;
}

%token <string_value> VAR BOOL_VAR
%token T_INTEGER T_REAL T_BOOL

%token <integer_value> CNST_INTEGER
%token <real_value> CNST_REAL
%token <boolean_value> CNST_TRUE CNST_FALSE
%token <string_value> CNST_STRING
%token OP_ASSIGN OP_EQ OP_NEQ OP_GT OP_LT OP_GEQ OP_LEQ OP_AND OP_OR OP_AS

%token DO_THIS
%token IF ENDIF
%token WHILE WHILENT

%token INPUT OUTPUT OUTPUT_ERR EXIT

%left '+' '-'
%left '*' '/' '%'
%left OP_LEQ OP_GEQ OP_GT OP_LT
%left OP_NEQ OP_EQ
%left OP_AND OP_OR
%left OP_AS

%type <variable_type> expr explicit_type_conversion
%type <boolean_value> condition
%type <string_value> var bool_var

%start program

%%
program: statement
       | program statement
;

statement: declaration
         | if
         | while
         | assignment
         | explicit_type_conversion
         | io
         | exit
         | ';' { out << pad() << ';' << endl; }
;

io: input
  | print
  | print_error
;
// ################################################ Building Blocks ################################################# //
semi: ';' { out << ';' << endl; }
;

var: VAR { if (!isDeclaredVar($1)) return UndeclaredVariable; }
;

bool_var: BOOL_VAR { if (!isDeclaredVar($1)) return UndeclaredVariable; }
;

declaration: declaration_body semi
           | declaration_body error { yyerror("Declaration should be followed by ';'.\nSyntax\n <type> <var_name>;"); }
;

declaration_body: T_INTEGER VAR   { if (!declareVar($2, Integer)) return AlreadyDeclaredVariable; out << pad() << "int " << $2; }
                | T_REAL VAR      { if (!declareVar($2, Real)) return AlreadyDeclaredVariable; out << pad() << "float " << $2; }
                | T_BOOL BOOL_VAR { if (!declareVar($2, Boolean)) return AlreadyDeclaredVariable; out << pad() << "bool " << boolVar($2); }
;

condition: expr { if ($1 != Boolean) { yyerror("Expression cannot be used as a condition"); return NonMatchingType; } }
;

expr: var           { $$ = symTable.at($1); out << $1; }
    | bool_var      { $$ = Boolean; out << boolVar($1); }
    | CNST_TRUE     { $$ = Boolean; out << "true"; }  | CNST_FALSE    { $$ = Boolean; out << "false"; }
    | CNST_INTEGER  { $$ = Integer; out << $1; }      | CNST_REAL     { $$ = Real; out << $1; }
    | expr '+'      { out << " + "; }   expr { if (!isSameType($1, $4, "Expression")) return NonMatchingType; }
    | expr '-'      { out << " - "; }   expr { if (!isSameType($1, $4, "Expression")) return NonMatchingType; }
    | expr '*'      { out << " * "; }   expr { if (!isSameType($1, $4, "Expression")) return NonMatchingType; }
    | expr '/'      { out << " / "; }   expr { if (!isSameType($1, $4, "Expression")) return NonMatchingType; }
    | expr '%'      { out << " % "; }   expr { if (($1 != $4) || $1 != Integer) { yyerror("Remainder calculation left and right sides must have type 'Integer'"); return NonMatchingType; } }
    | expr OP_AND   { out << " && "; }  expr { if (!isSameType($1, $4, "Condition")) return NonMatchingType; $$ = Boolean; } 
    | expr OP_OR    { out << " || "; }  expr { if (!isSameType($1, $4, "Condition")) return NonMatchingType; $$ = Boolean; }
    | expr OP_EQ    { out << " == "; }  expr { if (!isSameType($1, $4, "Condition")) return NonMatchingType; $$ = Boolean; }
    | expr OP_NEQ   { out << " != "; }  expr { if (!isSameType($1, $4, "Condition")) return NonMatchingType; $$ = Boolean; }
    | expr OP_GT    { out << " > "; }   expr { if (!isSameType($1, $4, "Condition")) return NonMatchingType; $$ = Boolean; }
    | expr OP_LT    { out << " < "; }   expr { if (!isSameType($1, $4, "Condition")) return NonMatchingType; $$ = Boolean; }
    | expr OP_GEQ   { out << " >= "; }  expr { if (!isSameType($1, $4, "Condition")) return NonMatchingType; $$ = Boolean; }
    | expr OP_LEQ   { out << " <= "; }  expr { if (!isSameType($1, $4, "Condition")) return NonMatchingType; $$ = Boolean; }
    | '('           { out << '('; }     expr ')' { $$ = $3; out << ')'; }
;

printable: expr
         | CNST_STRING { out << $1; }
;

exit: EXIT CNST_INTEGER { out << pad() << "exit(" << $2 << ")"; } semi
;
// ############################################### /Building Blocks ################################################# //

// ############################################ Higher Level Structures ############################################# //
assignment: var OP_ASSIGN       { out << pad() << $1 << " = "; } expr { if (!isSameType(symTable.at($1), $4, "Assignment")) return NonMatchingType; } semi
          | bool_var OP_ASSIGN  { out << pad() << boolVar($1) << " = "; } condition { if (!isSameType(symTable.at($1), Boolean, "Assignment")) return NonMatchingType; } semi
;

if: IF { out << pad() << "if ("; depth++; } cond_action_list
    ENDIF { out << endl; }
  | IF error { yyerror("'when' statement should be followed with atleast one condition and action.\nSyntax:\nwhen\n | <condition> -> <statement>\nwhenn't"); }
;

cond_action_list: cond_action
                | cond_action { out << pad() << "else if ("; depth++; } cond_action_list
;

cond_action: '|' condition { out << ") {" << endl; } 
              DO_THIS { inLocal = true; } 
              program { out << pad(-1) << '}' << endl; inLocal = false; localSymTable.clear(); }
;

while: WHILE    { out << pad() << "while "; } '|' { out << '('; } condition { out << ") {" << endl; depth++; inLocal = true; }
       DO_THIS
       program
       WHILENT  { out << pad(-1) << '}' << endl << endl; inLocal = false; localSymTable.clear(); }
;

explicit_type_conversion: var OP_AS { out << pad() << $1 << " = ("; } T_INTEGER { out << "int)" << $1; } semi { $$ = Integer; }
                        | var OP_AS { out << pad() << $1 << " = ("; } T_REAL { out << "float)" << $1; } semi  { $$ = Real; }
;

input: INPUT { out << pad() << "cin >> "; } var { out << $3; } semi
     | INPUT { out << pad() << "cin >> "; } bool_var { out << boolVar($3); } semi
;

print: OUTPUT { out << pad() << "cout << "; } printable semi
;

print_error: OUTPUT_ERR { out << pad() << "cout << \"ERROR: \" << "; } printable { out << "; exit(1)"; } semi
;
// ########################################### /Higher Level Structures ############################################# //
%%

int main() {
  out.open("generated.cpp");
  out << "#include <iostream>\n" 
      << "using namespace std;\n"
      << '\n' 
      << "int main()\n"
      << "{\n";
  depth++;

  /* yydebug = 1; */
  int ret = yyparse();
	if (ret == 0) cout << "OK!" << endl;
  printSymTable();

  out << string(TAB_SIZE, ' ') << "return 0;\n"
      << "}\n"
      << '\n';
  out.close();

  return ret;
}

int yyerror(string s) {
   cout << "[row=" << parsePosition.row << ", column=" << parsePosition.column << "]: " << s << endl;
   return 0;
}
