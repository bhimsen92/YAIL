/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.5"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */

/* Line 268 of yacc.c  */
#line 1 "parser.yacc"

#include<iostream>
#include<cstdlib>
#include<stack>
#include "headers/bnKapi.h"
#include "headers/tokens.h"
#include "headers/node.h"
#include "headers/interpreter.h"
#include "headers/context.h"
#include "headers/object.h"
#include "headers/number.h"

#include<list>
using namespace std;
using namespace bnk_astNodes;

typedef int DataType;

extern int yylex();
extern void yyerror(const char*);
extern int yyparse();
void _debugMessage( const char* );
void putType( DataType type );
DataType getType(void);
void removeType(void);

StatementList *programAST;
stack<StatementList*> statementStack;
stack<DataType> typeStack;
StatementList *stmtList = NULL;
int counter = 0;



/* Line 268 of yacc.c  */
#line 106 "y.tab.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     FUNCTION = 258,
     INTEGER_T = 259,
     DOUBLE_T = 260,
     STRING_T = 261,
     FUNCTION_T = 262,
     BOOL_T = 263,
     OR = 264,
     AND = 265,
     EQUAL = 266,
     LE = 267,
     GE = 268,
     IF = 269,
     ELSE = 270,
     NOT = 271,
     ELIF = 272,
     RETURN = 273,
     ARRAY_T = 274,
     IDENTIFIER = 275,
     STRING = 276,
     INTEGER = 277,
     DOUBLE = 278,
     NOTHING = 279,
     EMPTY = 280
   };
#endif
/* Tokens.  */
#define FUNCTION 258
#define INTEGER_T 259
#define DOUBLE_T 260
#define STRING_T 261
#define FUNCTION_T 262
#define BOOL_T 263
#define OR 264
#define AND 265
#define EQUAL 266
#define LE 267
#define GE 268
#define IF 269
#define ELSE 270
#define NOT 271
#define ELIF 272
#define RETURN 273
#define ARRAY_T 274
#define IDENTIFIER 275
#define STRING 276
#define INTEGER 277
#define DOUBLE 278
#define NOTHING 279
#define EMPTY 280




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 293 of yacc.c  */
#line 35 "parser.yacc"

    bnk_astNodes::Node *node;



