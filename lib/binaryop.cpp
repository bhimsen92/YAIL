#include<iostream>
#include<cstdlib>
#include "./headers/tokens.h"
#include "./headers/binaryop.h"
#include "./headers/value.h"
#include "./headers/number.h"

using namespace std;
using namespace bnk_types;
using namespace bnk;

Object* BinaryOperation::executeOperation(void){
    int fOpType = this->firstOp->getDataType(),
        sOpType = this->secondOp->getDataType(),
        finalType;
    int ia, ib, ir;
    double da, db, dr;
    Object *rval = NULL;
    // check first operand type.
    if( fOpType == __integer_t ){
        // check second operand type.
        ia = firstOp->getValue()->getIntVal();
        if( sOpType == __integer_t ){
            ib = secondOp->getValue()->getIntVal();
            // so it is a simple int + int operation.
            ir = this->exec( ia, ib );
            rval = new Integer( ir );
            finalType = __integer_t;
        }
        else{
            db = secondOp->getValue()->getDoubleVal();
            dr = (double)this->exec( ia, db );
            finalType = __double_t;
        }
    }
    else if( fOpType == __double_t ){
        da = firstOp->getValue()->getDoubleVal();
        // for union sake, i need to check the other operand.
        if( sOpType == __integer_t ){
            db = (double)secondOp->getValue()->getIntVal();
        }
        else{
            db = secondOp->getValue()->getDoubleVal();
        }
        dr = this->exec( da, db );
        finalType = __double_t;
    }
    return rval;
}

bool BinaryOperation::isCompatible(void){
    return ( ( firstOp->getTypeClass() == NumberClass ) && ( secondOp->getTypeClass() == NumberClass ) );
}

int AdditionOperation::exec( int a, int b ){
    return a + b;
}


int SubtractionOperation::exec( int a, int b ){
    return a - b;
}

int MultiplicationOperation::exec( int a, int b ){
    return a * b;
}

int DivOperation::exec( int a, int b ){
    return a / b;
}
