/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "akos.y"

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


#line 112 "akos.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "akos.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_INTEGER = 4,                    /* INTEGER  */
  YYSYMBOL_DOUBLE = 5,                     /* DOUBLE  */
  YYSYMBOL_TRUE = 6,                       /* TRUE  */
  YYSYMBOL_FALSE = 7,                      /* FALSE  */
  YYSYMBOL_TYPE_INT = 8,                   /* TYPE_INT  */
  YYSYMBOL_TYPE_DOUBLE = 9,                /* TYPE_DOUBLE  */
  YYSYMBOL_TYPE_BOOL = 10,                 /* TYPE_BOOL  */
  YYSYMBOL_ASSIGNMENT_OP = 11,             /* ASSIGNMENT_OP  */
  YYSYMBOL_REL_AND = 12,                   /* REL_AND  */
  YYSYMBOL_REL_OR = 13,                    /* REL_OR  */
  YYSYMBOL_REL_NOT = 14,                   /* REL_NOT  */
  YYSYMBOL_REL_NOTEQ = 15,                 /* REL_NOTEQ  */
  YYSYMBOL_REL_EQ = 16,                    /* REL_EQ  */
  YYSYMBOL_REL_LT = 17,                    /* REL_LT  */
  YYSYMBOL_REL_GT = 18,                    /* REL_GT  */
  YYSYMBOL_REL_LTE = 19,                   /* REL_LTE  */
  YYSYMBOL_REL_GTE = 20,                   /* REL_GTE  */
  YYSYMBOL_KEY_WHILE = 21,                 /* KEY_WHILE  */
  YYSYMBOL_KEY_IF = 22,                    /* KEY_IF  */
  YYSYMBOL_KEY_ELSE = 23,                  /* KEY_ELSE  */
  YYSYMBOL_OP_SUB = 24,                    /* OP_SUB  */
  YYSYMBOL_OP_ADD = 25,                    /* OP_ADD  */
  YYSYMBOL_OP_MUL = 26,                    /* OP_MUL  */
  YYSYMBOL_OP_DIV = 27,                    /* OP_DIV  */
  YYSYMBOL_OP_MOD = 28,                    /* OP_MOD  */
  YYSYMBOL_IO_READ = 29,                   /* IO_READ  */
  YYSYMBOL_IO_WRITE = 30,                  /* IO_WRITE  */
  YYSYMBOL_OPEN_BRACE = 31,                /* OPEN_BRACE  */
  YYSYMBOL_CLOSE_BRACE = 32,               /* CLOSE_BRACE  */
  YYSYMBOL_OPEN_PAREN = 33,                /* OPEN_PAREN  */
  YYSYMBOL_CLOSE_PAREN = 34,               /* CLOSE_PAREN  */
  YYSYMBOL_SEMICOLON = 35,                 /* SEMICOLON  */
  YYSYMBOL_YYACCEPT = 36,                  /* $accept  */
  YYSYMBOL_program = 37,                   /* program  */
  YYSYMBOL_input = 38,                     /* input  */
  YYSYMBOL_var_declaration = 39,           /* var_declaration  */
  YYSYMBOL_40_1 = 40,                      /* $@1  */
  YYSYMBOL_41_2 = 41,                      /* $@2  */
  YYSYMBOL_42_3 = 42,                      /* $@3  */
  YYSYMBOL_var_assignment = 43,            /* var_assignment  */
  YYSYMBOL_44_4 = 44,                      /* $@4  */
  YYSYMBOL_expression = 45,                /* expression  */
  YYSYMBOL_46_5 = 46,                      /* $@5  */
  YYSYMBOL_47_6 = 47,                      /* $@6  */
  YYSYMBOL_48_7 = 48,                      /* $@7  */
  YYSYMBOL_49_8 = 49,                      /* $@8  */
  YYSYMBOL_50_9 = 50,                      /* $@9  */
  YYSYMBOL_51_10 = 51,                     /* $@10  */
  YYSYMBOL_52_11 = 52,                     /* $@11  */
  YYSYMBOL_53_12 = 53,                     /* $@12  */
  YYSYMBOL_logical_expression = 54,        /* logical_expression  */
  YYSYMBOL_55_13 = 55,                     /* $@13  */
  YYSYMBOL_56_14 = 56,                     /* $@14  */
  YYSYMBOL_57_15 = 57,                     /* $@15  */
  YYSYMBOL_relational_expression = 58,     /* relational_expression  */
  YYSYMBOL_relation = 59,                  /* relation  */
  YYSYMBOL_value = 60,                     /* value  */
  YYSYMBOL_if_statement = 61,              /* if_statement  */
  YYSYMBOL_62_16 = 62,                     /* $@16  */
  YYSYMBOL_63_17 = 63,                     /* $@17  */
  YYSYMBOL_64_18 = 64,                     /* $@18  */
  YYSYMBOL_65_19 = 65,                     /* $@19  */
  YYSYMBOL_66_20 = 66,                     /* $@20  */
  YYSYMBOL_while_statement = 67,           /* while_statement  */
  YYSYMBOL_68_21 = 68,                     /* $@21  */
  YYSYMBOL_69_22 = 69,                     /* $@22  */
  YYSYMBOL_read_value = 70,                /* read_value  */
  YYSYMBOL_write_value = 71,               /* write_value  */
  YYSYMBOL_72_23 = 72                      /* $@23  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   285

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  36
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  37
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  142

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   290


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    79,    79,    80,    84,    85,    86,    87,    88,    89,
      90,    91,    95,    96,    97,    98,    98,    99,    99,   100,
     100,   104,   104,   108,   109,   109,   110,   110,   111,   111,
     112,   112,   113,   113,   114,   114,   115,   115,   116,   116,
     121,   122,   123,   123,   124,   124,   125,   125,   129,   133,
     134,   135,   136,   137,   138,   141,   142,   143,   144,   145,
     149,   149,   149,   150,   150,   150,   150,   151,   152,   156,
     156,   156,   160,   164,   164
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER",
  "INTEGER", "DOUBLE", "TRUE", "FALSE", "TYPE_INT", "TYPE_DOUBLE",
  "TYPE_BOOL", "ASSIGNMENT_OP", "REL_AND", "REL_OR", "REL_NOT",
  "REL_NOTEQ", "REL_EQ", "REL_LT", "REL_GT", "REL_LTE", "REL_GTE",
  "KEY_WHILE", "KEY_IF", "KEY_ELSE", "OP_SUB", "OP_ADD", "OP_MUL",
  "OP_DIV", "OP_MOD", "IO_READ", "IO_WRITE", "OPEN_BRACE", "CLOSE_BRACE",
  "OPEN_PAREN", "CLOSE_PAREN", "SEMICOLON", "$accept", "program", "input",
  "var_declaration", "$@1", "$@2", "$@3", "var_assignment", "$@4",
  "expression", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "logical_expression", "$@13", "$@14", "$@15", "relational_expression",
  "relation", "value", "if_statement", "$@16", "$@17", "$@18", "$@19",
  "$@20", "while_statement", "$@21", "$@22", "read_value", "write_value",
  "$@23", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-87)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-61)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -87,    72,   -87,   -26,     0,    12,    19,    28,    16,    22,
      26,    27,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,    -3,    -1,     5,   -87,   205,    58,   -87,    23,
     -87,   -87,   -87,   -87,   -87,   -87,   210,    29,   210,   210,
      30,    23,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
      17,   -87,    23,    23,    23,    32,   229,    40,     1,    31,
      42,    45,    49,   171,    23,    23,    23,   -87,   -87,   -87,
     -87,   -87,   -87,    71,   234,   239,   -87,   -87,   -87,   -87,
     -87,   -87,   -87,    23,    55,   -87,   -87,   -87,    56,    57,
     -87,    54,    24,    24,   251,    23,    23,    23,    23,    23,
     -87,   -87,   -87,   210,    -7,   -87,    23,    23,    82,   -87,
     -87,   -87,   -87,    24,    24,   -87,   -87,   -22,    66,   -87,
     229,   -87,   -87,    85,   -87,   -87,   -87,   112,    74,   127,
     142,   -87,   -87,   -87,    86,   157,    79,   -87,   -87,   -87,
     172,   -87
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       2,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     4,     3,     5,     6,     7,     8,     9,    10,
      11,    21,     0,     0,     0,    69,     0,     0,    73,     0,
      15,    12,    17,    13,    19,    14,     0,     0,     0,     0,
       0,     0,    59,    55,    58,    56,    57,    26,    24,    38,
       0,    23,     0,     0,     0,     0,    40,     0,    41,     0,
       0,     0,     0,     0,     0,     0,     0,    30,    28,    32,
      34,    36,    22,     0,     0,     0,    46,    50,    49,    52,
      51,    54,    53,     0,     0,    42,    44,     2,     0,     0,
      72,     0,    27,    25,     0,     0,     0,     0,     0,     0,
      16,    18,    20,     0,    48,    70,     0,     0,     0,    61,
      64,    74,    39,    31,    29,    33,    35,    37,     0,     2,
       0,    43,    45,    67,     2,     2,    47,     0,     0,     0,
       0,    71,     2,    62,     0,     0,     0,    68,    65,     2,
       0,    66
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -87,   -86,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -29,
     -87,   -87,   -87,   -87,   -87,   -87,   -87,   -87,   -32,   -87,
     -87,   -87,   -49,   -87,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,   -87,   -87,   -87,   -87,   -87,   -87
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    13,    14,    52,    53,    54,    15,    29,    56,
      65,    64,    96,    95,    97,    98,    99,    66,    57,   106,
     107,   103,    58,    83,    51,    16,    38,   124,    39,   125,
     139,    17,    36,   119,    18,    19,    41
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      50,   108,    67,    68,    69,    70,    60,    61,    30,    20,
      32,    21,    63,    85,    86,    22,    34,    67,    68,    69,
      70,    71,    23,    73,    74,    75,    42,    43,    44,    45,
      46,    24,    31,   127,    33,    92,    93,    94,   129,   130,
      35,    67,    68,    69,    70,    71,   135,    47,    48,    25,
      69,    70,    72,   140,   104,    26,    49,   121,   122,    27,
      28,    40,    87,    59,    62,    76,   113,   114,   115,   116,
     117,   118,     2,     3,    84,     4,    88,   120,   120,    89,
       5,     6,     7,     3,    90,     4,   105,   109,   110,   111,
       5,     6,     7,     8,     9,    67,    68,    69,    70,    71,
     126,    10,    11,     8,     9,   132,   100,    12,   128,   136,
     138,    10,    11,     3,   123,     4,     0,    12,     0,     0,
       5,     6,     7,     0,     0,     0,     0,     0,     3,     0,
       4,     0,     0,     8,     9,     5,     6,     7,     0,     0,
       0,    10,    11,     3,   131,     4,     0,    12,     8,     9,
       5,     6,     7,     0,     0,     0,    10,    11,     3,   133,
       4,     0,    12,     8,     9,     5,     6,     7,     0,     0,
       0,    10,    11,     3,   134,     4,     0,    12,     8,     9,
       5,     6,     7,     0,     0,     0,    10,    11,     0,   137,
       0,     0,    12,     8,     9,    67,    68,    69,    70,    71,
       0,    10,    11,     0,   141,    91,    37,    12,   -60,   -60,
     -60,   -60,   -60,    42,    43,    44,    45,    46,     0,   -60,
       0,     0,     0,     0,    55,     0,     0,     0,     0,   -60,
     -60,     0,     0,     0,    47,    48,     0,     0,   -60,     0,
       0,     0,     0,    49,    77,    78,    79,    80,    81,    82,
       0,     0,     0,    67,    68,    69,    70,    71,    67,    68,
      69,    70,    71,    67,    68,    69,    70,    71,     0,   101,
       0,     0,     0,     0,   102,    67,    68,    69,    70,    71,
       0,     0,     0,     0,     0,   112
};

static const yytype_int16 yycheck[] =
{
      29,    87,    24,    25,    26,    27,    38,    39,    11,    35,
      11,    11,    41,    12,    13,     3,    11,    24,    25,    26,
      27,    28,     3,    52,    53,    54,     3,     4,     5,     6,
       7,     3,    35,   119,    35,    64,    65,    66,   124,   125,
      35,    24,    25,    26,    27,    28,   132,    24,    25,    33,
      26,    27,    35,   139,    83,    33,    33,   106,   107,    33,
      33,     3,    31,    34,    34,    33,    95,    96,    97,    98,
      99,   103,     0,     1,    34,     3,    34,   106,   107,    34,
       8,     9,    10,     1,    35,     3,    31,    31,    31,    35,
       8,     9,    10,    21,    22,    24,    25,    26,    27,    28,
      34,    29,    30,    21,    22,    31,    35,    35,    23,    23,
      31,    29,    30,     1,    32,     3,    -1,    35,    -1,    -1,
       8,     9,    10,    -1,    -1,    -1,    -1,    -1,     1,    -1,
       3,    -1,    -1,    21,    22,     8,     9,    10,    -1,    -1,
      -1,    29,    30,     1,    32,     3,    -1,    35,    21,    22,
       8,     9,    10,    -1,    -1,    -1,    29,    30,     1,    32,
       3,    -1,    35,    21,    22,     8,     9,    10,    -1,    -1,
      -1,    29,    30,     1,    32,     3,    -1,    35,    21,    22,
       8,     9,    10,    -1,    -1,    -1,    29,    30,    -1,    32,
      -1,    -1,    35,    21,    22,    24,    25,    26,    27,    28,
      -1,    29,    30,    -1,    32,    34,     1,    35,     3,     4,
       5,     6,     7,     3,     4,     5,     6,     7,    -1,    14,
      -1,    -1,    -1,    -1,    14,    -1,    -1,    -1,    -1,    24,
      25,    -1,    -1,    -1,    24,    25,    -1,    -1,    33,    -1,
      -1,    -1,    -1,    33,    15,    16,    17,    18,    19,    20,
      -1,    -1,    -1,    24,    25,    26,    27,    28,    24,    25,
      26,    27,    28,    24,    25,    26,    27,    28,    -1,    35,
      -1,    -1,    -1,    -1,    35,    24,    25,    26,    27,    28,
      -1,    -1,    -1,    -1,    -1,    34
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    37,     0,     1,     3,     8,     9,    10,    21,    22,
      29,    30,    35,    38,    39,    43,    61,    67,    70,    71,
      35,    11,     3,     3,     3,    33,    33,    33,    33,    44,
      11,    35,    11,    35,    11,    35,    68,     1,    62,    64,
       3,    72,     3,     4,     5,     6,     7,    24,    25,    33,
      45,    60,    40,    41,    42,    14,    45,    54,    58,    34,
      54,    54,    34,    45,    47,    46,    53,    24,    25,    26,
      27,    28,    35,    45,    45,    45,    33,    15,    16,    17,
      18,    19,    20,    59,    34,    12,    13,    31,    34,    34,
      35,    34,    45,    45,    45,    49,    48,    50,    51,    52,
      35,    35,    35,    57,    45,    31,    55,    56,    37,    31,
      31,    35,    34,    45,    45,    45,    45,    45,    54,    69,
      45,    58,    58,    32,    63,    65,    34,    37,    23,    37,
      37,    32,    31,    32,    32,    37,    23,    32,    31,    66,
      37,    32
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    36,    37,    37,    38,    38,    38,    38,    38,    38,
      38,    38,    39,    39,    39,    40,    39,    41,    39,    42,
      39,    44,    43,    45,    46,    45,    47,    45,    48,    45,
      49,    45,    50,    45,    51,    45,    52,    45,    53,    45,
      54,    54,    55,    54,    56,    54,    57,    54,    58,    59,
      59,    59,    59,    59,    59,    60,    60,    60,    60,    60,
      62,    63,    61,    64,    65,    66,    61,    61,    61,    68,
      69,    67,    70,    72,    71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     0,     2,     1,     1,     1,     1,     1,     1,
       1,     2,     3,     3,     3,     0,     6,     0,     6,     0,
       6,     0,     5,     1,     0,     3,     0,     3,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       1,     1,     0,     4,     0,     4,     0,     5,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     0,     9,     0,     0,     0,    14,     7,    11,     0,
       0,     9,     5,     0,     6
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 4: /* input: SEMICOLON  */
#line 84 "akos.y"
                { out << ";\n"; }
