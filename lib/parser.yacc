%{
#include<iostream>
#include<cstdlib>
#include<stack>
#include "headers/bnKapi.h"
#include "headers/tokens.h"
#include "headers/node.h"
#include "headers/interpreter.h"
#include "headers/context.h"
#include "headers/object.h"
#include "headers/number.h"

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

%token FUNCTION INTEGER_T DOUBLE_T STRING_T FUNCTION_T OR AND EQUAL LE GE IF ELSE NOT
%token <node> IDENTIFIER
%token <node> STRING
%token <node> INTEGER
%token <node> DOUBLE
%token <node> NOTHING
%token <node> EMPTY

%type <node> program statement statementList variableList variableDeclarations variableDefinition expression atom type
%type <node> functionDefinition returnType formalParameters formalParameterList formalParameterDef functionBody arglist arguments functCall
%type <node> block conditionalExpression orExp andExp equality relationalOp term power unary

%%
program: statementList {
                          programAST = CAST_TO( StatementList, $1 );
                          if( programAST != NULL ){
                            $$ = $1;
                            //_debugMessage( "ParsingDone....:)" );
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
                                      //_debugMessage( "In statement..." );
                                      $$ = $1;
                                      removeType();
                                   }

         | functionDefinition      {
                                      $$ = $1;
                                   }         
         | IF '(' conditionalExpression ')' block                 {
                                                                      list<Node*> *operands = new list<Node*>();
                                                                      operands->push_back( $3 );
                                                                      operands->push_back( $5 );
                                                                      Operator *ifNode = new Operator( __if, 2, operands );
                                                                      $$ = ifNode;
                                                                  }
         | IF '(' conditionalExpression ')' block ELSE block      {
                                                                      list<Node*> *operands = new list<Node*>();
                                                                      operands->push_back( $3 );
                                                                      operands->push_back( $5 );
                                                                      operands->push_back( $7 );
                                                                      Operator *ifElseNode = new Operator( __ifelse, 3, operands );
                                                                      $$ = ifElseNode;
                                                                  }
         | expression ';'          { $$ = $1; }
         ;

block : statement                              {  $$ = $1; }
      | '{' statementList '}'                  {  $$ = $2; }
      ;

conditionalExpression: orExp                   { $$ = $1; }
                     ;

orExp : andExp                                 { $$ = $1; }
      | orExp OR andExp                        {
                                                  list<Node*> *operands = new list<Node*>();
                                                  operands->push_back( $1 );
                                                  operands->push_back( $3 );
                                                  Operator *orExpNode = new Operator( __or, 2, operands );
                                                  $$ = orExpNode;
                                               }
      ;

andExp: equality                               { $$ = $1; }
      | andExp AND equality                    {
                                                  list<Node*> *operands = new list<Node*>();
                                                  operands->push_back( $1 );
                                                  operands->push_back( $3 );
                                                  Operator *andNode = new Operator( __and, 2, operands );
                                                  $$ = andNode;
                                               }
      ;

equality: relationalOp                         {  $$ = $1; }
        | equality EQUAL relationalOp          { 
                                                  list<Node*> *operands = new list<Node*>();
                                                  operands->push_back( $1 );
                                                  operands->push_back( $3 );
                                                  Operator *equality = new Operator( __equality, 2, operands );
                                                  $$ = equality;
                                               }
        ;

relationalOp: expression '<' expression        {
                                                  list<Node*> *operands = new list<Node*>();
                                                  operands->push_back( $1 );
                                                  operands->push_back( $3 );
                                                  Operator *ltRelOpNode = new Operator( __lt, 2, operands );
                                                  $$ = ltRelOpNode;
                                               }
            | expression LE expression         {
                                                  list<Node*> *operands = new list<Node*>();
                                                  operands->push_back( $1 );
                                                  operands->push_back( $3 );
                                                  Operator *leRelOpNode = new Operator( __le, 2, operands );
                                                  $$ = leRelOpNode;
                                               }
            | expression '>' expression        {
                                                  list<Node*> *operands = new list<Node*>();
                                                  operands->push_back( $1 );
                                                  operands->push_back( $3 );
                                                  Operator *gtRelOpNode = new Operator( __gt, 2, operands );
                                                  $$ = gtRelOpNode;
                                               }
            | expression GE expression         {
                                                  list<Node*> *operands = new list<Node*>();
                                                  operands->push_back( $1 );
                                                  operands->push_back( $3 );
                                                  Operator *geRelOpNode = new Operator( __ge, 2, operands );
                                                  $$ = geRelOpNode;
                                               }
            | expression                       { $$ = $1; }
            ;


functionDefinition: FUNCTION IDENTIFIER '(' formalParameters ')' ':' returnType functionBody {
                                                                                                list<Node*> *operands = new list<Node*>();
                                                                                                operands->push_back( $2 );
                                                                                                operands->push_back( $4 );
                                                                                                operands->push_back( $7 );
                                                                                                operands->push_back( $8 );
                                                                                                Operator *functDef = new Operator( __funct_def, 4, operands );
                                                                                                $$ = functDef;
                                                                                             }
                  ;

returnType : type { $$ = $1; }
           ;

functionBody : '{' statementList '}' { $$ = $2; }
             ;
formalParameters : empty                   { $$ = new FormalParameterList(); }
                 | formalParameterList     { $$ = $1;   }
                 ;

formalParameterList : formalParameterDef                        {
                                                                   FormalParameterList *fpList = new FormalParameterList();
                                                                   fpList->push_back( $1 );
                                                                   $$ = fpList;
                                                                }
                    | formalParameterList ',' formalParameterDef {
                                                                    FormalParameterList *fpList = CAST_TO( FormalParameterList, $1 );
                                                                    if( fpList != NULL ){
                                                                      fpList->push_back( $3 );
                                                                    }                                            
                                                                    $$ = fpList;
                                                                 }
                    ;

formalParameterDef : type IDENTIFIER    {
                                            FormalParameter *fParameter = new FormalParameter( $1, $2 );
                                            $$ = fParameter;
                                        }
                   ;

variableDefinition: type { putType( $1->getType() ); } variableList {
                                                              list<Node*> *operands = new list<Node*>();
                                                              operands->push_back( $1 );
                                                              operands->push_back( $3 );
                                                              Operator *vDefinitionNode = new Operator( __var_definition, 2, operands );
                                                              removeType();
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
                                                    list<Node*> *operands = new list<Node*>();
                                                    operands->push_back( new Type( getType() ) );
                                                    operands->push_back( $1 );
                                                    operands->push_back( $3 );
                                                    Operator *node = new Operator( __assignment, 3, operands );
                                                    $$ = node;
                                                }
                    ;

expression: expression '+' term           {
                                              list<Node*> *operands = new list<Node*>();
                                              operands->push_back( $1 );
                                              operands->push_back( $3 );
                                              Operator *plusNode = new Operator( __addition, 2, operands );
                                              $$ = plusNode;
                                          }
          | expression '-' term           {
                                              list<Node*> *operands = new list<Node*>();
                                              operands->push_back( $1 );
                                              operands->push_back( $3 );
                                              Operator *subtractionNode = new Operator( __subtraction, 2, operands );
                                              $$ = subtractionNode;
                                          }
          | term                          { $$ = $1; }
          ;

term: term '*' power                     {
                                              list<Node*> *operands = new list<Node*>();
                                              operands->push_back( $1 );
                                              operands->push_back( $3 );
                                              Operator *multiplicationNode = new Operator( __multiplication, 2, operands );
                                              $$ = multiplicationNode;
                                          }
    | term '/' power                      {
                                              list<Node*> *operands = new list<Node*>();
                                              operands->push_back( $1 );
                                              operands->push_back( $3 );
                                              Operator *divNode = new Operator( __div, 2, operands );
                                              $$ = divNode;
                                          }
    | power                               { $$ = $1; }
    ;

power : power '^' unary                     {
                                              list<Node*> *operands = new list<Node*>();
                                              operands->push_back( $1 );
                                              operands->push_back( $3 );
                                              Operator *powerNode = new Operator( __power, 2, operands );
                                              $$ = powerNode;
                                          }
      | unary                             { $$ = $1; }
      ;

unary: NOT unary                          {
                                              list<Node*> *operands = new list<Node*>();
                                              operands->push_back( $2 );
                                              Operator *notNode = new Operator( __not, 1, operands );
                                              $$ = notNode;
                                          }
     | '-' unary                          {
                                              list<Node*> *operands = new list<Node*>();
                                              operands->push_back( $2 );
                                              Operator *uMinusNode = new Operator( __uminus, 1, operands );
                                              $$ = uMinusNode;
                                          }
     | atom                               { $$ = $1; }
     ;

atom  : IDENTIFIER    { $$ = $1; }
      | INTEGER       { $$ = $1; }
      | DOUBLE        { $$ = $1; }
      | STRING        { $$ = $1; }
      | NOTHING       { $$ = $1; }
      | EMPTY         { $$ = $1; }
      | functCall     { $$ = $1; }
      | '(' conditionalExpression ')'  { $$ = $2; }

empty :
      ;

type : INTEGER_T  {  $$ = new Type( __integer_t ); }
     | DOUBLE_T   {  $$ = new Type( __double_t );  }    
     | STRING_T   {  $$ = new Type( __string_t );  }
     | FUNCTION_T { $$ = new Type( __function_t ); }
     ;

functCall : IDENTIFIER '(' arguments ')'  {
                                              list<Node*> *operands = new list<Node*>();
                                              operands->push_back( $1 );
                                              if( $3 != NULL ){
                                                  operands->push_back( $3 );
                                              }
                                              Operator *functCall = new Operator( __funct_call, 2, operands );
                                              $$ = functCall;
                                              //_debugMessage( "saw function call, all is well..." );
                                          }
          ;

arguments : empty                  {
                                      $$ = NULL;
                                   }
                                   
          | arglist                {  $$ = $1; }
          ;

arglist : expression                 {
                                        ArgumentList *arglist = new ArgumentList();
                                        arglist->push_back( $1 );
                                        $$ = $1;
                                        //_debugMessage( "In arguments..." );
                                     }

        | arglist ',' expression     {                                          
                                        ArgumentList *arglist = CAST_TO( ArgumentList, $1 );
                                        arglist->push_back( $3 );
                                        $$ = arglist;  
                                     }
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
    /*bnk_types::Object *val = ctx->get( string("b") );
    bnk_types::Integer *i = CAST_TO( bnk_types::Integer, val );
    if( i != NULL )
      cout<<"value b: "<<i->getValue()<<endl;*/
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
