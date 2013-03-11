%{
#include<iostream>
#include<cstdlib>
#include<cstring>
#include "./headers/node.h"
#include "y.tab.h"
using namespace std;
using namespace bnk_astNodes;

%}
newline    \n
digit      [0-9]
character  [a-zA-Z_]
digits     {digit}+
realVal    {digit}*\.{digits}
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
           
"elif"     {
                return ELIF;
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
                      Node *nothingNode = new bnk_astNodes::Nothing();
                      yylval.node = nothingNode;
                      return NOTHING;
                  }

"<="       {
                return LE;
           }

">="       {
                return GE;
           }
           
"=="       {
                return EQUAL;
           }
           
{ident}    {
                Node *ident = new Identifier( yytext );
                yylval.node = ident;
                return IDENTIFIER;
           }
           
{realVal}  {
                Node *realVal = new Double( yytext );
                yylval.node = realVal;
                return DOUBLE;
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