#line 1567 "akos.tab.c"
    break;

  case 12: /* var_declaration: TYPE_INT IDENTIFIER SEMICOLON  */
#line 95 "akos.y"
                                    { declare((yyvsp[-1].variable_name), 1); out << indent() << "int " << (yyvsp[-1].variable_name) << ";\n"; }
#line 1573 "akos.tab.c"
    break;

  case 13: /* var_declaration: TYPE_DOUBLE IDENTIFIER SEMICOLON  */
#line 96 "akos.y"
                                       { declare((yyvsp[-1].variable_name), 2); out << indent() << "double " << (yyvsp[-1].variable_name) << ";\n"; }
#line 1579 "akos.tab.c"
    break;

  case 14: /* var_declaration: TYPE_BOOL IDENTIFIER SEMICOLON  */
#line 97 "akos.y"
                                     { declare((yyvsp[-1].variable_name), 0); out << indent() << "bool " << (yyvsp[-1].variable_name) << ";\n"; }
#line 1585 "akos.tab.c"
    break;

  case 15: /* $@1: %empty  */
#line 98 "akos.y"
                                        { out << indent() << "int " << (yyvsp[-1].variable_name) << "="; }
#line 1591 "akos.tab.c"
    break;

  case 16: /* var_declaration: TYPE_INT IDENTIFIER ASSIGNMENT_OP $@1 expression SEMICOLON  */
