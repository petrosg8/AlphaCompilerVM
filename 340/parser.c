/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse alpha_yyparse
#define yylex   alpha_yylex
#define yyerror alpha_yyerror
#define yylval  alpha_yylval
#define yychar  alpha_yychar
#define yydebug alpha_yydebug
#define yynerrs alpha_yynerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     IF = 258,
     ELSE = 259,
     WHILE = 260,
     FOR = 261,
     FUNCTION = 262,
     BREAK = 263,
     CONT = 264,
     RETURN = 265,
     AND = 266,
     NOT = 267,
     OR = 268,
     LOCAL = 269,
     TRUE = 270,
     FALSE = 271,
     NIL = 272,
     EQUAL = 273,
     PLUS = 274,
     MINUS = 275,
     STAR = 276,
     SLASH = 277,
     PERC = 278,
     EQ_EQ = 279,
     NEQ = 280,
     PLUS_PLUS = 281,
     MINUS_MINUS = 282,
     GREATER = 283,
     LESS = 284,
     GREQ = 285,
     LEQ = 286,
     BRACE_L = 287,
     BRACE_R = 288,
     BRACKET_L = 289,
     BRACKET_R = 290,
     PARENTH_L = 291,
     PARENTH_R = 292,
     SEMICOLON = 293,
     COMMA = 294,
     COLON = 295,
     DOUBLE_COLON = 296,
     DOT = 297,
     DOT_DOT = 298,
     INT = 299,
     REAL = 300,
     ID = 301,
     STRING = 302,
     UMINUS = 303
   };
#endif
/* Tokens.  */
#define IF 258
#define ELSE 259
#define WHILE 260
#define FOR 261
#define FUNCTION 262
#define BREAK 263
#define CONT 264
#define RETURN 265
#define AND 266
#define NOT 267
#define OR 268
#define LOCAL 269
#define TRUE 270
#define FALSE 271
#define NIL 272
#define EQUAL 273
#define PLUS 274
#define MINUS 275
#define STAR 276
#define SLASH 277
#define PERC 278
#define EQ_EQ 279
#define NEQ 280
#define PLUS_PLUS 281
#define MINUS_MINUS 282
#define GREATER 283
#define LESS 284
#define GREQ 285
#define LEQ 286
#define BRACE_L 287
#define BRACE_R 288
#define BRACKET_L 289
#define BRACKET_R 290
#define PARENTH_L 291
#define PARENTH_R 292
#define SEMICOLON 293
#define COMMA 294
#define COLON 295
#define DOUBLE_COLON 296
#define DOT 297
#define DOT_DOT 298
#define INT 299
#define REAL 300
#define ID 301
#define STRING 302
#define UMINUS 303