/* Line 293 of yacc.c  */
#line 198 "y.tab.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 343 of yacc.c  */
#line 210 "y.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   221

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  81
/* YYNRULES -- Number of states.  */
#define YYNSTATES  143

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   280

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      27,    28,    38,    36,    34,    37,     2,    39,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    33,    26,
      31,    35,    32,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    41,     2,    42,    40,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    29,     2,    30,     2,     2,     2,     2,
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
      25
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    10,    13,    15,    22,    26,
      29,    32,    39,    41,    45,    47,    49,    53,    55,    59,
      61,    65,    69,    73,    77,    81,    83,    92,    94,    98,
     100,   102,   104,   108,   111,   112,   116,   118,   122,   126,
     130,   134,   136,   140,   144,   146,   150,   152,   155,   158,
     160,   162,   164,   166,   168,   170,   172,   174,   176,   178,
     180,   184,   185,   187,   189,   191,   193,   195,   197,   201,
     206,   208,   210,   212,   216,   220,   222,   224,   228,   233,
     240,   242
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      44,     0,    -1,    45,    -1,    69,    -1,    45,    46,    -1,
      60,    26,    -1,    54,    -1,    14,    27,    49,    28,    48,
      47,    -1,    18,    49,    26,    -1,    49,    26,    -1,    15,
      48,    -1,    17,    27,    49,    28,    48,    47,    -1,    46,
      -1,    29,    45,    30,    -1,    50,    -1,    51,    -1,    50,
       9,    51,    -1,    52,    -1,    51,    10,    52,    -1,    53,
      -1,    52,    11,    53,    -1,    64,    31,    64,    -1,    64,
      12,    64,    -1,    64,    32,    64,    -1,    64,    13,    64,
      -1,    64,    -1,     3,    20,    27,    57,    28,    33,    55,
      56,    -1,    70,    -1,    29,    45,    30,    -1,    69,    -1,
      58,    -1,    59,    -1,    58,    34,    59,    -1,    70,    20,
      -1,    -1,    70,    61,    62,    -1,    63,    -1,    62,    34,
      63,    -1,    20,    35,    64,    -1,    64,    36,    65,    -1,
      64,    37,    65,    -1,    65,    -1,    65,    38,    66,    -1,
      65,    39,    66,    -1,    66,    -1,    66,    40,    67,    -1,
      67,    -1,    16,    67,    -1,    37,    67,    -1,    68,    -1,
      20,    -1,    22,    -1,    23,    -1,    21,    -1,    24,    -1,
      25,    -1,    71,    -1,    74,    -1,    76,    -1,    77,    -1,
      27,    49,    28,    -1,    -1,     4,    -1,     5,    -1,     6,
      -1,     7,    -1,    24,    -1,     8,    -1,     4,    41,    42,
      -1,    20,    27,    72,    28,    -1,    69,    -1,    73,    -1,
      64,    -1,    73,    34,    64,    -1,    41,    75,    42,    -1,
      69,    -1,    64,    -1,    75,    34,    64,    -1,    20,    41,
      64,    42,    -1,    20,    41,    78,    33,    78,    42,    -1,
      69,    -1,    64,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    53,    53,    60,    65,    74,    79,    82,    93,   100,
     103,   109,   118,   119,   122,   125,   126,   135,   136,   145,
     146,   155,   162,   169,   176,   183,   187,   198,   201,   203,
     204,   207,   212,   221,   227,   227,   237,   243,   252,   262,
     269,   276,   279,   286,   293,   296,   303,   306,   312,   318,
     321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
     331,   333,   336,   337,   338,   339,   340,   341,   342,   345,
     356,   360,   363,   371,   379,   382,   386,   391,   399,   408,
     418,   419
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "FUNCTION", "INTEGER_T", "DOUBLE_T",
  "STRING_T", "FUNCTION_T", "BOOL_T", "OR", "AND", "EQUAL", "LE", "GE",
  "IF", "ELSE", "NOT", "ELIF", "RETURN", "ARRAY_T", "IDENTIFIER", "STRING",
  "INTEGER", "DOUBLE", "NOTHING", "EMPTY", "';'", "'('", "')'", "'{'",
  "'}'", "'<'", "'>'", "':'", "','", "'='", "'+'", "'-'", "'*'", "'/'",
  "'^'", "'['", "']'", "$accept", "program", "statementList", "statement",
  "elseBlock", "block", "conditionalExpression", "orExp", "andExp",
  "equality", "relationalOp", "functionDefinition", "returnType",
  "functionBody", "formalParameters", "formalParameterList",
  "formalParameterDef", "variableDefinition", "$@1", "variableList",
  "variableDeclarations", "expression", "term", "power", "unary", "atom",
  "empty", "type", "functCall", "arguments", "arglist", "list",
  "valueList", "indexOp", "slice", "sliceExp", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,    59,    40,    41,   123,
     125,    60,    62,    58,    44,    61,    43,    45,    42,    47,
      94,    91,    93
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    46,    46,    46,    46,
      47,    47,    48,    48,    49,    50,    50,    51,    51,    52,
      52,    53,    53,    53,    53,    53,    54,    55,    56,    57,
      57,    58,    58,    59,    61,    60,    62,    62,    63,    64,
      64,    64,    65,    65,    65,    66,    66,    67,    67,    67,
      68,    68,    68,    68,    68,    68,    68,    68,    68,    68,
      68,    69,    70,    70,    70,    70,    70,    70,    70,    71,
      72,    72,    73,    73,    74,    75,    75,    75,    76,    77,
      78,    78
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     2,     1,     6,     3,     2,
       2,     6,     1,     3,     1,     1,     3,     1,     3,     1,
       3,     3,     3,     3,     3,     1,     8,     1,     3,     1,
       1,     1,     3,     2,     0,     3,     1,     3,     3,     3,
       3,     1,     3,     3,     1,     3,     1,     2,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     1,     1,     1,     1,     1,     1,     3,     4,
       1,     1,     1,     3,     3,     1,     1,     3,     4,     6,
       1,     1
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      61,     0,     2,     3,     1,     0,    62,    63,    64,    65,
      67,     0,     0,     0,    50,    53,    51,    52,    54,    55,
       0,     0,    61,     4,     0,    14,    15,    17,    19,     6,
       0,    25,    41,    44,    46,    49,    34,    56,    57,    58,
      59,     0,     0,     0,    54,    47,     0,    61,    61,     0,
      48,    76,    75,     0,     9,     0,     0,     0,     5,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    61,
      68,     0,     8,    72,    70,     0,    71,    81,    80,     0,
      60,     0,    74,    16,    18,    20,    22,    24,    21,    23,
      39,    40,    42,    43,    45,     0,    35,    36,    66,     0,
      30,    31,    29,     0,     0,    69,     0,    78,    61,    77,
       0,     0,     0,     0,    33,    61,    12,     0,    73,    81,
       0,    38,    37,     0,    32,     0,     0,     0,     7,    79,
       0,    27,    13,    10,     0,    61,    26,     0,     0,     0,
      28,     0,    11
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     1,     2,    23,   128,   117,    24,    25,    26,    27,
      28,    29,   130,   136,    99,   100,   101,    30,    68,    96,
      97,    31,    32,    33,    34,    35,     3,    36,    37,    75,
      76,    38,    53,    39,    40,    79
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -119
static const yytype_int16 yypact[] =
{
    -119,    35,   158,  -119,  -119,   -11,     4,  -119,  -119,  -119,
    -119,    19,   180,   180,   -22,  -119,  -119,  -119,    29,  -119,
     180,   180,   180,  -119,    26,    45,    46,    44,  -119,  -119,
      33,   156,   -14,    21,  -119,  -119,  -119,  -119,  -119,  -119,
    -119,    41,    27,   180,  -119,  -119,    48,   180,   180,    42,
    -119,    -8,  -119,   -24,  -119,   180,   180,   180,  -119,   180,
     180,   180,   180,   180,   180,   180,   180,   180,    51,     9,
    -119,    50,  -119,    -8,  -119,    62,    38,     0,  -119,    43,
    -119,   180,  -119,    46,    44,  -119,    -8,    -8,    -8,    -8,
     -14,   -14,    21,    21,  -119,    56,    60,  -119,  -119,    65,
      61,  -119,  -119,    77,    59,  -119,   180,  -119,   180,    -8,
     180,    51,    66,     9,  -119,  -119,  -119,     5,    -8,    -8,
      69,    -8,  -119,     9,  -119,   102,    59,    71,  -119,  -119,
      72,  -119,  -119,  -119,   180,  -119,  -119,    74,   130,    59,
    -119,     5,  -119
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -119,  -119,  -112,   -92,   -38,  -118,   -13,  -119,    49,    57,
      55,  -119,  -119,  -119,  -119,  -119,     1,  -119,  -119,  -119,
       6,   -21,   -20,   -15,   -10,  -119,   -16,   -65,  -119,  -119,
    -119,  -119,  -119,  -119,  -119,     7
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -67
static const yytype_int16 yytable[] =
{
      46,    51,    45,   125,   103,    47,    52,    49,   133,    41,
      81,    50,   116,     6,     7,     8,     9,    10,    82,    48,
     126,   141,   127,   138,    65,    66,    73,    77,    63,    64,
      71,    74,    78,    98,   116,     4,    63,    64,    86,    87,
      88,    89,   107,    90,    91,    42,    43,   116,   103,   -66,
      92,    93,    54,   102,    55,    57,    56,    94,   131,    58,
     109,    67,     5,     6,     7,     8,     9,    10,    69,    70,
      80,    95,   106,    11,    72,    12,   108,    13,   104,    14,
      15,    16,    17,    18,    19,   118,    20,   119,   115,   121,
     105,   110,    78,   112,   111,   113,    21,   114,   134,   123,
      22,   135,   139,   142,    83,     5,     6,     7,     8,     9,
      10,   129,    85,    84,   124,   120,    11,   122,    12,     0,
      13,   137,    14,    15,    16,    17,    18,    19,     0,    20,
       0,     0,   132,     5,     6,     7,     8,     9,    10,    21,
       0,     0,     0,    22,    11,     0,    12,     0,    13,     0,
      14,    15,    16,    17,    18,    19,     0,    20,     0,     0,
     140,     5,     6,     7,     8,     9,    10,    21,    59,    60,
       0,    22,    11,     0,    12,     0,    13,     0,    14,    15,
      16,    17,    18,    19,     0,    20,     0,    61,    62,     0,
       0,     0,    63,    64,     0,    21,    12,     0,     0,    22,
      14,    15,    16,    17,    44,    19,     0,    20,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,     0,     0,
       0,    22
};

#define yypact_value_is_default(yystate) \
  ((yystate) == (-119))

#define yytable_value_is_error(yytable_value) \
  YYID (0)

static const yytype_int16 yycheck[] =
{
      13,    22,    12,   115,    69,    27,    22,    20,   126,    20,
      34,    21,   104,     4,     5,     6,     7,     8,    42,    41,
      15,   139,    17,   135,    38,    39,    47,    48,    36,    37,
      43,    47,    48,    24,   126,     0,    36,    37,    59,    60,
      61,    62,    42,    63,    64,    41,    27,   139,   113,    20,
      65,    66,    26,    69,     9,    11,    10,    67,   123,    26,
      81,    40,     3,     4,     5,     6,     7,     8,    27,    42,
      28,    20,    34,    14,    26,    16,    33,    18,    28,    20,
      21,    22,    23,    24,    25,   106,    27,   108,    29,   110,
      28,    35,   108,    28,    34,    34,    37,    20,    27,    33,
      41,    29,    28,   141,    55,     3,     4,     5,     6,     7,
       8,    42,    57,    56,   113,   108,    14,   111,    16,    -1,
      18,   134,    20,    21,    22,    23,    24,    25,    -1,    27,
      -1,    -1,    30,     3,     4,     5,     6,     7,     8,    37,
      -1,    -1,    -1,    41,    14,    -1,    16,    -1,    18,    -1,
      20,    21,    22,    23,    24,    25,    -1,    27,    -1,    -1,
      30,     3,     4,     5,     6,     7,     8,    37,    12,    13,
      -1,    41,    14,    -1,    16,    -1,    18,    -1,    20,    21,
      22,    23,    24,    25,    -1,    27,    -1,    31,    32,    -1,
      -1,    -1,    36,    37,    -1,    37,    16,    -1,    -1,    41,
      20,    21,    22,    23,    24,    25,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    -1,    -1,
      -1,    41
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    44,    45,    69,     0,     3,     4,     5,     6,     7,
       8,    14,    16,    18,    20,    21,    22,    23,    24,    25,
      27,    37,    41,    46,    49,    50,    51,    52,    53,    54,
      60,    64,    65,    66,    67,    68,    70,    71,    74,    76,
      77,    20,    41,    27,    24,    67,    49,    27,    41,    49,
      67,    64,    69,    75,    26,     9,    10,    11,    26,    12,
      13,    31,    32,    36,    37,    38,    39,    40,    61,    27,
      42,    49,    26,    64,    69,    72,    73,    64,    69,    78,
      28,    34,    42,    51,    52,    53,    64,    64,    64,    64,
      65,    65,    66,    66,    67,    20,    62,    63,    24,    57,
      58,    59,    69,    70,    28,    28,    34,    42,    33,    64,
      35,    34,    28,    34,    20,    29,    46,    48,    64,    64,
      78,    64,    63,    33,    59,    45,    15,    17,    47,    42,
      55,    70,    30,    48,    27,    29,    56,    49,    45,    28,
      30,    48,    47
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* This macro is provided for backward compatibility. */

#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
	    /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (0, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  YYSIZE_T yysize1;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = 0;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
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
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                yysize1 = yysize + yytnamerr (0, yytname[yyx]);
                if (! (yysize <= yysize1
                       && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                  return 2;
                yysize = yysize1;
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  yysize1 = yysize + yystrlen (yyformat);
  if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
    return 2;
  yysize = yysize1;

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1806 of yacc.c  */
#line 53 "parser.yacc"
    {
                          programAST = CAST_TO( StatementList, (yyvsp[(1) - (1)].node) );
                          if( programAST != NULL ){
                            (yyval.node) = (yyvsp[(1) - (1)].node);
                          }
                       }
    break;

  case 3:

/* Line 1806 of yacc.c  */
#line 60 "parser.yacc"
    {
                                            stmtList = new StatementList();
                                            (yyval.node) = stmtList;
                                       }
    break;

  case 4:

/* Line 1806 of yacc.c  */
#line 65 "parser.yacc"
    {
                                            stmtList = CAST_TO( StatementList, (yyvsp[(1) - (2)].node) );
                                            if( stmtList != NULL ){
                                              stmtList->push_back( (yyvsp[(2) - (2)].node) );
                                            }
                                            (yyval.node) = stmtList;
                                       }
    break;

  case 5:

/* Line 1806 of yacc.c  */
#line 74 "parser.yacc"
    {
                                      (yyval.node) = (yyvsp[(1) - (2)].node);
                                      removeType();
                                   }
    break;

  case 6:

/* Line 1806 of yacc.c  */
#line 79 "parser.yacc"
    {
                                      (yyval.node) = (yyvsp[(1) - (1)].node);
                                   }
    break;

  case 7:

/* Line 1806 of yacc.c  */
#line 82 "parser.yacc"
    {   // right now else block is compulsory,
                                                                // because it is not yet decided, whether to make if an expression or a 
                                                                // statement, if it becomes a statement, then else will be 
                                                                // optional
                                                                Operands *operands = new Operands();
                                                                operands->push_back( (yyvsp[(3) - (6)].node) );
                                                                operands->push_back( (yyvsp[(5) - (6)].node) );
                                                                operands->push_back( (yyvsp[(6) - (6)].node) );
                                                                Operator *ifNode = new Operator( __if, 3, operands );
                                                                (yyval.node) = ifNode;
                                                            }
    break;

  case 8:

/* Line 1806 of yacc.c  */
#line 93 "parser.yacc"
    {
                                        Operands *operands = new Operands();
                                        operands->push_back( (yyvsp[(2) - (3)].node) );
                                        Operator *returnNode = new Operator( __return, 1, operands );
                                        (yyval.node) = returnNode;
                                   }
    break;

  case 9:

/* Line 1806 of yacc.c  */
#line 100 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (2)].node); }
    break;

  case 10:

/* Line 1806 of yacc.c  */
#line 103 "parser.yacc"
    { 
                            Operands *operands = new Operands();
                            operands->push_back( (yyvsp[(2) - (2)].node) );
                            Operator *elseNode = new Operator( __else, 1, operands );
                            (yyval.node) = elseNode;
                       }
    break;

  case 11:

/* Line 1806 of yacc.c  */
#line 109 "parser.yacc"
    {
                                                                    Operands *operands = new Operands();
                                                                    operands->push_back( (yyvsp[(3) - (6)].node) );
                                                                    operands->push_back( (yyvsp[(5) - (6)].node) );
                                                                    operands->push_back( (yyvsp[(6) - (6)].node) );
                                                                    Operator *elifNode = new Operator( __elif, 3, operands );
                                                                    (yyval.node) = elifNode;
                                                              }
    break;

  case 12:

/* Line 1806 of yacc.c  */
#line 118 "parser.yacc"
    {  (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 13:

/* Line 1806 of yacc.c  */
#line 119 "parser.yacc"
    {  (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 14:

/* Line 1806 of yacc.c  */
#line 122 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 15:

/* Line 1806 of yacc.c  */
#line 125 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 16:

/* Line 1806 of yacc.c  */
#line 126 "parser.yacc"
    {
                                                  Operands *operands = new Operands();
                                                  operands->push_back( (yyvsp[(1) - (3)].node) );
                                                  operands->push_back( (yyvsp[(3) - (3)].node) );
                                                  Operator *orExpNode = new Operator( __or, 2, operands );
                                                  (yyval.node) = orExpNode;
                                               }
    break;

  case 17:

/* Line 1806 of yacc.c  */
#line 135 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 18:

/* Line 1806 of yacc.c  */
#line 136 "parser.yacc"
    {
                                                  Operands *operands = new Operands();
                                                  operands->push_back( (yyvsp[(1) - (3)].node) );
                                                  operands->push_back( (yyvsp[(3) - (3)].node) );
                                                  Operator *andNode = new Operator( __and, 2, operands );
                                                  (yyval.node) = andNode;
                                               }
    break;

  case 19:

/* Line 1806 of yacc.c  */
#line 145 "parser.yacc"
    {  (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 20:

/* Line 1806 of yacc.c  */
#line 146 "parser.yacc"
    { 
                                                  Operands *operands = new Operands();
                                                  operands->push_back( (yyvsp[(1) - (3)].node) );
                                                  operands->push_back( (yyvsp[(3) - (3)].node) );
                                                  Operator *equality = new Operator( __equality, 2, operands );
                                                  (yyval.node) = equality;
                                               }
    break;

  case 21:

/* Line 1806 of yacc.c  */
#line 155 "parser.yacc"
    {
                                                  Operands *operands = new Operands();
                                                  operands->push_back( (yyvsp[(1) - (3)].node) );
                                                  operands->push_back( (yyvsp[(3) - (3)].node) );
                                                  Operator *ltRelOpNode = new Operator( __lt, 2, operands );
                                                  (yyval.node) = ltRelOpNode;
                                               }
    break;

  case 22:

/* Line 1806 of yacc.c  */
#line 162 "parser.yacc"
    {
                                                  Operands *operands = new Operands();
                                                  operands->push_back( (yyvsp[(1) - (3)].node) );
                                                  operands->push_back( (yyvsp[(3) - (3)].node) );
                                                  Operator *leRelOpNode = new Operator( __le, 2, operands );
                                                  (yyval.node) = leRelOpNode;
                                               }
    break;

  case 23:

/* Line 1806 of yacc.c  */
#line 169 "parser.yacc"
    {
                                                  Operands *operands = new Operands();
                                                  operands->push_back( (yyvsp[(1) - (3)].node) );
                                                  operands->push_back( (yyvsp[(3) - (3)].node) );
                                                  Operator *gtRelOpNode = new Operator( __gt, 2, operands );
                                                  (yyval.node) = gtRelOpNode;
                                               }
    break;

  case 24:

/* Line 1806 of yacc.c  */
#line 176 "parser.yacc"
    {
                                                  Operands *operands = new Operands();
                                                  operands->push_back( (yyvsp[(1) - (3)].node) );
                                                  operands->push_back( (yyvsp[(3) - (3)].node) );
                                                  Operator *geRelOpNode = new Operator( __ge, 2, operands );
                                                  (yyval.node) = geRelOpNode;
                                               }
    break;

  case 25:

/* Line 1806 of yacc.c  */
#line 183 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 26:

/* Line 1806 of yacc.c  */
#line 187 "parser.yacc"
    {
                                                                                                Operands *operands = new Operands();
                                                                                                operands->push_back( (yyvsp[(2) - (8)].node) );
                                                                                                operands->push_back( (yyvsp[(4) - (8)].node) );
                                                                                                operands->push_back( (yyvsp[(7) - (8)].node) );
                                                                                                operands->push_back( (yyvsp[(8) - (8)].node) );
                                                                                                Operator *functDef = new Operator( __funct_def, 4, operands );
                                                                                                (yyval.node) = functDef;
                                                                                             }
    break;

  case 27:

/* Line 1806 of yacc.c  */
#line 198 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 28:

/* Line 1806 of yacc.c  */
#line 201 "parser.yacc"
    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 29:

/* Line 1806 of yacc.c  */
#line 203 "parser.yacc"
    { (yyval.node) = new FormalParameterList(); }
    break;

  case 30:

/* Line 1806 of yacc.c  */
#line 204 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node);   }
    break;

  case 31:

/* Line 1806 of yacc.c  */
#line 207 "parser.yacc"
    {
                                                                   FormalParameterList *fpList = new FormalParameterList();
                                                                   fpList->push_back( (yyvsp[(1) - (1)].node) );
                                                                   (yyval.node) = fpList;
                                                                }
    break;

  case 32:

/* Line 1806 of yacc.c  */
#line 212 "parser.yacc"
    {
                                                                    FormalParameterList *fpList = CAST_TO( FormalParameterList, (yyvsp[(1) - (3)].node) );
                                                                    if( fpList != NULL ){
                                                                      fpList->push_back( (yyvsp[(3) - (3)].node) );
                                                                    }
                                                                    (yyval.node) = fpList;
                                                                 }
    break;

  case 33:

/* Line 1806 of yacc.c  */
#line 221 "parser.yacc"
    {
                                            FormalParameter *fParameter = new FormalParameter( (yyvsp[(1) - (2)].node), (yyvsp[(2) - (2)].node) );
                                            (yyval.node) = fParameter;
                                        }
    break;

  case 34:

/* Line 1806 of yacc.c  */
#line 227 "parser.yacc"
    { putType( (yyvsp[(1) - (1)].node)->getType() ); }
    break;

  case 35:

/* Line 1806 of yacc.c  */
#line 227 "parser.yacc"
    {
                                                              Operands *operands = new Operands();
                                                              operands->push_back( (yyvsp[(1) - (3)].node) );
                                                              operands->push_back( (yyvsp[(3) - (3)].node) );
                                                              Operator *vDefinitionNode = new Operator( __var_definition, 2, operands );
                                                              removeType();
                                                              (yyval.node) = vDefinitionNode;
                                                         }
    break;

  case 36:

/* Line 1806 of yacc.c  */
#line 237 "parser.yacc"
    {
                                                        VariableList *vlist = new VariableList( -1 );
                                                        vlist->push_back( (yyvsp[(1) - (1)].node) );
                                                        (yyval.node) = vlist;
                                                   }
    break;

  case 37:

/* Line 1806 of yacc.c  */
#line 243 "parser.yacc"
    {
                                                         VariableList *vlist = CAST_TO( VariableList, (yyvsp[(1) - (3)].node) );
                                                         if( vlist != NULL ){
                                                            vlist->push_back( (yyvsp[(3) - (3)].node) );
                                                         }
                                                         (yyval.node) = vlist;
                                                    }
    break;

  case 38:

/* Line 1806 of yacc.c  */
#line 252 "parser.yacc"
    {
                                                    Operands *operands = new Operands();
                                                    operands->push_back( new Type( getType() ) );
                                                    operands->push_back( (yyvsp[(1) - (3)].node) );
                                                    operands->push_back( (yyvsp[(3) - (3)].node) );
                                                    Operator *node = new Operator( __assignment, 3, operands );
                                                    (yyval.node) = node;
                                                }
    break;

  case 39:

/* Line 1806 of yacc.c  */
#line 262 "parser.yacc"
    {
                                              Operands *operands = new Operands();
                                              operands->push_back( (yyvsp[(1) - (3)].node) );
                                              operands->push_back( (yyvsp[(3) - (3)].node) );
                                              Operator *plusNode = new Operator( __addition, 2, operands );
                                              (yyval.node) = plusNode;
                                          }
    break;

  case 40:

/* Line 1806 of yacc.c  */
#line 269 "parser.yacc"
    {
                                              Operands *operands = new Operands();
                                              operands->push_back( (yyvsp[(1) - (3)].node) );
                                              operands->push_back( (yyvsp[(3) - (3)].node) );
                                              Operator *subtractionNode = new Operator( __subtraction, 2, operands );
                                              (yyval.node) = subtractionNode;
                                          }
    break;

  case 41:

/* Line 1806 of yacc.c  */
#line 276 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 42:

/* Line 1806 of yacc.c  */
#line 279 "parser.yacc"
    {
                                              Operands *operands = new Operands();
                                              operands->push_back( (yyvsp[(1) - (3)].node) );
                                              operands->push_back( (yyvsp[(3) - (3)].node) );
                                              Operator *multiplicationNode = new Operator( __multiplication, 2, operands );
                                              (yyval.node) = multiplicationNode;
                                          }
    break;

  case 43:

/* Line 1806 of yacc.c  */
#line 286 "parser.yacc"
    {
                                              Operands *operands = new Operands();
                                              operands->push_back( (yyvsp[(1) - (3)].node) );
                                              operands->push_back( (yyvsp[(3) - (3)].node) );
                                              Operator *divNode = new Operator( __div, 2, operands );
                                              (yyval.node) = divNode;
                                          }
    break;

  case 44:

/* Line 1806 of yacc.c  */
#line 293 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 45:

/* Line 1806 of yacc.c  */
#line 296 "parser.yacc"
    {
                                              Operands *operands = new Operands();
                                              operands->push_back( (yyvsp[(1) - (3)].node) );
                                              operands->push_back( (yyvsp[(3) - (3)].node) );
                                              Operator *powerNode = new Operator( __power, 2, operands );
                                              (yyval.node) = powerNode;
                                          }
    break;

  case 46:

/* Line 1806 of yacc.c  */
#line 303 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 47:

/* Line 1806 of yacc.c  */
#line 306 "parser.yacc"
    {
                                              Operands *operands = new Operands();
                                              operands->push_back( (yyvsp[(2) - (2)].node) );
                                              Operator *notNode = new Operator( __not, 1, operands );
                                              (yyval.node) = notNode;
                                          }
    break;

  case 48:

/* Line 1806 of yacc.c  */
#line 312 "parser.yacc"
    {
                                              Operands *operands = new Operands();
                                              operands->push_back( (yyvsp[(2) - (2)].node) );
                                              Operator *uMinusNode = new Operator( __uminus, 1, operands );
                                              (yyval.node) = uMinusNode;
                                          }
    break;

  case 49:

/* Line 1806 of yacc.c  */
#line 318 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 50:

/* Line 1806 of yacc.c  */
#line 321 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 51:

/* Line 1806 of yacc.c  */
#line 322 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 52:

/* Line 1806 of yacc.c  */
#line 323 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 53:

/* Line 1806 of yacc.c  */
#line 324 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 54:

/* Line 1806 of yacc.c  */
#line 325 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 55:

/* Line 1806 of yacc.c  */
#line 326 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 56:

/* Line 1806 of yacc.c  */
#line 327 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 57:

/* Line 1806 of yacc.c  */
#line 328 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 58:

/* Line 1806 of yacc.c  */
#line 329 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 59:

/* Line 1806 of yacc.c  */
#line 330 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 60:

/* Line 1806 of yacc.c  */
#line 331 "parser.yacc"
    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 62:

/* Line 1806 of yacc.c  */
#line 336 "parser.yacc"
    {  (yyval.node) = new Type(__integer_t ); }
    break;

  case 63:

/* Line 1806 of yacc.c  */
#line 337 "parser.yacc"
    {  (yyval.node) = new Type(__double_t );  }
    break;

  case 64:

/* Line 1806 of yacc.c  */
#line 338 "parser.yacc"
    {  (yyval.node) = new Type(__string_t );  }
    break;

  case 65:

/* Line 1806 of yacc.c  */
#line 339 "parser.yacc"
    {  (yyval.node) = new Type(__function_t ); }
    break;

  case 66:

/* Line 1806 of yacc.c  */
#line 340 "parser.yacc"
    {  (yyval.node) = new Type(__nothing_t ); }
    break;

  case 67:

/* Line 1806 of yacc.c  */
#line 341 "parser.yacc"
    {  (yyval.node) = new Type(__boolean_t); }
    break;

  case 68:

/* Line 1806 of yacc.c  */
#line 342 "parser.yacc"
    {  (yyval.node) = new Type(__array_int_t); }
    break;

  case 69:

/* Line 1806 of yacc.c  */
#line 345 "parser.yacc"
    {
                                              Operands *operands = new Operands();
                                              operands->push_back( (yyvsp[(1) - (4)].node) );
                                              if( (yyvsp[(3) - (4)].node) != NULL ){
                                                  operands->push_back( (yyvsp[(3) - (4)].node) );
                                              }
                                              Operator *functCall = new Operator( __funct_call, 2, operands );
                                              (yyval.node) = functCall;
                                          }
    break;

  case 70:

/* Line 1806 of yacc.c  */
#line 356 "parser.yacc"
    {
                                      (yyval.node) = new ArgumentList();
                                   }
    break;

  case 71:

/* Line 1806 of yacc.c  */
#line 360 "parser.yacc"
    {  (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;

  case 72:

/* Line 1806 of yacc.c  */
#line 363 "parser.yacc"
    {
                                        ArgumentList *arglist = new ArgumentList();
                                        arglist->push_back( (yyvsp[(1) - (1)].node) );
                                        (yyval.node) = arglist;
                                        //cout<<"Hello...args"<<endl;
                                        //_debugMessage( "In arguments..." );
                                     }
    break;

  case 73:

/* Line 1806 of yacc.c  */
#line 371 "parser.yacc"
    {
                                        ArgumentList *arglist = CAST_TO( ArgumentList, (yyvsp[(1) - (3)].node) );
                                        arglist->push_back( (yyvsp[(3) - (3)].node) );
                                        (yyval.node) = arglist;
                                        //cout<<"Args seen: "<<arglist->getLength()<<endl;
                                     }
    break;

  case 74:

/* Line 1806 of yacc.c  */
#line 379 "parser.yacc"
    { (yyval.node) = (yyvsp[(2) - (3)].node); }
    break;

  case 75:

/* Line 1806 of yacc.c  */
#line 382 "parser.yacc"
    {  ValueList *vlist = new ValueList();
                                       //vlist->push_back( $1 );
                                       (yyval.node) = vlist;
                                     }
    break;

  case 76:

/* Line 1806 of yacc.c  */
#line 386 "parser.yacc"
    {  ValueList *vlist = new ValueList();
                                        vlist->push_back( (yyvsp[(1) - (1)].node) );
                                        (yyval.node) = vlist;
                                     }
    break;

  case 77:

/* Line 1806 of yacc.c  */
#line 391 "parser.yacc"
    {
                                        ValueList *vlist = CAST_TO( ValueList, (yyvsp[(1) - (3)].node) );
                                        if( vlist != NULL ){
                                            vlist->push_back( (yyvsp[(3) - (3)].node) );
                                        }
                                        (yyval.node) = vlist;
                                     }
    break;

  case 78:

/* Line 1806 of yacc.c  */
#line 399 "parser.yacc"
    {
                                          Operands *operands = new Operands();
                                          operands->push_back((yyvsp[(1) - (4)].node));
                                          operands->push_back((yyvsp[(3) - (4)].node));
                                          Operator *arrayReadOp = new Operator(__indexOp, 2, operands);
                                          (yyval.node) = arrayReadOp;
                                        }
    break;

  case 79:

/* Line 1806 of yacc.c  */
#line 408 "parser.yacc"
    {
                                                        Operands *operands = new Operands();
                                                        operands->push_back((yyvsp[(1) - (6)].node));
                                                        operands->push_back((yyvsp[(3) - (6)].node));
                                                        operands->push_back((yyvsp[(5) - (6)].node));
                                                        Operator *sliceOp = new Operator(__sliceOp, 3, operands);
                                                        (yyval.node) = sliceOp;
                                                 }
    break;

  case 80:

/* Line 1806 of yacc.c  */
#line 418 "parser.yacc"
    { (yyval.node) = NULL; }
    break;

  case 81:

/* Line 1806 of yacc.c  */
#line 419 "parser.yacc"
    { (yyval.node) = (yyvsp[(1) - (1)].node); }
    break;



/* Line 1806 of yacc.c  */
#line 2357 "y.tab.c"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 2067 of yacc.c  */
#line 421 "parser.yacc"


void yyerror( const char* error ){
    cout<<"Error: "<<error<<endl;
}

int main(){   
    yyparse();
    Context *ctx = new Context();
    Interpreter interp;
    int length;    
    length = programAST->getLength();
    cout<<"Parsing Done\n";
    for( int i = 0; i < length; i++ ){
      if( !programAST->empty() ){
        interp.evaluate( programAST->pop_front(), ctx, -1 );
      }
    }
    return 0;
}

void putType( DataType _type ){
  typeStack.push( _type );
}

DataType getType(void){
  if( typeStack.size() != 0 ){
      return typeStack.top();
  }
  else{
    return -1;
  }
}

void removeType(void){
  if( typeStack.size() != 0 ){
    typeStack.pop();
  }
}

