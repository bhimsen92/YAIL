#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<cstring>
#include<cstdarg>
#include<map>
#include "./headers/instr.h"
#include "./headers/ir.h"
#include "./headers/treewalker.h"
#include "../headers/node.h"
#include "../headers/context.h"

using namespace std;
using namespace yacl::ast;
using namespace yacl::codegen::ir;

Node* TreeWalker::evaluate( Node* astNode, Context* ctx, Type *dtype ){
    int nodeType = astNode->getType();
    switch( nodeType ){
        case __identifier:
                            // just returning identifier node to the caller.
                            // address calculation are offloaded to IRCode class
                            // methods[keeps things simple].
                            {
                                Identifier *id = CAST_TO(Identifier, astNode);
                                Node *rval = ctx->get(id->getName(), 0);
                                if(rval != NULL){
                                    return rval;
                                }
                                else{
                                    errorMessage(1, "Undefined variable: ", id->getName());
                                    exit(1);
                                }
                            }
        case __string:
                            break;
        case __integer:
                        {
                            Integer *integer;
                            integer = CAST_TO(Integer, astNode);
                            // create new Register.[uses current unused register]
                            Node *reg = new Register(__reg);
                            reg->setDataType(new Type(__integer, 4));
                            reg->setTypeClass(NumberClass);
                            ctx->addInstruction(new Move(mov, integer, NULL, reg));
                            //this->add(new Move(mov, integer, NULL, reg));
                            // return register which will be used in further expression codegen.
                            return reg;
                        }
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
                                            VariableList *vlist = CAST_TO(VariableList, ops->get(1));
                                            // get the length and calculate the amount of storage that 
                                            // needs to allocated.
                                            int allocationSize = dataWidth * vlist->getLength();
                                            // update storage for this context.
                                            ctx->updateStorage(allocationSize);
                                            // go through each variable list and generate instructions for that.
                                            for(int i = 0; i < vlist->getLength(); i++){
                                                this->evaluate(vlist->get(i), ctx, dataType);
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
                                    // check whether the name is already defined in the current
                                    // context or not.
                                    if(!ctx->isBound(id,0)){
                                        // get the expression node.
                                        Node *expressionNode = ops->get(2);
                                        // generate op code for expression and
                                        // return the result in an temp node.
                                        Node *result = this->evaluate(expressionNode, ctx, dtype);
                                        id->setDataType(result->getDataType());
                                        id->setTypeClass(result->getTypeClass());
                                        // put the name into the symbol table and its associated object.
                                        ctx->put(id->getName(), id);
                                        // put the id into contexts variables list.
                                        ctx->addVar(id);
                                        // add assignment instruction to contexts instruction list.
                                        // [assigment instruction=> move instruction]
                                        ctx->addInstruction(new Move(mov, result, NULL, id));
                                        // assignment instruction returns nothing.
                                        Register::clearAll();
                                        break;
                                    }
                                    else{
                                        errorMessage(1, "Variable is already defined");
                                        exit(1);
                                    }
                                }
                                break;
        case __funct_def:
                                break;
        case __funct_call:
                                break;
        case __addition:        {
                                    Operator *addition = CAST_TO(Operator, astNode);
                                    return this->execOperation(addition, ctx, new AdditionOperation(ctx));
                                }
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

Node* TreeWalker::execOperation( Operator* opNode, Context* ctx, BinaryOperation* op ){
    // get the operands from the operator node.
    // evaluate the operands by generating code for them,
    // then, check for type compatibility, if everything seems ok,
    // generate code for executing this operation.
    // temp node generation and generating code for them is offloaded to BinaryOperation subclasses.
    Operands *ops = opNode->getOperands();
    Node *firstOp = this->evaluate(ops->get(0), ctx, NULL);
    Node *secondOp = this->evaluate(ops->get(1), ctx, NULL);
    op->setFirstOperand(firstOp);
    op->setSecondOperand(secondOp);
    if(op->isTypeCompatible()){
        Node *rval = op->executeOperation();
        return rval;
    }
    else{
        errorMessage(1, "Incompatible operands for this operation");
    }
}

bool TreeWalker::isBuiltInFunction( Identifier *functName ){
}

bool TreeWalker::isUserDefinedFunction( Identifier *functName, Context *ctx ){
}

Node* TreeWalker::evaluateBuiltInFunction( Identifier *functName, Operands *operands, Context *ctx ){
}

Node* TreeWalker::evaluateUserDefinedFunction( Identifier *functName, Operands *arguments, Context *ctx ){
}

bool TreeWalker::isReturnType(Node* node){
}

//void TreeWalker::loadBuiltIns(void){
//}

//BuiltInFunction TreeWalker::getBuiltInFunction( Identifier *functName ){
//}

void TreeWalker::errorMessage( int size, ... ){
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

//bool TreeWalker::isCallable( Object *value ){
//    return ( value->getDataType() == __function_t );
//}