/* Copy the first part of user declarations.  */
#line 1 "parser.y"

    #include <math.h>
    #include "parser_handlers.c"
    #include "alphavm.h"

    extern FILE* alpha_yyin;
    extern FILE* alpha_yyout;
    extern char* alpha_yytext;

    extern alpha_stack_t* offsetStack;

    extern unsigned executionFinished;

    FILE* quadout;
    FILE* instr_out;
    FILE* out;

    int alpha_yylex();
    void alpha_yyerror();
    void printrule(const char* rule);

    int scope = 0;
    int inFunction = 0;



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 31 "parser.y"
{
    char* strVal;
    int intVal;
    unsigned int uintVal;
    double realVal;
    struct SymbolTableEntry* symVal;
    struct expr* exprVal;
    struct VariableList* varlistVal;
    struct Function *funcVal;
    struct call *callVal;
    struct forloopStruct* forloopVal;
    struct stmt* stmtVal;
}
/* Line 193 of yacc.c.  */
#line 240 "parser.c"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 253 "parser.c"

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
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
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
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

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

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  78
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   591

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  51
/* YYNRULES -- Number of rules.  */
#define YYNRULES  111
/* YYNRULES -- Number of states.  */
#define YYNSTATES  195

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   303

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
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
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    11,    14,    16,    18,
      20,    22,    24,    26,    28,    30,    32,    35,    38,    42,
      45,    49,    53,    57,    61,    65,    69,    73,    77,    81,
      85,    89,    93,    94,   100,   101,   107,   109,   111,   113,
     115,   117,   121,   124,   127,   130,   133,   136,   139,   141,
     143,   145,   147,   151,   153,   155,   158,   161,   163,   167,
     172,   176,   181,   186,   193,   196,   198,   200,   204,   210,
     211,   213,   217,   221,   225,   227,   231,   237,   238,   243,
     246,   248,   249,   252,   253,   255,   259,   263,   264,   265,
     269,   273,   275,   277,   279,   281,   283,   285,   287,   292,
     294,   297,   302,   303,   304,   308,   310,   314,   318,   319,
     320,   328
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      50,     0,    -1,    51,    -1,    -1,    51,    52,    -1,    52,
      -1,    62,    38,    -1,    89,    -1,    95,    -1,    99,    -1,
      55,    -1,    53,    -1,    54,    -1,    75,    -1,    84,    -1,
      38,    -1,     8,    38,    -1,     9,    38,    -1,    10,    62,
      38,    -1,    10,    38,    -1,    65,    18,    62,    -1,    62,
      19,    62,    -1,    62,    20,    62,    -1,    62,    21,    62,
      -1,    62,    22,    62,    -1,    62,    23,    62,    -1,    62,
      28,    62,    -1,    62,    30,    62,    -1,    62,    29,    62,
      -1,    62,    31,    62,    -1,    62,    24,    62,    -1,    62,
      25,    62,    -1,    -1,    62,    13,    60,    97,    62,    -1,
      -1,    62,    11,    61,    97,    62,    -1,    56,    -1,    63,
      -1,    57,    -1,    58,    -1,    59,    -1,    36,    62,    37,
      -1,    20,    62,    -1,    12,    62,    -1,    26,    65,    -1,
      65,    26,    -1,    27,    65,    -1,    65,    27,    -1,    64,
      -1,    65,    -1,    67,    -1,    72,    -1,    36,    84,    37,
      -1,    86,    -1,    46,    -1,    14,    46,    -1,    41,    46,
      -1,    66,    -1,    65,    42,    46,    -1,    65,    34,    62,
      35,    -1,    67,    42,    46,    -1,    67,    34,    62,    35,
      -1,    67,    36,    71,    37,    -1,    36,    84,    37,    36,
      71,    37,    -1,    65,    68,    -1,    69,    -1,    70,    -1,
      36,    71,    37,    -1,    43,    46,    36,    71,    37,    -1,
      -1,    62,    -1,    71,    39,    62,    -1,    34,    71,    35,
      -1,    34,    73,    35,    -1,    74,    -1,    73,    39,    74,
      -1,    32,    62,    40,    62,    33,    -1,    -1,    32,    76,
      51,    33,    -1,    32,    33,    -1,    46,    -1,    -1,     7,
      77,    -1,    -1,    46,    -1,    79,    39,    46,    -1,    36,
      79,    37,    -1,    -1,    -1,    81,    75,    82,    -1,    78,
      80,    83,    -1,    45,    -1,    44,    -1,    47,    -1,    85,
      -1,    15,    -1,    16,    -1,    17,    -1,     3,    36,    62,
      37,    -1,     4,    -1,    87,    52,    -1,    87,    52,    88,
      52,    -1,    -1,    -1,    90,    52,    91,    -1,     5,    -1,
      36,    62,    37,    -1,    93,    94,    92,    -1,    -1,    -1,
       6,    36,    71,    38,    97,    62,    38,    -1,    98,    96,
      71,    37,    96,    92,    96,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    95,    95,    96,    99,   107,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   122,   135,   148,   149,
     152,   154,   155,   156,   157,   158,   160,   161,   162,   163,
     164,   165,   168,   168,   180,   180,   194,   195,   196,   197,
     198,   201,   202,   211,   222,   223,   224,   225,   226,   229,
     230,   231,   232,   238,   241,   242,   243,   244,   247,   248,
     249,   250,   253,   258,   263,   276,   277,   280,   286,   292,
     293,   294,   297,   298,   301,   302,   305,   307,   307,   308,
     311,   312,   315,   335,   336,   337,   340,   349,   350,   352,
     361,   383,   384,   387,   388,   389,   390,   391,   394,   404,
     412,   417,   429,   430,   431,   433,   435,   445,   457,   459,
     461,   472
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "IF", "ELSE", "WHILE", "FOR", "FUNCTION",
  "BREAK", "CONT", "RETURN", "AND", "NOT", "OR", "LOCAL", "TRUE", "FALSE",
  "NIL", "EQUAL", "PLUS", "MINUS", "STAR", "SLASH", "PERC", "EQ_EQ", "NEQ",
  "PLUS_PLUS", "MINUS_MINUS", "GREATER", "LESS", "GREQ", "LEQ", "BRACE_L",
  "BRACE_R", "BRACKET_L", "BRACKET_R", "PARENTH_L", "PARENTH_R",
  "SEMICOLON", "COMMA", "COLON", "DOUBLE_COLON", "DOT", "DOT_DOT", "INT",
  "REAL", "ID", "STRING", "UMINUS", "$accept", "program", "stmtlist",
  "stmt", "breakstmt", "continuestmt", "returnstmt", "assignexpr",
  "arithmexpr", "relexpr", "boolexpr", "@1", "@2", "expr", "term",
  "primary", "lvalue", "member", "call", "callsuffix", "normcall",
  "methodcall", "elist", "tablemake", "indexed", "indexedelem", "block",
  "@3", "funcname", "funcprefix", "idlist", "funcargs", "funcblockstart",
  "funcblockend", "funcbody", "funcdef", "number", "const", "ifprefix",
  "elseprefix", "ifstmt", "loopstart", "loopend", "loopstmt", "whilestart",
  "whilecond", "whilestmt", "N", "M", "forprefix", "forstmt", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    50,    51,    51,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    53,    54,    55,    55,
      56,    57,    57,    57,    57,    57,    58,    58,    58,    58,
      58,    58,    60,    59,    61,    59,    62,    62,    62,    62,
      62,    63,    63,    63,    63,    63,    63,    63,    63,    64,
      64,    64,    64,    64,    65,    65,    65,    65,    66,    66,
      66,    66,    67,    67,    67,    68,    68,    69,    70,    71,
      71,    71,    72,    72,    73,    73,    74,    76,    75,    75,
      77,    77,    78,    79,    79,    79,    80,    81,    82,    83,
      84,    85,    85,    86,    86,    86,    86,    86,    87,    88,
      89,    89,    90,    91,    92,    93,    94,    95,    96,    97,
      98,    99
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     3,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     5,     0,     5,     1,     1,     1,     1,
       1,     3,     2,     2,     2,     2,     2,     2,     1,     1,
       1,     1,     3,     1,     1,     2,     2,     1,     3,     4,
       3,     4,     4,     6,     2,     1,     1,     3,     5,     0,
       1,     3,     3,     3,     1,     3,     5,     0,     4,     2,
       1,     0,     2,     0,     1,     3,     3,     0,     0,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     4,     1,
       2,     4,     0,     0,     3,     1,     3,     3,     0,     0,
       7,     7
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,   105,     0,    81,     0,     0,     0,     0,     0,
      95,    96,    97,     0,     0,     0,    77,    69,     0,    15,
       0,    92,    91,    54,    93,     0,     2,     5,    11,    12,
      10,    36,    38,    39,    40,     0,    37,    48,    49,    57,
      50,    51,    13,     0,    14,    94,    53,     0,     7,     0,
       8,   108,     9,     0,    69,    80,    82,    16,    17,    19,
       0,    43,    55,    42,     0,    44,     0,    46,    79,     0,
       0,    70,     0,     0,    74,     0,     0,    56,     1,     4,
      34,    32,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,     0,    45,    47,     0,    69,     0,
       0,    64,    65,    66,     0,    69,     0,    83,    87,   100,
       0,   102,    69,     0,     0,    18,     0,     0,     0,    72,
       0,    73,     0,    41,    52,   109,   109,    21,    22,    23,
      24,    25,    30,    31,    26,    28,    27,    29,    20,     0,
       0,    58,     0,     0,     0,    60,    84,     0,     0,    90,
      99,     0,     0,     0,   107,     0,    98,   109,     0,    78,
       0,    71,    75,    69,     0,     0,    59,    67,    69,    61,
      62,    86,     0,    88,   101,   106,   103,   108,     0,     0,
       0,    35,    33,     0,    85,    89,   104,   102,     0,    76,
      63,    68,   108,   110,   111
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,   126,   125,    35,    36,    37,    38,    39,    40,   101,
     102,   103,    72,    41,    73,    74,    42,    69,    56,    43,
     147,   108,   148,   185,   149,    44,    45,    46,    47,   151,
      48,   153,   186,   154,    49,   111,    50,   112,   164,    51,
      52
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -173
static const yytype_int16 yypact[] =
{
     205,   -22,  -173,   -17,    10,    24,    26,   241,   300,    25,
    -173,  -173,  -173,   300,   -10,   -10,    37,   277,    92,  -173,
      27,  -173,  -173,  -173,  -173,    29,   205,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,   121,  -173,  -173,    -9,  -173,
      -4,  -173,  -173,     8,  -173,  -173,  -173,   205,  -173,    36,
    -173,  -173,  -173,   300,   300,  -173,  -173,  -173,  -173,  -173,
     351,  -173,  -173,  -173,    67,   -21,    -4,   -21,  -173,   205,
     300,   519,   -23,   -11,  -173,   393,    49,  -173,  -173,  -173,
    -173,  -173,   300,   300,   300,   300,   300,   300,   300,   300,
     300,   300,   300,  -173,   300,  -173,  -173,   300,   300,    42,
      43,  -173,  -173,  -173,   300,   300,    46,    48,  -173,    91,
     300,  -173,   300,   414,    22,  -173,    59,   160,   329,  -173,
     300,  -173,    68,  -173,    65,  -173,  -173,    19,    19,  -173,
    -173,  -173,   547,   547,   243,   243,   243,   243,   519,   456,
      -2,  -173,    66,   477,     6,  -173,  -173,    11,    78,  -173,
    -173,   205,   435,   205,  -173,    15,  -173,  -173,    65,  -173,
     300,   519,  -173,   300,   300,   300,  -173,  -173,   300,  -173,
    -173,  -173,    69,  -173,  -173,  -173,  -173,  -173,   300,   498,
      16,   560,   534,    20,  -173,  -173,  -173,  -173,   372,  -173,
    -173,  -173,  -173,  -173,  -173
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -173,  -173,    45,   -24,  -173,  -173,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,    -7,  -173,  -173,    52,  -173,    54,  -173,
    -173,  -173,   -47,  -173,  -173,    -5,   -37,  -173,  -173,  -173,
    -173,  -173,  -173,  -173,  -173,   -15,  -173,  -173,  -173,  -173,
    -173,  -173,  -173,   -67,  -173,  -173,  -173,  -172,  -118,  -173,
    -173
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_int16 yytable[] =
{
      60,    61,    79,    76,     9,   187,    63,   114,   165,    94,
      71,    75,   119,    97,    53,    98,   120,    95,    96,    54,
     194,    99,   100,   109,   121,    97,    64,    98,   122,    78,
     104,    20,   105,    99,   100,   167,    23,   120,   106,   178,
      84,    85,    86,   170,   107,   120,   113,    71,   171,   116,
     172,   140,   177,   190,   120,   120,    55,   191,   144,   120,
     157,   120,    57,   118,    58,   155,    65,    67,    66,    66,
      68,    62,   110,    77,     4,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   124,   138,   141,   142,
     139,    71,   145,    79,   146,   150,   158,   143,    71,     4,
      70,   163,   168,   152,     8,    71,     9,    10,    11,    12,
      16,   173,    13,   161,   117,   184,   180,   162,    14,    15,
     192,   183,     0,     0,     0,     0,    17,   174,    18,   176,
       0,     0,    80,    20,    81,     0,    21,    22,    23,    24,
      82,    83,    84,    85,    86,    87,    88,     0,     0,    89,
      90,    91,    92,   179,     0,     0,    71,   181,   182,    93,
       0,    71,     0,     1,     0,     2,     3,     4,     5,     6,
       7,   188,     8,     0,     9,    10,    11,    12,     0,     0,
      13,     0,     0,     0,     0,     0,    14,    15,     0,     0,
       0,     0,    16,   159,    17,     0,    18,     0,    19,     0,
       0,    20,     0,     0,    21,    22,    23,    24,     1,     0,
       2,     3,     4,     5,     6,     7,     0,     8,     0,     9,
      10,    11,    12,     0,     0,    13,     0,     0,     0,     0,
       0,    14,    15,     0,     0,     0,     0,    16,     0,    17,
       0,    18,     0,    19,     0,     0,    20,     0,     0,    21,
      22,    23,    24,     8,     0,     9,    10,    11,    12,     0,
       0,    13,    82,    83,    84,    85,    86,    14,    15,     0,
       0,    -1,    -1,    -1,    -1,    17,     0,    18,     0,    59,
       0,     0,    20,     0,     0,    21,    22,    23,    24,     8,
       0,     9,    10,    11,    12,     0,     0,    13,     0,     0,
       0,     0,     0,    14,    15,     0,     0,     0,     0,    70,
       0,    17,     8,    18,     9,    10,    11,    12,    20,     0,
      13,    21,    22,    23,    24,     0,    14,    15,     0,     0,
       0,     0,     0,     0,    17,     0,    18,     0,     0,     0,
      80,    20,    81,     0,    21,    22,    23,    24,    82,    83,
      84,    85,    86,    87,    88,     0,     0,    89,    90,    91,
      92,     0,    80,     0,    81,     0,     0,     0,     0,   160,
      82,    83,    84,    85,    86,    87,    88,     0,     0,    89,
      90,    91,    92,    80,     0,    81,     0,     0,     0,   115,
       0,    82,    83,    84,    85,    86,    87,    88,     0,     0,
      89,    90,    91,    92,    80,     0,    81,     0,     0,     0,
     193,     0,    82,    83,    84,    85,    86,    87,    88,     0,
       0,    89,    90,    91,    92,    80,     0,    81,     0,     0,
     123,     0,     0,    82,    83,    84,    85,    86,    87,    88,
       0,     0,    89,    90,    91,    92,    80,     0,    81,     0,
       0,   156,     0,     0,    82,    83,    84,    85,    86,    87,
      88,     0,     0,    89,    90,    91,    92,    80,     0,    81,
       0,     0,   175,     0,     0,    82,    83,    84,    85,    86,
      87,    88,     0,     0,    89,    90,    91,    92,    80,     0,
      81,   166,     0,     0,     0,     0,    82,    83,    84,    85,
      86,    87,    88,     0,     0,    89,    90,    91,    92,    80,
       0,    81,   169,     0,     0,     0,     0,    82,    83,    84,
      85,    86,    87,    88,     0,     0,    89,    90,    91,    92,
      80,   189,    81,     0,     0,     0,     0,     0,    82,    83,
      84,    85,    86,    87,    88,    80,     0,    89,    90,    91,
      92,     0,     0,    82,    83,    84,    85,    86,    87,    88,
       0,     0,    89,    90,    91,    92,    82,    83,    84,    85,
      86,    -1,    -1,     0,     0,    89,    90,    91,    92,    82,
      83,    84,    85,    86,    87,    88,     0,     0,    89,    90,
      91,    92
};

static const yytype_int16 yycheck[] =
{
       7,     8,    26,    18,    14,   177,    13,    54,   126,    18,
      17,    18,    35,    34,    36,    36,    39,    26,    27,    36,
     192,    42,    43,    47,    35,    34,    36,    36,    39,     0,
      34,    41,    36,    42,    43,    37,    46,    39,    42,   157,
      21,    22,    23,    37,    36,    39,    53,    54,    37,    64,
      39,    98,    37,    37,    39,    39,    46,    37,   105,    39,
      38,    39,    38,    70,    38,   112,    14,    15,    14,    15,
      33,    46,    36,    46,     7,    82,    83,    84,    85,    86,
      87,    88,    89,    90,    91,    92,    37,    94,    46,    46,
      97,    98,    46,   117,    46,     4,    37,   104,   105,     7,
      32,    36,    36,   110,    12,   112,    14,    15,    16,    17,
      32,   148,    20,   120,    69,    46,   163,   122,    26,    27,
     187,   168,    -1,    -1,    -1,    -1,    34,   151,    36,   153,
      -1,    -1,    11,    41,    13,    -1,    44,    45,    46,    47,
      19,    20,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,   160,    -1,    -1,   163,   164,   165,    38,
      -1,   168,    -1,     3,    -1,     5,     6,     7,     8,     9,
      10,   178,    12,    -1,    14,    15,    16,    17,    -1,    -1,
      20,    -1,    -1,    -1,    -1,    -1,    26,    27,    -1,    -1,
      -1,    -1,    32,    33,    34,    -1,    36,    -1,    38,    -1,
      -1,    41,    -1,    -1,    44,    45,    46,    47,     3,    -1,
       5,     6,     7,     8,     9,    10,    -1,    12,    -1,    14,
      15,    16,    17,    -1,    -1,    20,    -1,    -1,    -1,    -1,
      -1,    26,    27,    -1,    -1,    -1,    -1,    32,    -1,    34,
      -1,    36,    -1,    38,    -1,    -1,    41,    -1,    -1,    44,
      45,    46,    47,    12,    -1,    14,    15,    16,    17,    -1,
      -1,    20,    19,    20,    21,    22,    23,    26,    27,    -1,
      -1,    28,    29,    30,    31,    34,    -1,    36,    -1,    38,
      -1,    -1,    41,    -1,    -1,    44,    45,    46,    47,    12,
      -1,    14,    15,    16,    17,    -1,    -1,    20,    -1,    -1,
      -1,    -1,    -1,    26,    27,    -1,    -1,    -1,    -1,    32,
      -1,    34,    12,    36,    14,    15,    16,    17,    41,    -1,
      20,    44,    45,    46,    47,    -1,    26,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    -1,    36,    -1,    -1,    -1,
      11,    41,    13,    -1,    44,    45,    46,    47,    19,    20,
      21,    22,    23,    24,    25,    -1,    -1,    28,    29,    30,
      31,    -1,    11,    -1,    13,    -1,    -1,    -1,    -1,    40,
      19,    20,    21,    22,    23,    24,    25,    -1,    -1,    28,
      29,    30,    31,    11,    -1,    13,    -1,    -1,    -1,    38,
      -1,    19,    20,    21,    22,    23,    24,    25,    -1,    -1,
      28,    29,    30,    31,    11,    -1,    13,    -1,    -1,    -1,
      38,    -1,    19,    20,    21,    22,    23,    24,    25,    -1,
      -1,    28,    29,    30,    31,    11,    -1,    13,    -1,    -1,
      37,    -1,    -1,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    11,    -1,    13,    -1,
      -1,    37,    -1,    -1,    19,    20,    21,    22,    23,    24,
      25,    -1,    -1,    28,    29,    30,    31,    11,    -1,    13,
      -1,    -1,    37,    -1,    -1,    19,    20,    21,    22,    23,
      24,    25,    -1,    -1,    28,    29,    30,    31,    11,    -1,
      13,    35,    -1,    -1,    -1,    -1,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    11,
      -1,    13,    35,    -1,    -1,    -1,    -1,    19,    20,    21,
      22,    23,    24,    25,    -1,    -1,    28,    29,    30,    31,
      11,    33,    13,    -1,    -1,    -1,    -1,    -1,    19,    20,
      21,    22,    23,    24,    25,    11,    -1,    28,    29,    30,
      31,    -1,    -1,    19,    20,    21,    22,    23,    24,    25,
      -1,    -1,    28,    29,    30,    31,    19,    20,    21,    22,
      23,    24,    25,    -1,    -1,    28,    29,    30,    31,    19,
      20,    21,    22,    23,    24,    25,    -1,    -1,    28,    29,
      30,    31
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     5,     6,     7,     8,     9,    10,    12,    14,
      15,    16,    17,    20,    26,    27,    32,    34,    36,    38,
      41,    44,    45,    46,    47,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    62,    63,    64,    65,    66,
      67,    72,    75,    78,    84,    85,    86,    87,    89,    93,
      95,    98,    99,    36,    36,    46,    77,    38,    38,    38,
      62,    62,    46,    62,    36,    65,    67,    65,    33,    76,
      32,    62,    71,    73,    74,    62,    84,    46,     0,    52,
      11,    13,    19,    20,    21,    22,    23,    24,    25,    28,
      29,    30,    31,    38,    18,    26,    27,    34,    36,    42,
      43,    68,    69,    70,    34,    36,    42,    36,    80,    52,
      36,    94,    96,    62,    71,    38,    84,    51,    62,    35,
      39,    35,    39,    37,    37,    61,    60,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      71,    46,    46,    62,    71,    46,    46,    79,    81,    83,
       4,    88,    62,    90,    92,    71,    37,    38,    37,    33,
      40,    62,    74,    36,    97,    97,    35,    37,    36,    35,
      37,    37,    39,    75,    52,    37,    52,    37,    97,    62,
      71,    62,    62,    71,    46,    82,    91,    96,    62,    33,
      37,    37,    92,    38,    96
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
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
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
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
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
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
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



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
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
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

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

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
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
#line 95 "parser.y"
    {printrule("program -> stmtlist");;}
    break;

  case 3:
#line 96 "parser.y"
    {printrule("program -> ε");;}
    break;

  case 4:
#line 100 "parser.y"
    {
                printrule("stmtlist -> stmtlist stmt");
                (yyval.stmtVal) = (yyvsp[(1) - (2)].stmtVal);
                (yyval.stmtVal)->breaklist = mergelist((yyvsp[(1) - (2)].stmtVal)->breaklist, (yyvsp[(2) - (2)].stmtVal)->breaklist);
                (yyval.stmtVal)->contlist = mergelist((yyvsp[(1) - (2)].stmtVal)->contlist, (yyvsp[(2) - (2)].stmtVal)->contlist);
                (yyval.stmtVal)->returnlist = mergelist((yyvsp[(1) - (2)].stmtVal)->returnlist, (yyvsp[(2) - (2)].stmtVal)->returnlist);
            ;}
    break;

  case 5:
#line 107 "parser.y"
    {printrule("stmtlist -> stmt");(yyval.stmtVal) = (yyvsp[(1) - (1)].stmtVal);;}
    break;

  case 6:
#line 110 "parser.y"
    {(yyval.stmtVal) = make_stmt();(yyvsp[(1) - (2)].exprVal) = short_circuit((yyvsp[(1) - (2)].exprVal));resettempcounter();printrule("stmt -> expr;");;}
    break;

  case 7:
#line 111 "parser.y"
    {(yyval.stmtVal) = (yyvsp[(1) - (1)].stmtVal);resettempcounter();printrule("stmt -> if");;}
    break;

  case 8:
#line 112 "parser.y"
    {(yyval.stmtVal) = make_stmt();resettempcounter();printrule("stmt -> while");;}
    break;

  case 9:
#line 113 "parser.y"
    {(yyval.stmtVal) = make_stmt();resettempcounter();printrule("stmt -> for");;}
    break;

  case 10:
#line 114 "parser.y"
    {(yyval.stmtVal) = (yyvsp[(1) - (1)].stmtVal);printrule("stmt -> return");;}
    break;

  case 11:
#line 115 "parser.y"
    {(yyval.stmtVal) = (yyvsp[(1) - (1)].stmtVal);resettempcounter();printrule("stmt -> break");;}
    break;

  case 12:
#line 116 "parser.y"
    {(yyval.stmtVal) = (yyvsp[(1) - (1)].stmtVal);resettempcounter();printrule("stmt -> continue");;}
    break;

  case 13:
#line 117 "parser.y"
    {(yyval.stmtVal) = (yyvsp[(1) - (1)].stmtVal);resettempcounter();printrule("stmt -> block");;}
    break;

  case 14:
#line 118 "parser.y"
    {(yyval.stmtVal) = make_stmt();resettempcounter();printrule("stmt -> funcdef");;}
    break;

  case 15:
#line 119 "parser.y"
    {(yyval.stmtVal) = make_stmt();resettempcounter();printrule("stmt -> empty");;}
    break;

  case 16:
#line 123 "parser.y"
    {
                printrule("breakstmt");
                if(loopcounter <= 0 ) {
                    fmt_error("break statement outside of loop");
                }

                (yyval.stmtVal) = make_stmt();
                (yyval.stmtVal)->breaklist = newlist(nextquadlabel());
                emit_jump();
            ;}
    break;

  case 17:
#line 136 "parser.y"
    {
                    printrule("continuestmt");
                    if(loopcounter <= 0 ) {
                        fmt_error("continue statement outside of loop");
                    }

                    (yyval.stmtVal) = make_stmt();
                    (yyval.stmtVal)->contlist = newlist(nextquadlabel());
                    emit_jump();
                ;}
    break;

  case 18:
#line 148 "parser.y"
    {(yyval.stmtVal) = handle_returnexpr((yyvsp[(2) - (3)].exprVal));;}
    break;

  case 19:
#line 149 "parser.y"
    {(yyval.stmtVal) = handle_returnexpr(NULL);;}
    break;

  case 20:
#line 152 "parser.y"
    {(yyval.exprVal) = handle_assign((yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal));;}
    break;

  case 21:
#line 154 "parser.y"
    {(yyval.exprVal) = handle_arithmexpr((yyvsp[(1) - (3)].exprVal), add, (yyvsp[(3) - (3)].exprVal));;}
    break;

  case 22:
#line 155 "parser.y"
    {(yyval.exprVal) = handle_arithmexpr((yyvsp[(1) - (3)].exprVal), sub, (yyvsp[(3) - (3)].exprVal));;}
    break;

  case 23:
#line 156 "parser.y"
    {(yyval.exprVal) = handle_arithmexpr((yyvsp[(1) - (3)].exprVal), mul, (yyvsp[(3) - (3)].exprVal));;}
    break;

  case 24:
#line 157 "parser.y"
    {(yyval.exprVal) = handle_arithmexpr((yyvsp[(1) - (3)].exprVal), Div, (yyvsp[(3) - (3)].exprVal));;}
    break;

  case 25:
#line 158 "parser.y"
    {(yyval.exprVal) = handle_arithmexpr((yyvsp[(1) - (3)].exprVal), mod, (yyvsp[(3) - (3)].exprVal));;}
    break;

  case 26:
#line 160 "parser.y"
    {(yyval.exprVal) = handle_relexpr((yyvsp[(1) - (3)].exprVal), if_greater, (yyvsp[(3) - (3)].exprVal));;}
    break;

  case 27:
#line 161 "parser.y"
    {(yyval.exprVal) = handle_relexpr((yyvsp[(1) - (3)].exprVal), if_greatereq, (yyvsp[(3) - (3)].exprVal));;}
    break;

  case 28:
#line 162 "parser.y"
    {(yyval.exprVal) = handle_relexpr((yyvsp[(1) - (3)].exprVal), if_less, (yyvsp[(3) - (3)].exprVal));;}
    break;

  case 29:
#line 163 "parser.y"
    {(yyval.exprVal) = handle_relexpr((yyvsp[(1) - (3)].exprVal), if_lesseq, (yyvsp[(3) - (3)].exprVal));;}
    break;

  case 30:
#line 164 "parser.y"
    {(yyval.exprVal) = handle_relexpr((yyvsp[(1) - (3)].exprVal), if_eq, (yyvsp[(3) - (3)].exprVal));;}
    break;

  case 31:
#line 165 "parser.y"
    {(yyval.exprVal) = handle_relexpr((yyvsp[(1) - (3)].exprVal), if_noteq, (yyvsp[(3) - (3)].exprVal));;}
    break;

  case 32:
#line 168 "parser.y"
    {(yyvsp[(1) - (2)].exprVal) = expr_to_boolexpr((yyvsp[(1) - (2)].exprVal));;}
    break;

  case 33:
#line 169 "parser.y"
    {
                printrule("boolexpr -> or");
                (yyvsp[(5) - (5)].exprVal) = expr_to_boolexpr((yyvsp[(5) - (5)].exprVal));

                (yyval.exprVal) = newexpr(boolexpr_e);
                (yyval.exprVal)->sym = newtemp_reuse((yyvsp[(1) - (5)].exprVal), (yyvsp[(5) - (5)].exprVal), NULL);
                patchlist((yyvsp[(1) - (5)].exprVal)->falselist, (yyvsp[(4) - (5)].uintVal));
                (yyval.exprVal)->truelist = mergelist((yyvsp[(1) - (5)].exprVal)->truelist, (yyvsp[(5) - (5)].exprVal)->truelist);
                (yyval.exprVal)->falselist = (yyvsp[(5) - (5)].exprVal)->falselist;
                // emit(or, $1, $3, $$);
            ;}
    break;

  case 34:
#line 180 "parser.y"
    {(yyvsp[(1) - (2)].exprVal) = expr_to_boolexpr((yyvsp[(1) - (2)].exprVal));;}
    break;

  case 35:
#line 181 "parser.y"
    {
                printrule("boolexpr -> and");
                (yyvsp[(5) - (5)].exprVal) = expr_to_boolexpr((yyvsp[(5) - (5)].exprVal));

                (yyval.exprVal) = newexpr(boolexpr_e);
                (yyval.exprVal)->sym = newtemp_reuse((yyvsp[(1) - (5)].exprVal), (yyvsp[(5) - (5)].exprVal), NULL);
                patchlist((yyvsp[(1) - (5)].exprVal)->truelist, (yyvsp[(4) - (5)].uintVal));
                (yyval.exprVal)->truelist = (yyvsp[(5) - (5)].exprVal)->truelist;
                (yyval.exprVal)->falselist = mergelist((yyvsp[(1) - (5)].exprVal)->falselist, (yyvsp[(5) - (5)].exprVal)->falselist);
                // emit(and, $1, $3, $$);
            ;}
    break;

  case 36:
#line 194 "parser.y"
    {printrule("expr -> assign");(yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);;}
    break;

  case 37:
#line 195 "parser.y"
    {printrule("expr -> term");(yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);;}
    break;

  case 38:
#line 196 "parser.y"
    {printrule("expr -> arithm");(yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);;}
    break;

  case 39:
#line 197 "parser.y"
    {printrule("expr -> relexpr");(yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);;}
    break;

  case 40:
#line 198 "parser.y"
    {printrule("expr -> boolop");(yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);;}
    break;

  case 41:
#line 201 "parser.y"
    {printrule("term -> (expr)");(yyval.exprVal) = (yyvsp[(2) - (3)].exprVal);;}
    break;

  case 42:
#line 203 "parser.y"
    {
            printrule("term -> uminus");
            check_arith((yyvsp[(2) - (2)].exprVal), "uminus");
            (yyval.exprVal) = newexpr(arithexpr_e);
            // $$->sym = istempexpr($2) ? $2->sym : newtemp();
            (yyval.exprVal)->sym = newtemp_reuse((yyvsp[(2) - (2)].exprVal), NULL);
            emit(uminus, (yyvsp[(2) - (2)].exprVal), NULL, (yyval.exprVal));
        ;}
    break;

  case 43:
#line 212 "parser.y"
    {
            printrule("term -> !expr");
            (yyvsp[(2) - (2)].exprVal) = expr_to_boolexpr((yyvsp[(2) - (2)].exprVal));
            (yyval.exprVal) = newexpr(boolexpr_e);
            // $$->sym = istempexpr($2) ? $2->sym : newtemp();
            (yyval.exprVal)->sym = newtemp_reuse((yyvsp[(2) - (2)].exprVal), NULL);
            (yyval.exprVal)->truelist = (yyvsp[(2) - (2)].exprVal)->falselist;
            (yyval.exprVal)->falselist = (yyvsp[(2) - (2)].exprVal)->truelist;
            // emit(not, $2, NULL, $$);
        ;}
    break;

  case 44:
#line 222 "parser.y"
    {printrule("term -> ++lv");(yyval.exprVal) = handle_precrement((yyvsp[(2) - (2)].exprVal), add);;}
    break;

  case 45:
#line 223 "parser.y"
    {printrule("term -> lv++");(yyval.exprVal) = handle_postcrement((yyvsp[(1) - (2)].exprVal), add);;}
    break;

  case 46:
#line 224 "parser.y"
    {printrule("term -> --lv");(yyval.exprVal) = handle_precrement((yyvsp[(2) - (2)].exprVal), sub);;}
    break;

  case 47:
#line 225 "parser.y"
    {printrule("term -> lv--");(yyval.exprVal) = handle_postcrement((yyvsp[(1) - (2)].exprVal), sub);;}
    break;

  case 48:
#line 226 "parser.y"
    {printrule("term -> primary");(yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);;}
    break;

  case 49:
#line 229 "parser.y"
    {printrule("primary -> lvalue");(yyval.exprVal) = emit_iftableitem((yyvsp[(1) - (1)].exprVal));;}
    break;

  case 50:
#line 230 "parser.y"
    {printrule("primary -> call");(yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);;}
    break;

  case 51:
#line 231 "parser.y"
    {printrule("primary -> tablemake");(yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);;}
    break;

  case 52:
#line 233 "parser.y"
    {
                printrule("primary -> funcdef");
                (yyval.exprVal) = newexpr(programfunc_e);
                (yyval.exprVal)->sym = (yyvsp[(2) - (3)].symVal);
            ;}
    break;

  case 53:
#line 238 "parser.y"
    {printrule("primary -> const");(yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);;}
    break;

  case 54:
#line 241 "parser.y"
    {printrule("lvalue -> ID");(yyval.exprVal) = lvalue_expr(handle_lval((yyvsp[(1) - (1)].strVal)));;}
    break;

  case 55:
#line 242 "parser.y"
    {printrule("lvalue -> local ID");(yyval.exprVal) = lvalue_expr(handle_local_lval((yyvsp[(2) - (2)].strVal)));;}
    break;

  case 56:
#line 243 "parser.y"
    {printrule("lvalue -> global ID");(yyval.exprVal) = lvalue_expr(handle_global_lval((yyvsp[(2) - (2)].strVal)));;}
    break;

  case 57:
#line 244 "parser.y"
    {printrule("lvalue -> member");(yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);;}
    break;

  case 58:
#line 247 "parser.y"
    {printrule("member -> lvalue.id");(yyval.exprVal) = member_item((yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].strVal));;}
    break;

  case 59:
#line 248 "parser.y"
    {printrule("member -> lvalue[expr]");(yyval.exprVal) = member_item_expr((yyvsp[(1) - (4)].exprVal), (yyvsp[(3) - (4)].exprVal));;}
    break;

  case 60:
#line 249 "parser.y"
    {printrule("member -> call.id");(yyval.exprVal) = member_item((yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].strVal));;}
    break;

  case 61:
#line 250 "parser.y"
    {printrule("member -> call[expr]");(yyval.exprVal) = member_item_expr((yyvsp[(1) - (4)].exprVal), (yyvsp[(3) - (4)].exprVal));;}
    break;

  case 62:
#line 254 "parser.y"
    {
            printrule("call -> call(elist)");
            (yyval.exprVal) = make_call((yyvsp[(1) - (4)].exprVal), (yyvsp[(3) - (4)].exprVal));
        ;}
    break;

  case 63:
#line 259 "parser.y"
    {
            printrule("call -> (funcdef)(elist)");
            (yyval.exprVal) = make_call(lvalue_expr((yyvsp[(2) - (6)].symVal)), (yyvsp[(5) - (6)].exprVal));
        ;}
    break;

  case 64:
#line 264 "parser.y"
    {
            printrule("call -> lvalue callsuffix");
            (yyvsp[(1) - (2)].exprVal) = emit_iftableitem((yyvsp[(1) - (2)].exprVal));
            (yyvsp[(2) - (2)].callVal)->elist = reverse_elist((yyvsp[(2) - (2)].callVal)->elist);
            if ((yyvsp[(2) - (2)].callVal)->method) {
                list_append((yyvsp[(2) - (2)].callVal)->elist, (yyvsp[(1) - (2)].exprVal));
                (yyvsp[(1) - (2)].exprVal) = emit_iftableitem(member_item((yyvsp[(1) - (2)].exprVal), (yyvsp[(2) - (2)].callVal)->name));
            }
            (yyval.exprVal) = make_call_r((yyvsp[(1) - (2)].exprVal), (yyvsp[(2) - (2)].callVal)->elist);
        ;}
    break;

  case 65:
