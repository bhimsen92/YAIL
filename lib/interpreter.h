#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<cstring>
#include "bnKapi.h"
#include "nodes/node.h"
#include "nodes/tokens.h"
#include "context.h"
#include "types/object.h"
#include "types/string.h"
#include "types/number.h"
#include "types/udf.h"

using namespace std;
using namespace bnk_astNodes;

#ifndef __INTERP
#define __INTERP

class Interpreter{
    public:
        Interpreter(){
        }
        bnk_types::Object* evaluate( Node* astNode, Context* execContext, int dataTypeInfo ){
           int nodeType = astNode->getType();
           switch( nodeType ){
              case __identifier:
                                    break;
              case __string:
                                    
                                    break;
              case __integer:
                                    bnk_astNodes::Integer *integer;
                                    integer = CAST_TO( bnk_astNodes::Integer, astNode );
                                    return new bnk_types::Integer( integer->getValue() );
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

           }
           return NULL;
        }        
};
#endif
