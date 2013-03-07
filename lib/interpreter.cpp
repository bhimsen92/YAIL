#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<cstring>
#include<map>
#include "headers/interpreter.h"
#include "headers/string.h"
#include "headers/number.h"
#include "headers/udf.h"
#include "headers/builtins.h"
#include "headers/binaryop.h"

using namespace std;

bnk_types::Object* Interpreter::evaluate( Node* astNode, Context* execContext, int dataTypeInfo ){
    int nodeType = astNode->getType();
    switch( nodeType ){
        case __identifier:
                            bnk_astNodes::Identifier *ident;
                            ident = CAST_TO( bnk_astNodes::Identifier, astNode );
                            if( ident != NULL ){
                                string varName = ident->getName();
                                Object* rval = execContext->get(varName);
                                if( rval != NULL ){
                                    return rval;
                                }
                                else{
                                    errorMessage("Undefined variable.");
                                    exit(1);
                                }
                            }
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
                                    Object *value = this->evaluate( operands->front(), execContext, dataType );
                                    execContext->put( string( id->getName() ), value );               
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
        case __addition:
                                    // cast to Operator Node.
                                    Operator *addNode;
                                    addNode = CAST_TO( bnk_astNodes::Operator, astNode );
                                    return this->execOperation( addNode, execContext, new AdditionOperation() );
                                    break;
        case __subtraction:
                                    Operator *subNode;
                                    subNode = CAST_TO( bnk_astNodes::Operator, astNode );
                                    return this->execOperation( subNode, execContext, new SubtractionOperation() );
                                    break;
        case __multiplication:
                                    Operator *mulNode;
                                    mulNode = CAST_TO( bnk_astNodes::Operator, astNode );
                                    return this->execOperation( mulNode, execContext, new MultiplicationOperation() );
                                    break;
        case __div:
                                    Operator *divNode;
                                    divNode = CAST_TO( bnk_astNodes::Operator, astNode );
                                    return this->execOperation( divNode, execContext, new DivOperation() );
                                    break;
        case __power:
                                    break;
        case __or:
                                    Operator *orNode;
                                    orNode = CAST_TO( bnk_astNodes::Operator, astNode );                                    
                                    break;
    }
    return NULL;
}

Object* Interpreter::execOperation( Operator* opNode, Context* execContext, BinaryOperation* op ){
    // get the operands.
    list<Node*> *operands = opNode->getOperands();
    // get the firstOp
    Object *firstOp = this->evaluate( operands->front(), execContext, -1 );
    operands->pop_front();
    Object *secondOp = this->evaluate( operands->front(), execContext, -1 );
    operands->pop_front();
    // set the operands to the operation object.
    op->setFirstOperand( firstOp );
    op->setSecondOperand( secondOp );
    if( op->isCompatible() ){
        return op->executeOperation();
    }
    else{
        errorMessage( "Incompatible Operands" );
        exit(1);
    }
}

bool Interpreter::isBuiltInFunction( Identifier *functName ){
    string name = functName->getName();
    if( builtins[ name ] != NULL ){
        return true;
    }
    else{
        return false;
    }
}

bool Interpreter::isUserDefinedFunction( Identifier *functName ){
    return false;
}

Object* Interpreter::evaluateBuiltInFunction( Identifier *functName, list<Node*> *operands, Context *execContext ){
    list<Object*> *args = new list<Object*>();
    // pop the functName.
    operands->pop_front();
    int length = operands->size();
    for( int i = 0; i < length; i++ ){
        args->push_back( this->evaluate( operands->front(), execContext, -1 ) );
        operands->pop_front();
    }
    BuiltInFunction function = getBuiltInFunction( functName );
    function(args);
    }

Object* Interpreter::evaluateUserDefinedFunction( Identifier *functName, list<Node*> *operands, Context *execContext ){
    ;
}

void Interpreter::loadBuiltIns(void){
    builtins[ "print" ] = bnk_builtins::__bprint;
}

BuiltInFunction Interpreter::getBuiltInFunction( Identifier *functName ){
    string name = functName->getName();
    return builtins[ name ];
}

void Interpreter::errorMessage( const char* message ){
    cout<<"Error: "<<message<<endl;
}