#line 276 "parser.y"
    {printrule("callsuffix -> normcall");(yyval.callVal) = (yyvsp[(1) - (1)].callVal);;}
    break;

  case 66:
#line 277 "parser.y"
    {printrule("callsuffix -> methodcall");(yyval.callVal) = (yyvsp[(1) - (1)].callVal);;}
    break;

  case 67:
#line 281 "parser.y"
    {
                printrule("normcall");
                (yyval.callVal) = newcall((yyvsp[(2) - (3)].exprVal), 0, "");
            ;}
    break;

  case 68:
#line 287 "parser.y"
    {
                printrule("methodcall");
                (yyval.callVal) = newcall((yyvsp[(4) - (5)].exprVal), 1, strdup((yyvsp[(2) - (5)].strVal)));
            ;}
    break;

  case 69:
#line 292 "parser.y"
    {printrule("elist -> empty");(yyval.exprVal) = NULL;;}
    break;

  case 70:
#line 293 "parser.y"
    {printrule("elist -> expr");(yyvsp[(1) - (1)].exprVal) = short_circuit((yyvsp[(1) - (1)].exprVal));(yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);;}
    break;

  case 71:
#line 294 "parser.y"
    {printrule("elist -> elist, expr");(yyvsp[(3) - (3)].exprVal) = short_circuit((yyvsp[(3) - (3)].exprVal));list_append((yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal));;}
    break;

  case 72:
