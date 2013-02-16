%{
#include<iostream>
#include<cstdlib>
#include "bnKapi.h"
#include "nodes/tokens.h"
#include "nodes/node.h"
#include "context.h"
#include "interpreter.h"
#include<list>
using namespace std;

extern int yylex();
extern void yyerror(const char*);
extern int yyparse();

void _debugMessage( const char* );

StatementList *programAST;
list<StatementList*> statementStack;

ParameterList *plist = NULL;
FunctionCall  *fcall = NULL;
StatementList *stmtList = NULL;
ArgumentList  *argList = NULL;
int counter = 0;

%}

%union{
    Node *node;
};

%type <node> statementList params arglist
%type <node> expr funct_call factor statement

%token FUNCTION 
%token <node> IDENT
%token SPAWN
%token <node> STRING
%token <node> NUMBER
%token SYNC

%%

program: statementList { StatementList *programAST = CAST_TO( StatementList, $1 );
                        /*if( ptr != NULL ){
                            cout<< "Length of the statment list is: "<<programAST->getLength()<<endl;
                            Operator *spawnNode = CAST_TO( Operator, programAST->get(2) );
                            if( spawnNode != NULL ){
                                cout<<"spawn_node: "<<spawnNode->getOperands()->size()<<endl;
                            }
                            else{
                                String *string = CAST_TO( String, programAST->get(0) );
                                if( string != NULL ){
                                    cout<<"string: "<<string->getString()<<endl;
                                }   
                            }
                        //}*/
                       }
       ;
statementList: statement {
                            if( stmtList == NULL ){
                                stmtList = new StatementList();
                            }
                            stmtList->push($1);
                            $$ = stmtList;
                            //_debugMessage("i am on fire");
                         }
             | statementList statement {
                                            StatementList *slist = CAST_TO( StatementList, $1 );
                                            if( slist != NULL ){
                                                slist->push($2);
                                                $$ = slist;
                                            }
                                       }
             ;

statement : funct_def { ; }
          | SPAWN funct_call ';' {
                                        //create an operator node of type spawn.
                                        list<Node*> *operands = new list<Node*>();
                                        operands->push_back($2);
                                        Node *spawnNode = new Operator( __spawn, 1, operands );
                                        $$ = spawnNode;
                                 }
          | SYNC ';' {
                          Node *syncNode = new Operator(  __sync, 0, NULL );
                          $$ = syncNode;
                     }
          | expr ';' { $$ = $1; }
          ;

funct_def : FUNCTION IDENT '(' arglist ')' '{' statementList '}' {
                                                                 }
          ;

arglist : /*empty*/ { ; }
        | IDENT     { ; }
        | arglist ',' IDENT {;}
        ;
        
expr : funct_call  { $$ = $1; }
     | factor   {;}
     ;

funct_call : IDENT '(' params ')'  {
                                        list<Node*> *operands = new list<Node*>();
                                        // store the operands.
                                        operands->push_back($1);
                                        operands->push_back($3);
                                        // create a OperatorNode with FUNCT_CALL as type.
                                        Node* functCallNode = new Operator( __funct_call, 2, operands );
                                        // return.
                                        $$ = functCallNode;
                                        //_debugMessage("seen functioncall" );
                                   }
           ;

params: /*empty*/ {  
                     if( plist != NULL ){
                        plist->clear();
                        plist = NULL;
                     }
                     //_debugMessage("hello world, there");
                     plist = new ParameterList();
                     $$ = plist;
                     //_debugMessage("seen empty paralist");
                  }
      | expr      {
                      if( plist == NULL ){
                        plist = new ParameterList();
                        $$ = plist;
                        //_debugMessage( "i hate bugs.." );
                      }
                      //_debugMessage("working..");
                      ParameterList *paraList = CAST_TO( ParameterList, $$ );
                      if( paraList != NULL ){
                          paraList->push($1);
                      }
                      $$ = paraList;
                      //_debugMessage("seen first para");
                  }
      | params ',' expr {
                            ParameterList *paraList = CAST_TO( ParameterList, $1 );
                            if( paraList != NULL ){
                                paraList->push($3);
                                $$ = paraList;
                            }
                            //_debugMessage("seeing multiple paras");
                        }
      ;

factor : IDENT   { $$ = $1; }
       | NUMBER  { $$ = $1; }
       | STRING  { $$ = $1; }
       ;
%%

void yyerror( const char* error ){
    cout<<"Error: "<<error<<endl;
}

int main(){   
    yyparse();
    // parsing done.
    cout<<"Parsing complete.."<<endl;
    Context *ctx = new Context();
    Interpreter *iterp = new Interpreter( ctx );
    iterp->evaluate( programAST );
    return 0;
}

void _debugMessage( const char* str ){
    cout<<str<<endl;
}
