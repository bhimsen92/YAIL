#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<cstring>
#include<map>
#include "bnKapi.h"
#include "nodes/node.h"
#include "nodes/tokens.h"
#include "context.h"
#include "types/object.h"
#include "types/string.h"
#include "types/number.h"
#include "types/udf.h"
#include "builtins/builtins.h"

using namespace std;
using namespace bnk_astNodes;
using namespace bnk_builtins;

#ifndef __INTERP
#define __INTERP

class Interpreter{
    private:
            map<string, BuiltInFunction> builtins;
    public:
        Interpreter(){
            this->loadBuiltIns();
        }
        bnk_types::Object* evaluate( Node* astNode, Context* execContext, int dataTypeInfo ){
           int nodeType = astNode->getType();
           switch( nodeType ){
              case __identifier:
                                    break;
              case __string:
                                    bnk_astNodes::String *str;                                    
                                    str = CAST_TO( bnk_astNodes::String, astNode );
                                    if( str != NULL ){
                                      return new bnk_types::String( str->getString() ); 
                                    }
                                    break;
              case __integer:
                                    bnk_astNodes::Integer *integer;
                                    integer = CAST_TO( bnk_astNodes::Integer, astNode );
                                    if( integer != NULL ){
                                      return new bnk_types::Integer( integer->getValue() );
                                    }
                                    break;
              case __var_definition:
                                    /**
                                      VariabeDefinition is made up of variableDeclarations.
                                      iterate over declarations, raise error if type mismatch occurs.
                                    */                                    
                                    int dataType;
                                    Operator *varDefinitionNode;
                                    varDefinitionNode = CAST_TO( Operator, astNode );
                                    if( varDefinitionNode != NULL ){
                                      // get the operands.
                                      list<Node*> *operands = varDefinitionNode->getOperands();
                                      // get the datatype of the operands.
                                      Type *dataTypeNode = CAST_TO( Type, operands->front() );
                                      if( dataTypeNode != NULL ){
                                        dataType = dataTypeNode->getType();
                                      }
                                      // get the variableDeclaration list.
                                      VariableList *vlist = CAST_TO( VariableList, operands->back() );
                                      if( vlist != NULL ){
                                        // go through each variable declarations and evaluate them.
                                        int length = vlist->getLength();                                        
                                        for( int i = 0; i < length; i++ ){
                                          if( !vlist->empty() ){
                                            this->evaluate( vlist->pop_front(), execContext, dataType );
                                          }
                                        }
                                      }
                                    }
                                    break;
              case __assignment:
                                Operator *assignmentNode;
                                assignmentNode = CAST_TO( Operator, astNode );
                                if( assignmentNode != NULL ){
                                  list<Node*> *operands = assignmentNode->getOperands();
                                  // getType.
                                  int dataType = dataTypeInfo;
                                  operands->pop_front();
                                  Identifier *id = CAST_TO( Identifier, operands->front() );
                                  if( id != NULL ){
                                    operands->pop_front();
                                    // get the expression node.
                                    Expression *expNode = CAST_TO( Expression, operands->front() );
                                    if( expNode != NULL ){
                                      Object *value = this->evaluate( expNode->getNode(), execContext, dataType );
                                      execContext->put( string( id->getName() ), value );
                                    }
                                  }
                                }
                                break;
                case __funct_def:
                                Operator *functDefNode;
                                functDefNode = CAST_TO( Operator, astNode );
                                if( functDefNode != NULL ){
                                  // get the operands
                                  list<Node*> *operands = functDefNode->getOperands();
                                  Identifier  *functName = CAST_TO( Identifier, operands->front() );
                                  if( functName != NULL ){
                                    UserDefinedFunction *funct = new UserDefinedFunction( operands );
                                    execContext->put( functName->getName(), funct );
                                  }
                                }
                                break;
                case __funct_call:
                                Operator *functCallNode;
                                functCallNode = CAST_TO( Operator, astNode );
                                if( functCallNode != NULL ){
                                  list<Node*> *operands = functCallNode->getOperands();
                                  // get the function name.
                                  Identifier *functName = CAST_TO( Identifier, operands->front() );
                                  if( functName != NULL ){
                                    if( this->isBuiltInFunction( functName ) ){
                                      this->evaluateBuiltInFunction( functName, operands, execContext );
                                    }
                                    else if( this->isUserDefinedFunction( functName ) ){
                                      this->evaluateUserDefinedFunction( functName, operands, execContext );
                                    }
                                    else{
                                      cout<<"Undefined function: "<<functName->getName()<<endl;
                                      exit(1);
                                    }
                                  }
                                }
                                break;
                  case __expression:                                    
                                    Expression *expNode;
                                    expNode = CAST_TO( Expression, astNode );
                                    if( expNode != NULL ){
                                      return this->evaluate( expNode->getNode(), execContext, dataTypeInfo );
                                    }
                                    break;

           }
           return NULL;
        }

        bool isBuiltInFunction( Identifier *functName ){
          string name = functName->getName();
          if( builtins[ name ] != NULL ){
            return true;
          }
          else{
            return false;
          }
        }

        bool isUserDefinedFunction( Identifier *functName ){
            return false;
        }

        Object* evaluateBuiltInFunction( Identifier *functName, list<Node*> *operands, Context *execContext ){
           list<Object*> *args = new list<Object*>();
           // pop the functName.
           operands->pop_front();
           int length = operands->size();
           for( int i = 0; i < length; i++ ){
              args->push_back( this->evaluate( operands->front(), execContext, -1 ) );
           }
           BuiltInFunction function = getBuiltInFunction( functName );
           function(args);
        }

        Object* evaluateUserDefinedFunction( Identifier *functName, list<Node*> *operands, Context *execContext ){
          ;
        }

        void loadBuiltIns(void){
          builtins[ "print" ] = bnk_builtins::__bprint;
        }

        BuiltInFunction getBuiltInFunction( Identifier *functName ){
          string name = functName->getName();
          return builtins[ name ];
        }
};
#endif