#line 297 "parser.y"
    {printrule("tablemake");(yyval.exprVal) = handle_tablemake_elist((yyvsp[(2) - (3)].exprVal));;}
    break;

  case 73:
#line 298 "parser.y"
    {printrule("tablemake");(yyval.exprVal) = handle_tablemake_idx((yyvsp[(2) - (3)].exprVal));;}
    break;

  case 74:
#line 301 "parser.y"
    {printrule("indexed -> indexedelem");(yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);;}
    break;

  case 75:
#line 302 "parser.y"
    {printrule("indexed -> indexed, indexedelem");list_append((yyvsp[(1) - (3)].exprVal), (yyvsp[(3) - (3)].exprVal));;}
    break;

  case 76:
#line 305 "parser.y"
    {printrule("indexedelem -> {expr:expr}");(yyval.exprVal) = (yyvsp[(4) - (5)].exprVal);(yyval.exprVal)->index = (yyvsp[(2) - (5)].exprVal);;}
    break;

  case 77:
#line 307 "parser.y"
    {printrule("block"); scope++;;}
    break;

  case 78:
#line 307 "parser.y"
    {hide_scope(scope--);(yyval.stmtVal)=(yyvsp[(3) - (4)].stmtVal);;}
    break;

  case 79:
#line 308 "parser.y"
    {printrule("block -> ε");(yyval.stmtVal) = make_stmt();;}
    break;

  case 80:
