%{
#include<iostream>
#include<cstdlib>
#include<cstring>
#include "nodes/node.h"
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
