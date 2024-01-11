/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_AKOS_TAB_H_INCLUDED
# define YY_YY_AKOS_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    INTEGER = 259,                 /* INTEGER  */
    DOUBLE = 260,                  /* DOUBLE  */
    TRUE = 261,                    /* TRUE  */
    FALSE = 262,                   /* FALSE  */
    TYPE_INT = 263,                /* TYPE_INT  */
    TYPE_DOUBLE = 264,             /* TYPE_DOUBLE  */
    TYPE_BOOL = 265,               /* TYPE_BOOL  */
    ASSIGNMENT_OP = 266,           /* ASSIGNMENT_OP  */
    REL_AND = 267,                 /* REL_AND  */
    REL_OR = 268,                  /* REL_OR  */
    REL_NOT = 269,                 /* REL_NOT  */
    REL_NOTEQ = 270,               /* REL_NOTEQ  */
    REL_EQ = 271,                  /* REL_EQ  */
    REL_LT = 272,                  /* REL_LT  */
    REL_GT = 273,                  /* REL_GT  */
    REL_LTE = 274,                 /* REL_LTE  */
    REL_GTE = 275,                 /* REL_GTE  */
    KEY_WHILE = 276,               /* KEY_WHILE  */
    KEY_IF = 277,                  /* KEY_IF  */
    KEY_ELSE = 278,                /* KEY_ELSE  */
    OP_SUB = 279,                  /* OP_SUB  */
    OP_ADD = 280,                  /* OP_ADD  */
    OP_MUL = 281,                  /* OP_MUL  */
    OP_DIV = 282,                  /* OP_DIV  */
    OP_MOD = 283,                  /* OP_MOD  */
    IO_READ = 284,                 /* IO_READ  */
    IO_WRITE = 285,                /* IO_WRITE  */
    OPEN_BRACE = 286,              /* OPEN_BRACE  */
    CLOSE_BRACE = 287,             /* CLOSE_BRACE  */
    OPEN_PAREN = 288,              /* OPEN_PAREN  */
    CLOSE_PAREN = 289,             /* CLOSE_PAREN  */
    SEMICOLON = 290                /* SEMICOLON  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 38 "akos.y"

  int         type;
  int         integer_value;
  double      double_value;
  char*       variable_name;

#line 106 "akos.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_AKOS_TAB_H_INCLUDED  */