#line 311 "parser.y"
    {printrule("funcname -> id");(yyval.strVal) = (yyvsp[(1) - (1)].strVal);;}
    break;

  case 81:
#line 312 "parser.y"
    {printrule("funcname -> ε");(yyval.strVal) = newhidfuncname();;}
    break;

  case 82:
#line 316 "parser.y"
    {
                    printrule("funcprefix");
                    if (check_funcdef((yyvsp[(2) - (2)].strVal))) {
                        (yyval.symVal) = new_func(strdup((yyvsp[(2) - (2)].strVal)), USERFUNC_T, NULL);
                        (yyval.symVal)->value.funcVal->iaddress = nextquadlabel();
                        emit_jump();
                        emit(funcstart, lvalue_expr((yyval.symVal)), NULL, NULL);
                        push_stack(offsetStack, create_stack_node(currscopeoffset()));
                        // fprintf(stdout,"PUSHING OFFSET %d\n",currscopeoffset());
                        enter_scopespace();
                        resetformalargsoffset();
                        inFunction++;
                    }
                    else {
                        (yyval.symVal) = NULL;
                    }
                ;}
    break;

  case 83:
#line 335 "parser.y"
    {printrule("idlist -> empty");(yyval.varlistVal) = NULL;;}
    break;

  case 84:
