%{
#include<iostream>
#include<cstdlib>
#include<stack>
#include "headers/bnKapi.h"
#include "headers/tokens.h"
#include "headers/node.h"
#include "./codegen/headers/treewalker.h"
#include "./codegen/headers/ir.h"
#include "./codegen/headers/instr.h"
#include "headers/context.h"
#include<list>
#include<vector>

using namespace std;
using namespace yacl::ast;

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
StatementList *stmtList = NULL;
int counter = 0;
int Context::contextIdCounter = 0;
%}

%union{
    yacl::ast::Node *node;
};

%token FUNCTION INTEGER_T DOUBLE_T STRING_T FUNCTION_T OR AND EQUAL LE GE IF ELSE NOT ELIF RETURN ARRAY_T
%token <node> IDENTIFIER
%token <node> STRING
%token <node> INTEGER
%token <node> DOUBLE
%token <node> NOTHING
%token <node> EMPTY

%type <node> program statement statementList variableList variableDeclarations variableDefinition expression atom type
%type <node> functionDefinition returnType formalParameters formalParameterList formalParameterDef functionBody arglist arguments functCall
%type <node> block conditionalExpression orExp andExp equality relationalOp term power unary elseBlock list indexOp valueList

%%
program: statementList {
                          programAST = CAST_TO( StatementList, $1 );
                          if( programAST != NULL ){
                            $$ = $1;
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

         | functionDefinition      {
                                      $$ = $1;
                                   }         
         | IF '(' conditionalExpression ')' block elseBlock {   // right now else block is compulsory,
                                                                // because it is not yet decided, whether to make if an expression or a 
                                                                // statement, if it becomes a statement, then else will be 
                                                                // optional
                                                                Operands *operands = new Operands();
                                                                operands->push_back( $3 );
                                                                operands->push_back( $5 );
                                                                operands->push_back( $6 );
                                                                Operator *ifNode = new Operator( __if, 3, operands );
                                                                $$ = ifNode;
                                                            }
         | RETURN expression ';'   {
                                        Operands *operands = new Operands();
                                        operands->push_back( $2 );
                                        Operator *returnNode = new Operator( __return, 1, operands );
                                        $$ = returnNode;
                                   }
         | expression ';'          { $$ = $1; }
         ;

elseBlock: ELSE block  { 
                            Operands *operands = new Operands();
                            operands->push_back( $2 );
                            Operator *elseNode = new Operator( __else, 1, operands );
                            $$ = elseNode;
                       }
         | ELIF '(' conditionalExpression ')' block elseBlock {
                                                                    Operands *operands = new Operands();
                                                                    operands->push_back( $3 );
                                                                    operands->push_back( $5 );
                                                                    operands->push_back( $6 );
                                                                    Operator *elifNode = new Operator( __elif, 3, operands );
                                                                    $$ = elifNode;
                                                              }
         ;
block : statement                              {  $$ = $1; }
      | '{' statementList '}'                  {  $$ = $2; }
      ;

conditionalExpression: orExp                   { $$ = $1; }
                     ;

orExp : andExp                                 { $$ = $1; }
      | orExp OR andExp                        {
                                                  Operands *operands = new Operands();
                                                  operands->push_back( $1 );
                                                  operands->push_back( $3 );
                                                  Operator *orExpNode = new Operator( __or, 2, operands );
                                                  $$ = orExpNode;
                                               }
      ;

andExp: equality                               { $$ = $1; }
      | andExp AND equality                    {
                                                  Operands *operands = new Operands();
                                                  operands->push_back( $1 );
                                                  operands->push_back( $3 );
                                                  Operator *andNode = new Operator( __and, 2, operands );
                                                  $$ = andNode;
                                               }
      ;

equality: relationalOp                         {  $$ = $1; }
        | equality EQUAL relationalOp          { 
                                                  Operands *operands = new Operands();
                                                  operands->push_back( $1 );
                                                  operands->push_back( $3 );
                                                  Operator *equality = new Operator( __equality, 2, operands );
                                                  $$ = equality;
                                               }
        ;

relationalOp: expression '<' expression        {
                                                  Operands *operands = new Operands();
                                                  operands->push_back( $1 );
                                                  operands->push_back( $3 );
                                                  Operator *ltRelOpNode = new Operator( __lt, 2, operands );
                                                  $$ = ltRelOpNode;
                                               }
            | expression LE expression         {
                                                  Operands *operands = new Operands();
                                                  operands->push_back( $1 );
                                                  operands->push_back( $3 );
                                                  Operator *leRelOpNode = new Operator( __le, 2, operands );
                                                  $$ = leRelOpNode;
                                               }
            | expression '>' expression        {
                                                  Operands *operands = new Operands();
                                                  operands->push_back( $1 );
                                                  operands->push_back( $3 );
                                                  Operator *gtRelOpNode = new Operator( __gt, 2, operands );
                                                  $$ = gtRelOpNode;
                                               }
            | expression GE expression         {
                                                  Operands *operands = new Operands();
                                                  operands->push_back( $1 );
                                                  operands->push_back( $3 );
                                                  Operator *geRelOpNode = new Operator( __ge, 2, operands );
                                                  $$ = geRelOpNode;
                                               }
            | expression                       { $$ = $1; }
            ;


functionDefinition: FUNCTION IDENTIFIER '(' formalParameters ')' ':' returnType functionBody {
                                                                                                Operands *operands = new Operands();
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
                                                              Operands *operands = new Operands();
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
                                                   }

            | variableList ',' variableDeclarations {
                                                         VariableList *vlist = CAST_TO( VariableList, $1 );
                                                         if( vlist != NULL ){
                                                            vlist->push_back( $3 );
                                                         }
                                                         $$ = vlist;
                                                    }
            ;

variableDeclarations: IDENTIFIER '=' expression {
                                                    Operands *operands = new Operands();
                                                    operands->push_back(NULL);
                                                    operands->push_back($1);
                                                    operands->push_back($3);
                                                    Operator *node = new Operator(__assignment, 3, operands);
                                                    $$ = node;
                                                }
                    ;

expression: expression '+' term           {
                                              Operands *operands = new Operands();
                                              operands->push_back( $1 );
                                              operands->push_back( $3 );
                                              Operator *plusNode = new Operator( __addition, 2, operands );
                                              $$ = plusNode;
                                          }
          | expression '-' term           {
                                              Operands *operands = new Operands();
                                              operands->push_back( $1 );
                                              operands->push_back( $3 );
                                              Operator *subtractionNode = new Operator( __subtraction, 2, operands );
                                              $$ = subtractionNode;
                                          }
          | term                          { $$ = $1; }
          ;

term: term '*' power                     {
                                              Operands *operands = new Operands();
                                              operands->push_back( $1 );
                                              operands->push_back( $3 );
                                              Operator *multiplicationNode = new Operator( __multiplication, 2, operands );
                                              $$ = multiplicationNode;
                                          }
    | term '/' power                      {
                                              Operands *operands = new Operands();
                                              operands->push_back( $1 );
                                              operands->push_back($3);
                                              Operator *divNode = new Operator( __div, 2, operands );
                                              $$ = divNode;
                                          }
    | power                               { $$ = $1; }
    ;

power : power '^' unary                     {
                                              Operands *operands = new Operands();
                                              operands->push_back( $1 );
                                              operands->push_back( $3 );
                                              Operator *powerNode = new Operator( __power, 2, operands );
                                              $$ = powerNode;
                                          }
      | unary                             { $$ = $1; }
      ;

unary: NOT unary                          {
                                              Operands *operands = new Operands();
                                              operands->push_back( $2 );
                                              Operator *notNode = new Operator( __not, 1, operands );
                                              $$ = notNode;
                                          }
     | '-' unary                          {
                                              Operands *operands = new Operands();
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
      | list          { $$ = $1; }
      | indexOp       { $$ = $1; }
      | '(' conditionalExpression ')'  { $$ = $2; }

empty :
      ;

type : INTEGER_T  {  $$ = new Type(__integer, 8 ); }
     | DOUBLE_T   {  $$ = new Type(__double, 8 );  }
     | STRING_T   {  $$ = new Type(__string, 0 );  }
     | FUNCTION_T {  $$ = new Type(__function_t, 0); }
     | NOTHING    {  $$ = new Type(__nothing, 0); }
     | ARRAY_T    {  $$ = new Type(__array_t, 0); }
     ;

functCall : IDENTIFIER '(' arguments ')'  {
                                              Operands *operands = new Operands();
                                              operands->push_back( $1 );
                                              if( $3 != NULL ){
                                                  operands->push_back( $3 );
                                              }
                                              Operator *functCall = new Operator( __funct_call, 2, operands );
                                              $$ = functCall;
                                          }
          ;

arguments : empty                  {
                                      $$ = new ArgumentList();
                                   }
                                   
          | arglist                {  $$ = $1; }
          ;

arglist : expression                 {
                                        ArgumentList *arglist = new ArgumentList();
                                        arglist->push_back( $1 );
                                        $$ = arglist;
                                        //cout<<"Hello...args"<<endl;
                                        //_debugMessage( "In arguments..." );
                                     }

        | arglist ',' expression     {
                                        ArgumentList *arglist = CAST_TO( ArgumentList, $1 );
                                        arglist->push_back( $3 );
                                        $$ = arglist;
                                        //cout<<"Args seen: "<<arglist->getLength()<<endl;
                                     }
        ;

list : '[' valueList ']'   { $$ = $2; }
     ;

valueList : expression               { ValueList *vlist = new ValueList();
                                       vlist->push_back( $1 );
                                       $$ = vlist;
                                     }
                                     
          | valueList ',' expression {
                                        ValueList *vlist = CAST_TO( ValueList, $1 );
                                        if( vlist != NULL ){
                                            vlist->push_back( $3 );
                                        }
                                        $$ = vlist;
                                     }
          ;
indexOp : IDENTIFIER '[' INTEGER ']' {
                                        Operands *operands = new Operands();
                                        operands->push_back( $1 );
                                        operands->push_back( $3 );
                                        Operator *arrayReadOp = new Operator( __indexOp, 2, operands );
                                        $$ = arrayReadOp;
                                     }
        ;
%%

void yyerror( const char* error ){
    cout<<"Error: "<<error<<endl;
}

int main(){   
    yyparse();
    Context *ctx = new Context();
    TreeWalker treewalker;
    int length;
    length = programAST->getLength();
    ctx->addInstruction(new Push(push, ctx->getRegister(rbp)));
    ctx->addInstruction(new Move(mov, ctx->getRegister(rsp), NULL, ctx->getRegister(rbp)));    
    //cout<<"Parsing done.."<<endl;
    for( int i = 0; i < length; i++ ){
      if( !programAST->empty() ){
        treewalker.evaluate( programAST->get(i), ctx, NULL );
      }
    }
    cout<<treewalker.pre();
    vector<Context*>* contexts = treewalker.getContexts();
    //contexts->push_back(ctx);
    for(int i = 0, len = contexts->size(); i < len; i++){
        (*contexts)[i]->generateCode();
    }
    cout<<treewalker.post();
    ctx->generateCode(true, true);
    cout<<treewalker.end();
    return 0;
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
