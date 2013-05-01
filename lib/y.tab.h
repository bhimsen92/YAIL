/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
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
     SPAWN = 274,
     SYNC = 275,
     IDENTIFIER = 276,
     STRING = 277,
     INTEGER = 278,
     DOUBLE = 279,
     NOTHING = 280,
     EMPTY = 281
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
#define SPAWN 274
#define SYNC 275
#define IDENTIFIER 276
#define STRING 277
#define INTEGER 278
#define DOUBLE 279
#define NOTHING 280
#define EMPTY 281




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 35 "parser.yacc"

    bnk_astNodes::Node *node;



/* Line 2068 of yacc.c  */
#line 108 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