#line 336 "parser.y"
    {printrule("idlist -> ID");(yyval.varlistVal) = handle_idlist_single((yyvsp[(1) - (1)].strVal));;}
    break;

  case 85:
#line 337 "parser.y"
    {printrule("idlist -> idlist, ID");(yyval.varlistVal) = handle_idlist_multiple((yyvsp[(1) - (3)].varlistVal), (yyvsp[(3) - (3)].strVal));;}
    break;

  case 86:
#line 341 "parser.y"
    {
                printrule("funcargs");
                enter_scopespace();
                resetfunctionlocalsoffset();
                (yyval.varlistVal) = (yyvsp[(2) - (3)].varlistVal);
            ;}
    break;

  case 87:
#line 349 "parser.y"
    {push_loopcounter();;}
    break;

  case 88:
#line 350 "parser.y"
    {pop_loopcounter();;}
    break;

  case 89:
#line 353 "parser.y"
    {
                printrule("funcbody");
                (yyval.uintVal) = currscopeoffset();
                patchlist((yyvsp[(2) - (3)].stmtVal)->returnlist, nextquadlabel());
                exit_scopespace();
            ;}
    break;

  case 90:
#line 362 "parser.y"
    {
                if ((yyvsp[(1) - (3)].symVal) != NULL) {
                    printrule("funcdef");
                    inFunction--;
                    exit_scopespace();

                    (yyvsp[(1) - (3)].symVal)->value.funcVal->total_locals = (yyvsp[(3) - (3)].uintVal);
                    unsigned prev_offset = pop_stack(offsetStack);
                    // fprintf(stdout,"GOT OFFSET %d\n",prev_offset);
                    (yyvsp[(1) - (3)].symVal)->value.funcVal->arguments = (yyvsp[(2) - (3)].varlistVal);

                    // restore_curr_scope_offset(prev_offset);
                    emit(funcend, lvalue_expr((yyvsp[(1) - (3)].symVal)), NULL, NULL);

                    patchlabel((yyvsp[(1) - (3)].symVal)->value.funcVal->iaddress, nextquadlabel());
                }
                (yyval.symVal) = (yyvsp[(1) - (3)].symVal);
            ;}
    break;

  case 91:
#line 383 "parser.y"
    {printrule("real number");(yyval.exprVal) = newexpr_constreal((yyvsp[(1) - (1)].realVal));;}
    break;

  case 92:
#line 384 "parser.y"
    {printrule("int number");(yyval.exprVal) = newexpr_constint((yyvsp[(1) - (1)].intVal));;}
    break;

  case 93:
#line 387 "parser.y"
    {(yyval.exprVal) = newexpr_conststring((yyvsp[(1) - (1)].strVal));;}
    break;

  case 94:
#line 388 "parser.y"
    {(yyval.exprVal) = (yyvsp[(1) - (1)].exprVal);;}
    break;

  case 95:
#line 389 "parser.y"
    {(yyval.exprVal) = newexpr_constbool(1);;}
    break;

  case 96:
#line 390 "parser.y"
    {(yyval.exprVal) = newexpr_constbool(0);;}
    break;

  case 97:
#line 391 "parser.y"
    {(yyval.exprVal) = newexpr(nil_e);;}
    break;

  case 98:
#line 395 "parser.y"
    {
                printrule("ifprefix");
                (yyvsp[(3) - (4)].exprVal) = short_circuit((yyvsp[(3) - (4)].exprVal));
                emit_l(if_eq, newexpr_constbool(1), (yyvsp[(3) - (4)].exprVal), NULL, nextquadlabel()+2);
                (yyval.uintVal) = nextquadlabel();
                emit_jump();
            ;}
    break;

  case 99:
