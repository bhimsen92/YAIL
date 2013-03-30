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
     OR = 263,
     AND = 264,
     EQUAL = 265,
     LE = 266,
     GE = 267,
     IF = 268,
     ELSE = 269,
     NOT = 270,
     ELIF = 271,
     RETURN = 272,
     ARRAY_T = 273,
     IDENTIFIER = 274,
     STRING = 275,
     INTEGER = 276,
     DOUBLE = 277,
     NOTHING = 278,
     EMPTY = 279
   };
#endif
/* Tokens.  */
#define FUNCTION 258
#define INTEGER_T 259
#define DOUBLE_T 260
#define STRING_T 261
#define FUNCTION_T 262
#define OR 263
#define AND 264
#define EQUAL 265
#define LE 266
#define GE 267
#define IF 268
#define ELSE 269
#define NOT 270
#define ELIF 271
#define RETURN 272
#define ARRAY_T 273
#define IDENTIFIER 274
#define STRING 275
#define INTEGER 276
#define DOUBLE 277
#define NOTHING 278
#define EMPTY 279




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 33 "parser.yacc"

    yacl::ast::Node *node;



/* Line 2068 of yacc.c  */
#line 104 "y.tab.h"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