#line 98 "akos.y"
                                                                                                                        { declare((yyvsp[-4].variable_name), 1); checkAssignmentType(1, (yyvsp[-1].type)); out << ";\n";}
#line 1597 "akos.tab.c"
    break;

  case 17: /* $@2: %empty  */
#line 99 "akos.y"
                                           { out << indent() << "double " << (yyvsp[-1].variable_name) << "="; }
#line 1603 "akos.tab.c"
    break;

  case 18: /* var_declaration: TYPE_DOUBLE IDENTIFIER ASSIGNMENT_OP $@2 expression SEMICOLON  */
#line 99 "akos.y"
                                                                                                                              { declare((yyvsp[-4].variable_name), 2); checkAssignmentType(2, (yyvsp[-1].type)); out << ";\n"; }
#line 1609 "akos.tab.c"
    break;

  case 19: /* $@3: %empty  */
#line 100 "akos.y"
                                         { out << indent() << "bool " << (yyvsp[-1].variable_name) << "="; }
#line 1615 "akos.tab.c"
    break;

  case 20: /* var_declaration: TYPE_BOOL IDENTIFIER ASSIGNMENT_OP $@3 expression SEMICOLON  */
#line 100 "akos.y"
                                                                                                                          { declare((yyvsp[-4].variable_name), 0); checkAssignmentType(0, (yyvsp[-1].type)); out << ";\n"; }