#line 405 "parser.y"
    {
                printrule("elseprefix");
                (yyval.uintVal) = nextquadlabel();
                emit_jump();
            ;}
    break;

  case 100:
#line 412 "parser.y"
    {
            printrule("ifstmt -> if");
            patchlabel((yyvsp[(1) - (2)].uintVal), nextquadlabel());
            (yyval.stmtVal) = (yyvsp[(2) - (2)].stmtVal);
        ;}
    break;

  case 101:
#line 417 "parser.y"
    {
            printrule("ifstmt -> ifelse");
            patchlabel((yyvsp[(1) - (4)].uintVal), (yyvsp[(3) - (4)].uintVal) + 1);
            patchlabel((yyvsp[(3) - (4)].uintVal), nextquadlabel());

            (yyval.stmtVal) = make_stmt();
            (yyval.stmtVal)->breaklist = mergelist((yyvsp[(2) - (4)].stmtVal)->breaklist, (yyvsp[(4) - (4)].stmtVal)->breaklist);
            (yyval.stmtVal)->contlist = mergelist((yyvsp[(2) - (4)].stmtVal)->contlist, (yyvsp[(4) - (4)].stmtVal)->contlist);
            (yyval.stmtVal)->returnlist = mergelist((yyvsp[(2) - (4)].stmtVal)->returnlist, (yyvsp[(4) - (4)].stmtVal)->returnlist);
        ;}
    break;

  case 102:
#line 429 "parser.y"
    {printrule("loopstart");++loopcounter;;}
    break;

  case 103:
#line 430 "parser.y"
    {printrule("loopend");--loopcounter;;}
    break;

  case 104:
#line 431 "parser.y"
    {(yyval.stmtVal) = (yyvsp[(2) - (3)].stmtVal);;}
    break;

  case 105:
#line 433 "parser.y"
    {(yyval.uintVal) = nextquadlabel();;}
    break;

  case 106:
#line 436 "parser.y"
    {
                printrule("whilecond");
                (yyvsp[(2) - (3)].exprVal) = short_circuit((yyvsp[(2) - (3)].exprVal));
                emit_l(if_eq, (yyvsp[(2) - (3)].exprVal), newexpr_constbool(1), NULL, nextquadlabel()+2);
                (yyval.uintVal) = nextquadlabel();
                emit_jump();
            ;}
    break;

  case 107:
#line 446 "parser.y"
    {
                printrule("whilestmt");
                emit_l(jump, NULL, NULL, NULL, (yyvsp[(1) - (3)].uintVal));
                patchlabel((yyvsp[(2) - (3)].uintVal), nextquadlabel());

                patchlist((yyvsp[(3) - (3)].stmtVal)->breaklist, nextquadlabel());
                patchlist((yyvsp[(3) - (3)].stmtVal)->contlist, (yyvsp[(1) - (3)].uintVal));
                (yyval.stmtVal) = (yyvsp[(3) - (3)].stmtVal);
            ;}
    break;

  case 108:
#line 457 "parser.y"
    {printrule("N");(yyval.uintVal) = nextquadlabel();emit_jump();;}
    break;

  case 109:
#line 459 "parser.y"
    {printrule("M");(yyval.uintVal) = nextquadlabel();;}
    break;

  case 110:
#line 462 "parser.y"
    {
                printrule("forprefix");
                (yyval.forloopVal) = malloc(sizeof(struct forloopStruct));
                (yyval.forloopVal)->test = (yyvsp[(5) - (7)].uintVal);
                (yyvsp[(6) - (7)].exprVal) = short_circuit((yyvsp[(6) - (7)].exprVal));
                (yyval.forloopVal)->enter = nextquadlabel();
                emit_l(if_eq, (yyvsp[(6) - (7)].exprVal), newexpr_constbool(1), NULL, 0);
            ;}
    break;

  case 111:
#line 473 "parser.y"
    {
                printrule("forstmt");
                patchlabel((yyvsp[(1) - (7)].forloopVal)->enter, (yyvsp[(5) - (7)].uintVal)+1);
                patchlabel((yyvsp[(2) - (7)].uintVal), nextquadlabel());
                patchlabel((yyvsp[(5) - (7)].uintVal), (yyvsp[(1) - (7)].forloopVal)->test);
                patchlabel((yyvsp[(7) - (7)].uintVal), (yyvsp[(2) - (7)].uintVal)+1);

                patchlist((yyvsp[(6) - (7)].stmtVal)->breaklist, nextquadlabel());
                patchlist((yyvsp[(6) - (7)].stmtVal)->contlist, (yyvsp[(2) - (7)].uintVal)+1);
                (yyval.stmtVal) = (yyvsp[(6) - (7)].stmtVal);
            ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2448 "parser.c"
      default: break;
    }
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
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
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

  /* Else will try to reuse look-ahead token after shifting the error
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
      if (yyn != YYPACT_NINF)
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

  if (yyn == YYFINAL)
    YYACCEPT;

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

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
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


#line 487 "parser.y"



int main(int argc, char **argv) {
    if (!(alpha_yyin = fopen(argv[1], "r"))) {
        fprintf(stderr, "Cannot open file %s for reading. Exiting.\n", argv[1]);
        return 1;
    }

    if (!(alpha_yyout = fopen("yyout.txt", "w"))) {
    // if (!(alpha_yyout = stdout)) {
        fprintf(stderr, "Cannot open file for writing yacc outputs. ");
        fprintf(stderr, "Reverting to stdout instead.\n");
        alpha_yyout = stdout;
    }


    // if (argc > 2) {
    //     if (!(quadout = fopen(argv[2], "w"))) {
    //         fprintf(stderr, "Cannot open file %s for writing quads. ", argv[2]);
    //         fprintf(stderr, "Reverting to stdout instead.\n");
    //         quadout = stdout;
    //     }
    // } else {
    //     // quadout = stdout;
    // }

    push_loopcounter();

    for (int i = 0; i < 12; i++)
        handle_funcdef_lib(lib_funcs[i]);

    alpha_yyparse();
    fprint_scope_lists(alpha_yyout);
    fprint_symbol_table(alpha_yyout);
    fclose(alpha_yyout);

    quadout = fopen("quads.txt", "w");
    print_quads(quadout);
    fclose(quadout);

    // revert stdout to file named "debugout.txt"
    FILE* debugout = fopen("debugout.txt", "w");
    // FILE* stdout_b = stdout;
    out = stdout;
    stdout = debugout;
    // out = fopen("out.txt", "w");

    generate_target_code();

    instr_out = fopen("tcode.txt", "w");
    print_instructions(instr_out);
    fclose(instr_out);

    avm_initialize();
	while(!executionFinished){
        fprintf(stdout,"EXECUTING INSTRUCTION\n");
		execute_cycle();
	}


    // createbin();
    fclose(out);

    return 0;
}

void alpha_yyerror(const char *msg) {
    fprintf(stderr, "\e[48;2;200;0;0m""error: %s at line %d""\x1b[0m""\n", msg, yyline);
    // exit(1);
}

int yywrap() {
    return 1;
}
