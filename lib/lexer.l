%{
#include<iostream>
#include<cstdlib>
#include<cstring>
#include "nodes/node.h"
#include "y.tab.h"
using namespace std;

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
           
"spawn"    {
                return SPAWN;
           }
           
"sync"     {
                return SYNC;
           }
           
{string}   {
                Node *string = new String( yytext );
                yylval.node = string;
                return STRING;                
           }
           
{ident}    {
                Node *ident = new Identifier( yytext );
                yylval.node = ident;
                return IDENT;
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
