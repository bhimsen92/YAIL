// modifications that needs to be done: add stmtlist in case expressions, it will avoid lots of repeating code.
// 2264 lines.
#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<cstring>
#include<cstdarg>
#include<map>
#include "headers/instr.h"
#include "headers/ir.h"
#include "headers/treewalker.h"
#include "headers/string.h"
#include "headers/number.h"
#include "headers/udf.h"
#include "headers/builtins.h"
#include "headers/binaryop.h"

using namespace std;

bnk_types::Object* TreeWalker::evaluate( Node* astNode, Context* execContext, Type *dtype ){
    int nodeType = astNode->getType();
    switch( nodeType ){
        case __identifier:
                            break;
        case __string:
                            break;
        case __integer:
                            break;
        case __nothing:
                            break;       
        case __double:
                            break;
        case __return:
                            break;
        case __if:
                            break;
        case __else:
                            break;
        case __elif:
                            break;
        case __var_definition:
                                    Operator *varDefNode;
                                    varDefNode = CAST_TO(Operator, astNode);
                                    if(varDefNode != NULL){
                                        // get the type operands object.
                                        Operands *ops = varDefNode->getOperands();
                                        // get the type object.
                                        Type *dataType = CAST_TO(Type, ops->get(0));
                                        if(dataType != NULL){
                                            // get the width.
                                            int dataWidth = dataType->getDataWidth();
                                            // get variable list object.
                                            VariableList *vlist = CAST(VariableList, ops->get(1));
                                            // get the length and calculate the amount of storage that 
                                            // needs to allocated.
                                            int allocationSize = dataWidth * vlist->getLength();
                                            // generate allocate instruction.
                                            this->add(new Allocate(allocate, new bnk_astNodes::Integer(allocationSize), NULL, NULL));
                                            // update offset 
                                            this->updateOffset(allocationSize);
                                            // go through each variable list and generate instructions for that.
                                            for(int i = 0; i < vlist->getLength(); i++){
                                                this->evaluate(vlist->get(i), execContext, dataType);
                                            }
                                        }
                                    }
                                    break;
        case __assignment:
                                Operator *assignNode;
                                assignNode = CAST_TO(Operator, astNode);
                                if(assignNode != NULL){
                                    Operands *ops = assignNode->getOperands();
                                    // get the identifier node.
                                    Identifier *id = CAST_TO(Identifier, ops->get(1));
                                    // get the expression node.
                                    Node *expressionNode = ops->get(2);
                                    // generate op code for expression and 
                                    // return the result in an temp node.
                                    Node *result = this->evaluate(expressionNode, execContext, dataType);
                                    // 
                                }
                                break;
        case __funct_def:
                                break;
        case __funct_call:
                                break;
        case __addition:
                                break;
        case __subtraction:
                                break;
        case __multiplication:
                                break;
        case __div:
                                break;
        case __power:
                                break;
        case __or:
                                break;
        case __and:
                                break;
        case __lt:
                                break;
        case __gt:
                                break;
        case __le:
                                break;
        case __ge:
                                break;
        case __equality:
                                break;
    }
    return NULL;
}

Object* Interpreter::execOperation( Operator* opNode, Context* execContext, BinaryOperation* op ){
}

bool Interpreter::isBuiltInFunction( Identifier *functName ){
}

bool Interpreter::isUserDefinedFunction( Identifier *functName, Context *execContext ){
}

Object* Interpreter::evaluateBuiltInFunction( Identifier *functName, Operands *operands, Context *execContext ){
}

Object* Interpreter::evaluateUserDefinedFunction( Identifier *functName, Operands *arguments, Context *execContext ){
}

bool Interpreter::isReturnType( Object* obj ){
}

void Interpreter::loadBuiltIns(void){
}

BuiltInFunction Interpreter::getBuiltInFunction( Identifier *functName ){
}

void Interpreter::errorMessage( int size, ... ){
    int i;
    char *message;
    va_list args;
    va_start( args, size );
    for( i = 0; i < size; i++ ){
        message = va_arg( args, char* );
        cout<<message;
    }
    cout<<endl;
}

bool Interpreter::isCallable( Object *value ){
    return ( value->getDataType() == __function_t );
}
