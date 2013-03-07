%{
#include<iostream>
#include<cstdlib>
#include<cstring>
#include "headers/node.h"
#include "y.tab.h"
using namespace std;
using namespace bnk_astNodes;

%}
newline    \n
digit      [0-9]
character  [a-zA-Z_]
digits     {digit}+
word       {character}+
ident      {character}({character}|{digit})*
whiteSpace [\n\t ]*
comment    "#"(.*)\n
string     \"(.*)\"
%%
"function" {
                return FUNCTION;
           }
"Int"      {
                return INTEGER_T;
           }

"Double"   {
                return DOUBLE_T;
           }

"String"   {
                return STRING_T;
           }

"Function" {
                return FUNCTION_T;
           }

"if"       {
                return IF;
           }

"else"     {
                return ELSE;
           }

"and"      {
                return AND;
           }

"or"       {
                return OR;
           }

"not"      {
                return NOT;
           }

"Nothing"         {
                      Node *nothingNode = new Nothing();
                      yylval.node = nothingNode;
                      return NOTHING;
                  }
"EMPTY"    {
                Node *emptyNode = new Empty();
                yylval.node = emptyNode;
                return EMPTY;
           }

"<="       {
                return LE;
           }

">="       {
                return GE;
           }
           
{ident}    {
                Node *ident = new Identifier( yytext );
                yylval.node = ident;
                return IDENTIFIER;
           }

{digits}   {
                Node *integer = new Integer( yytext );
                yylval.node = integer;
                return INTEGER;
           }

{string}   {
                Node *string = new String( yytext );
                yylval.node = string;
                return STRING;                
           }           
           
{whiteSpace} {
                ; /* Ignore */
             }
{comment}  {  
                ; /* Ignore */
           }
            
.          {
                return *yytext;
           }
%%
