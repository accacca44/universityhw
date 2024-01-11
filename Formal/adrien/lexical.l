%{
#include "common.h"
#include "parser.tab.h"
#include <iostream>
using namespace std;

#define TAB_SIZE 4

ParsePosition parsePosition = { 1, 0 };

bool debug = true;

void updatePos() {
    // Advance to next row is we hit a newline character
    if (yytext[0] == '\n') {
        parsePosition.row = yylineno;
        parsePosition.column = 1;
    } else if (yytext[0] == '\t') {
        parsePosition.column += TAB_SIZE;
    } else {
        parsePosition.column += yyleng;
    }
}

void printToken(const char* bisonEquivalent) {
    cout << "Lexical | [row=" << parsePosition.row << ", column=" << parsePosition.column << "]: Token ('" << bisonEquivalent << "'): '" << yytext << "'" << endl;
}

void processToken(const char* bisonEquivalent) {
    if (debug) printToken(bisonEquivalent);
    updatePos();
}
%}

%option noyywrap
%option yylineno

SPACE           " "
TAB             [\t]

DIGIT           [0-9]
NON_ZERO_DIGIT  [1-9]

/* Types */
T_BOOL          "boolean"
T_INTEGER       "integer"
T_REAL          "real"

/* Functions */
IN              "#in"
OUT             "#out"
PRINT_ERR       "#err"
EXIT            "#exit"

F_ADD           "#add"
F_SUB           "#sub"
F_MUL           "#mul"
F_DIV           "#div"
F_MOD           "#mod"

/* Comparisons */
EQ              "#eq"
NEQ             "#neq"
GT              "#gt"
LT              "#lt"
GEQ             "#geq"
LEQ             "#leq"

/* Constants */
TRUE            "@True"
FALSE           "@False"
STRING          \".*\"

/* Logical operators */
AND             "#and"
OR              "#or"

/* Control flow */
CHECK_COND      "|"

WHEN            "when"
WHENNT          "whenn't"

/* Loops */
WHILE           "while"
WHILENT         "whilen't"

/* Operators */
OP_ASSIGN       "$="

/* Comments */
LINE_COMMENT    "//".*
MULTI_COMMENT_S "/*"

/* Higher level definitions */
VARIABLE        [a-zA-Z][a-zA-Z0-9]*
BOOL_VAR        @{VARIABLE}
INTEGER         [\-]?{NON_ZERO_DIGIT}{DIGIT}*|0
REAL            [\-]?{INTEGER}\.{DIGIT}+

%x MULTILINE_COMMENT

%%

<MULTILINE_COMMENT>.|\n { updatePos(); }
<MULTILINE_COMMENT>"*/" { BEGIN(0); updatePos(); }

{T_BOOL} { processToken("T_BOOL"); return T_BOOL; }
{T_INTEGER} { processToken("T_INTEGER"); return T_INTEGER; }
{T_REAL} { processToken("T_REAL"); return T_REAL; }

{INTEGER} { 
    processToken("CNST_INTEGER"); 
    yylval.integer_value = atoi(yytext);
    return CNST_INTEGER;
}
{REAL} { 
    processToken("CNST_REAL");
    yylval.real_value = atof(yytext);
    return CNST_REAL;
}
{TRUE} { 
    processToken("CNST_TRUE"); 
    yylval.boolean_value = true;
    return CNST_TRUE;
}
{FALSE} { 
    processToken("CNST_FALSE");
    yylval.boolean_value = false;
    return CNST_FALSE;
}
{STRING} { 
    processToken("CNST_STRING");
    yylval.string_value = strdup(yytext);
    return CNST_STRING;
}

{OP_ASSIGN} { processToken("OP_ASSIGN"); return OP_ASSIGN; }

{EQ} { processToken("OP_EQ"); return OP_EQ; }
{NEQ} { processToken("OP_NEQ"); return OP_NEQ; }
{GT} { processToken("OP_GT"); return OP_GT; }
{LT} { processToken("OP_LT"); return OP_LT; }
{GEQ} { processToken("OP_GEQ"); return OP_GEQ; }
{LEQ} { processToken("OP_LEQ"); return OP_LEQ; }
{AND} { processToken("OP_AND"); return OP_AND; }
{OR} { processToken("OP_OR"); return OP_OR; }

{F_ADD} { processToken("+"); return '+'; }
{F_SUB} { processToken("-"); return '-'; }
{F_MUL} { processToken("*"); return '*'; }
{F_DIV} { processToken("/"); return '/'; }
{F_MOD} { processToken("%"); return '%'; }

{IN} { processToken("INPUT"); return INPUT; }
{OUT} { processToken("OUTPUT"); return OUTPUT; }
{PRINT_ERR} { processToken("OUTPUT_ERR"); return OUTPUT_ERR; }
{EXIT} { processToken("EXIT"); return EXIT; }

";" { processToken(";"); return ';'; }
"(" { processToken("("); return '('; }
")" { processToken(")"); return ')'; }
"#as" { processToken("#as"); return OP_AS; }

{CHECK_COND} { processToken("|"); return '|'; }
"->" { processToken("DO_THIS"); return DO_THIS; }

{WHEN} { processToken("IF"); return IF; }
{WHENNT} { processToken("ENDIF"); return ENDIF; }

{WHILE} { processToken("WHILE"); return WHILE; }
{WHILENT} { processToken("WHILENT"); return WHILENT; }

{VARIABLE} { 
    processToken("VAR");
    yylval.string_value = strdup(yytext);
    return VAR;
}
{BOOL_VAR} {
    processToken("BOOL_VAR");
    yylval.string_value = strdup(yytext);
    return BOOL_VAR;
}

{LINE_COMMENT} { updatePos(); }
{MULTI_COMMENT_S} { BEGIN(MULTILINE_COMMENT); updatePos(); }
{SPACE}|{TAB} { updatePos(); }
 
. { 
    cout << ">> Lexical error | [row=" << parsePosition.row << ", column=" << parsePosition.column << "]: Token: '" << yytext << "'" << endl;
}

\n { updatePos(); }

%%