#line 1621 "akos.tab.c"
    break;

  case 21: /* $@4: %empty  */
#line 104 "akos.y"
                             { out << indent() << (yyvsp[-1].variable_name) << "="; }
#line 1627 "akos.tab.c"
    break;

  case 22: /* var_assignment: IDENTIFIER ASSIGNMENT_OP $@4 expression SEMICOLON  */
#line 104 "akos.y"
                                                                                                   { if(checkDeclared((yyvsp[-4].variable_name)) == true) { checkAssignmentType(getType((yyvsp[-4].variable_name)), (yyvsp[-1].type)); } out << ";\n"; }
#line 1633 "akos.tab.c"
    break;

  case 23: /* expression: value  */
#line 108 "akos.y"
            { (yyval.type) = (yyvsp[0].type); }
#line 1639 "akos.tab.c"
    break;

  case 24: /* $@5: %empty  */
#line 109 "akos.y"
             { out << "+"; }
#line 1645 "akos.tab.c"
    break;

  case 25: /* expression: OP_ADD $@5 expression  */
#line 109 "akos.y"
                                        { (yyval.type) = (yyvsp[0].type); }
#line 1651 "akos.tab.c"
    break;

  case 26: /* $@6: %empty  */
#line 110 "akos.y"
             { out << "-"; }
