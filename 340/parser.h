/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

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
/* Line 1529 of yacc.c.  */
#line 159 "parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE alpha_yylval;

