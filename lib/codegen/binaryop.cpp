#include<iostream>
#include<cstdlib>
#include "../headers/tokens.h"
#include "../headers/node.h"
#include "./headers/binaryop.h"
#include "./headers/ir.h"
#include "./headers/instr.h"

using namespace std;
using namespace yacl::ast;
using namespace yacl::codegen::binaryop;
using namespace yacl::codegen::ir;
using namespace yacl::codegen;

Node* BinaryOperation::executeOperation(void){
    int ftype = firstOp->getDataType()->getDataType(),
        stype = secondOp->getDataType()->getDataType();
    if(ftype == __integer){
        if(stype == __integer){
            // if both ops are integers,
            // then the resulting type is also integer.
            // generate instruction for moving firstOp and secondOp
            // to register, then for addition and moving result into temp
            // location.
            ctx->updateStorage(firstOp->getDataType()->getDataWidth());
            Temp *tmp = new Temp(__tmp);
            tmp->setDataType(new Type(__integer, 4));
            tmp->setTypeClass(NumberClass);
            // add this temp to tmp list.
            ctx->addTemp(tmp);
            // generate add instruction.
            ctx->addInstruction(new Add(add, firstOp, secondOp, secondOp));
            // generate move instruction.
            ctx->addInstruction(new Move(mov, secondOp, NULL, tmp));
            // clear all the registers.
            Register::clearAll();
            return tmp;
        }
        else{
            return NULL;
        }
    }
    else{
        return NULL;
    }
}

bool BinaryOperation::isTypeCompatible(void){
    return true;
}

Node* AdditionOperation::exec( int a, int b ){
}

Node* AdditionOperation::exec( double a, double b ){
}

bool AdditionOperation::isTypeCompatible(void){
    // Addition operation is defined for NumberClass, CharClass and ListClass.
    // if the operands(both) belong to one of this classes then interpreter can
    // proceed with the operation.
    return true;
}
/*
Node* SubtractionOperation::exec( int a, int b ){
}

Node* SubtractionOperation::exec( double a, double b ){
}

Node* MultiplicationOperation::exec( int a, int b ){
}

Node* MultiplicationOperation::exec( double a, double b ){
}

Node* DivOperation::exec( int a, int b ){
}

Node* DivOperation::exec( double a, double b ){
}

Node* OrOperation::exec( int a, int b ){
}

Node* AndOperation::exec( int a, int b ){
}

Node* LessThanOperator::exec( int a, int b ){
}

Node* LessThanOrEqualOperator::exec( int a, int b ){
}

Node* GreaterThanOperator::exec( int a, int b ){
}

Node* GreaterThanOrEqualOperator::exec( int a, int b ){
}

Node* EqualityOperator::exec( int a, int b ){
}*/