#line 1657 "akos.tab.c"
    break;

  case 27: /* expression: OP_SUB $@6 expression  */
#line 110 "akos.y"
                                        { (yyval.type) = (yyvsp[0].type); }
#line 1663 "akos.tab.c"
    break;

  case 28: /* $@7: %empty  */
#line 111 "akos.y"
                        { out << "+"; }
#line 1669 "akos.tab.c"
    break;

  case 29: /* expression: expression OP_ADD $@7 expression  */
#line 111 "akos.y"
                                                   { (yyval.type) = commonType((yyvsp[-3].type), (yyvsp[0].type)); }
#line 1675 "akos.tab.c"
    break;

  case 30: /* $@8: %empty  */
#line 112 "akos.y"
                        { out << "-"; }
#line 1681 "akos.tab.c"
    break;

  case 31: /* expression: expression OP_SUB $@8 expression  */
#line 112 "akos.y"
                                                   { (yyval.type) = commonType((yyvsp[-3].type), (yyvsp[0].type)); }
#line 1687 "akos.tab.c"
    break;

  case 32: /* $@9: %empty  */
#line 113 "akos.y"
                        { out << "*"; }
#line 1693 "akos.tab.c"
    break;

  case 33: /* expression: expression OP_MUL $@9 expression  */
#line 113 "akos.y"
                                                   { (yyval.type) = commonType((yyvsp[-3].type), (yyvsp[0].type)); }
