%{
#include<iostream>
#include<cstdlib>
#include<stack>
#include "bnKapi.h"
#include "nodes/tokens.h"
#include "nodes/node.h"
#include "interpreter.h"
#include "context.h"
#include "types/object.h"
#include "types/number.h"

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

//ParameterList *plist = NULL;
//FunctionCall  *fcall = NULL;
StatementList *stmtList = NULL;
//ArgumentList  *argList = NULL;
int counter = 0;

%}

%union{
    bnk_astNodes::Node *node;
};

%token FUNCTION NOTHING EMPTY INTEGER_T DOUBLE_T STRING_T
%token <node> IDENTIFIER
%token <node> STRING
%token <node> INTEGER
%token <node> DOUBLE

%type <node> program statement statementList variableList variableDeclarations variableDefinition expression atom type
%%
program: statementList {
                          programAST = CAST_TO( StatementList, $1 );
                          if( programAST != NULL ){
                            $$ = $1;
                            _debugMessage( "ParsingDone....:)" );
                          }
                       }
       ;
statementList: empty                   {
                                            stmtList = new StatementList();
                                            $$ = stmtList;
                                       }
             | statementList statement {
                                            stmtList = CAST_TO( StatementList, $1 );
                                            if( stmtList != NULL ){
                                              stmtList->push_back( $2 );
                                            }                 
                                            $$ = stmtList;
                                       }
             ;

statement: variableDefinition ';'  {
                                      $$ = $1;
                                      removeType();
                                   }
         ;

variableDefinition: type { putType( $1->getType() ); } variableList {
                                                              list<Node*> *operands = new list<Node*>();
                                                              operands->push_back( $1 );
                                                              operands->push_back( $3 );
                                                              Operator *vDefinitionNode = new Operator( __var_definition, 2, operands );
                                                              $$ = vDefinitionNode;
                                                         }
                  ;

variableList: variableDeclarations                 {
                                                        VariableList *vlist = new VariableList( -1 );
                                                        vlist->push_back( $1 );
                                                        $$ = vlist;
                                                        //_debugMessage( "here..." );
                                                   }

            | variableList ',' variableDeclarations {
                                                         //_debugMessage( "good" );
                                                         VariableList *vlist = CAST_TO( VariableList, $1 );
                                                         if( vlist != NULL ){
                                                            vlist->push_back( $3 );
                                                         }
                                                         $$ = vlist;
                                                    }
            ;

variableDeclarations: IDENTIFIER '=' expression {
                                                    //Identifier *id = CAST_TO( Identifier, $1 );
                                                    //_debugMessage( id->getName() );
                                                    list<Node*> *operands = new list<Node*>();
                                                    operands->push_back( new Type( getType() ) );
                                                    operands->push_back( $1 );
                                                    operands->push_back( $3 );
                                                    Operator *node = new Operator( __assignment, 3, operands );
                                                    //_debugMessage( "seen vardecl" );
                                                    $$ = node;
                                                }
                    ;

expression: atom      {
                          $$ = new Expression( $1 );
                      }
          ;

atom  : IDENTIFIER    { $$ = $1; }
      | INTEGER       { $$ = $1; }
      | DOUBLE        { ; }
      | STRING        { $$ = $1; }
      | NOTHING       { ; }
      | EMPTY         { ; }
      | '(' expression ')'  { ; }

empty:
     ;

type: INTEGER_T {  $$ = new Type( __integer_t ); }
    | DOUBLE_T  {  $$ = new Type( __double_t );  }    
    | STRING_T  {  $$ = new Type( __string_t );  }
    ;
%%

void yyerror( const char* error ){
    cout<<"Error: "<<error<<endl;
}

int main(){   
    yyparse();
    Context *ctx = new Context();
    Interpreter interp;
    int length;
    //cout<< "length of statement list: "<< programAST->getLength()<<endl;
    length = programAST->getLength();
    for( int i = 0; i < length; i++ ){
      if( !programAST->empty() ){
        interp.evaluate( programAST->pop_front(), ctx, -1 );
      }
    }
    bnk_types::Object *val = ctx->get( string("b") );
    bnk_types::Integer *i = CAST_TO( bnk_types::Integer, val );
    if( i != NULL )
      cout<<"value b: "<<i->getValue()<<endl;
    return 0;
}

void _debugMessage( const char* str ){
    cout<<str<<endl;
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