#line 1699 "akos.tab.c"
    break;

  case 34: /* $@10: %empty  */
#line 114 "akos.y"
                        { out << "/"; }
#line 1705 "akos.tab.c"
    break;

  case 35: /* expression: expression OP_DIV $@10 expression  */
#line 114 "akos.y"
                                                   { (yyval.type) = commonType((yyvsp[-3].type), (yyvsp[0].type)); }
#line 1711 "akos.tab.c"
    break;

  case 36: /* $@11: %empty  */
#line 115 "akos.y"
                        { out << "%"; }
#line 1717 "akos.tab.c"
    break;

  case 37: /* expression: expression OP_MOD $@11 expression  */
#line 115 "akos.y"
                                                   { (yyval.type) = commonType((yyvsp[-3].type), (yyvsp[0].type)); }
#line 1723 "akos.tab.c"
    break;

  case 38: /* $@12: %empty  */
#line 116 "akos.y"
                 { out << "("; }
#line 1729 "akos.tab.c"
    break;

  case 39: /* expression: OPEN_PAREN $@12 expression CLOSE_PAREN  */
#line 116 "akos.y"
                                                        { (yyval.type) = (yyvsp[-1].type); out << ")"; }
#line 1735 "akos.tab.c"
    break;

  case 40: /* logical_expression: expression  */
#line 121 "akos.y"
                 { (yyval.type) = (yyvsp[0].type); }
#line 1741 "akos.tab.c"
    break;

  case 41: /* logical_expression: relational_expression  */
#line 122 "akos.y"
                            { (yyval.type) = (yyvsp[0].type); }
#line 1747 "akos.tab.c"
    break;

  case 42: /* $@13: %empty  */
#line 123 "akos.y"
                                    { out << "&&"; }
#line 1753 "akos.tab.c"
    break;

  case 43: /* logical_expression: relational_expression REL_AND $@13 relational_expression  */
#line 123 "akos.y"
                                                                           { (yyval.type) = commonType((yyvsp[-3].type), (yyvsp[0].type)); }
#line 1759 "akos.tab.c"
    break;

  case 44: /* $@14: %empty  */
#line 124 "akos.y"
                                   { out << "||"; }
#line 1765 "akos.tab.c"
    break;

  case 45: /* logical_expression: relational_expression REL_OR $@14 relational_expression  */
#line 124 "akos.y"
                                                                          { (yyval.type) = commonType((yyvsp[-3].type), (yyvsp[0].type)); }
#line 1771 "akos.tab.c"
    break;

  case 46: /* $@15: %empty  */
#line 125 "akos.y"
                         { out << "!("; }
#line 1777 "akos.tab.c"
    break;

  case 47: /* logical_expression: REL_NOT OPEN_PAREN $@15 logical_expression CLOSE_PAREN  */
#line 125 "akos.y"
                                                                         { (yyval.type) = (yyvsp[-1].type); out << ")"; }
#line 1783 "akos.tab.c"
    break;

  case 48: /* relational_expression: expression relation expression  */
#line 129 "akos.y"
                                   { (yyval.type) = 0; }
#line 1789 "akos.tab.c"
    break;

  case 49: /* relation: REL_EQ  */
#line 133 "akos.y"
             { out << "=="; }
#line 1795 "akos.tab.c"
    break;

  case 50: /* relation: REL_NOTEQ  */
#line 134 "akos.y"
                { out << "!="; }
#line 1801 "akos.tab.c"
    break;

  case 51: /* relation: REL_GT  */
#line 135 "akos.y"
             { out << ">"; }
#line 1807 "akos.tab.c"
    break;

  case 52: /* relation: REL_LT  */
#line 136 "akos.y"
             { out << "<"; }
#line 1813 "akos.tab.c"
    break;

  case 53: /* relation: REL_GTE  */
#line 137 "akos.y"
              { out << ">="; }
#line 1819 "akos.tab.c"
    break;

  case 54: /* relation: REL_LTE  */
#line 138 "akos.y"
              { out << "<="; }
#line 1825 "akos.tab.c"
    break;

  case 55: /* value: INTEGER  */
#line 141 "akos.y"
              { (yyval.type) = 1; out << (yyvsp[0].integer_value); }
#line 1831 "akos.tab.c"
    break;

  case 56: /* value: TRUE  */
#line 142 "akos.y"
           { (yyval.type) = 0; out << "true"; }
#line 1837 "akos.tab.c"
    break;

  case 57: /* value: FALSE  */
#line 143 "akos.y"
            { (yyval.type) = 0; out << "false"; }
#line 1843 "akos.tab.c"
    break;

  case 58: /* value: DOUBLE  */
#line 144 "akos.y"
             { (yyval.type) = 2; out << (yyvsp[0].double_value); }
#line 1849 "akos.tab.c"
    break;

  case 59: /* value: IDENTIFIER  */
#line 145 "akos.y"
                 { checkDeclared((yyvsp[0].variable_name)); (yyval.type) = getType((yyvsp[0].variable_name)); out << (yyvsp[0].variable_name); }
#line 1855 "akos.tab.c"
    break;

  case 60: /* $@16: %empty  */
#line 149 "akos.y"
                        { out << indent() << "if("; }
#line 1861 "akos.tab.c"
    break;

  case 61: /* $@17: %empty  */
#line 149 "akos.y"
                                                                                                { out << ") {\n"; depth++; }
#line 1867 "akos.tab.c"
    break;

  case 62: /* if_statement: KEY_IF OPEN_PAREN $@16 logical_expression CLOSE_PAREN OPEN_BRACE $@17 program CLOSE_BRACE  */
#line 149 "akos.y"
                                                                                                                                                 { checkAssignmentType(0, (yyvsp[-5].type)); depth--; out << indent() << "}\n"; }
#line 1873 "akos.tab.c"
    break;

  case 63: /* $@18: %empty  */
#line 150 "akos.y"
                        { out << indent() << "if("; }
#line 1879 "akos.tab.c"
    break;

  case 64: /* $@19: %empty  */
#line 150 "akos.y"
                                                                                                { out << ") {\n"; depth++; }
#line 1885 "akos.tab.c"
    break;

  case 65: /* $@20: %empty  */
#line 150 "akos.y"
                                                                                                                                                                     { depth--; out<< indent() << "} else {\n"; depth++; }
#line 1891 "akos.tab.c"
    break;

  case 66: /* if_statement: KEY_IF OPEN_PAREN $@18 logical_expression CLOSE_PAREN OPEN_BRACE $@19 program CLOSE_BRACE KEY_ELSE OPEN_BRACE $@20 program CLOSE_BRACE  */
#line 150 "akos.y"
                                                                                                                                                                                                                                               { checkAssignmentType(0, (yyvsp[-10].type)); depth--; out << indent() << "}\n"; }
#line 1897 "akos.tab.c"
    break;

  case 69: /* $@21: %empty  */
#line 156 "akos.y"
                       { out << indent() << "while("; }
#line 1903 "akos.tab.c"
    break;

  case 70: /* $@22: %empty  */
#line 156 "akos.y"
                                                                                                  { out <<") {\n"; depth++; }
#line 1909 "akos.tab.c"
    break;

  case 71: /* while_statement: KEY_WHILE OPEN_PAREN $@21 logical_expression CLOSE_PAREN OPEN_BRACE $@22 program CLOSE_BRACE  */
#line 156 "akos.y"
                                                                                                                                                  { checkAssignmentType(0, (yyvsp[-5].type)); depth--; out << indent() << "}\n"; }
#line 1915 "akos.tab.c"
    break;

  case 72: /* read_value: IO_READ OPEN_PAREN IDENTIFIER CLOSE_PAREN SEMICOLON  */
#line 160 "akos.y"
                                                      { checkDeclared((yyvsp[-2].variable_name)); out << indent() << "cin >> " << (yyvsp[-2].variable_name) << ";\n"; }
#line 1921 "akos.tab.c"
    break;

  case 73: /* $@23: %empty  */
#line 164 "akos.y"
                      {out << indent() << "cout << "; }
#line 1927 "akos.tab.c"
    break;

  case 74: /* write_value: IO_WRITE OPEN_PAREN $@23 expression CLOSE_PAREN SEMICOLON  */
#line 164 "akos.y"
                                                                                         { out << " << endl;\n"; }
#line 1933 "akos.tab.c"
    break;


#line 1937 "akos.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 167 "akos.y"


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
