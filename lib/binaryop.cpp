#include<iostream>
#include<cstdlib>
#include "./headers/tokens.h"
#include "./headers/binaryop.h"
#include "./headers/value.h"
#include "./headers/number.h"
#include "./headers/bool.h"

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
            rval = this->exec( ia, ib );
            //rval = new Integer( ir );
            finalType = __integer_t;
        }
        else{
            db = secondOp->getValue()->getDoubleVal();
            rval = this->exec( ia, db );
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
        rval = this->exec( da, db );
        finalType = __double_t;
    }
    return rval;
}

bool BinaryOperation::isTypeCompatible(void){
    return ( ( firstOp->getTypeClass() == NumberClass ) && ( secondOp->getTypeClass() == NumberClass ) );
}

Object* AdditionOperation::exec( int a, int b ){
    return new Integer( a + b );
}

bool AdditionOperation::isTypeCompatible(void){
    // Addition operation is defined for NumberClass, CharClass and ListClass.
    // if the operands(both) belong to one of this classes then interpreter can
    // proceed with the operation.
    bool rval = false;
    int  cls1 = firstOp->getTypeClass(),
         cls2 = secondOp->getTypeClass();
    if( cls1 == NumberClass && cls2 == NumberClass ){
        rval = true;
    }
    else if( cls1 == CharClass && cls2 == CharClass ){
        rval = true;
    }
    else if( cls1 == ListClass && cls2 == ListClass ){
        rval = true;
    }
    return rval;
}

Object* SubtractionOperation::exec( int a, int b ){
    return new Integer( a - b );
}

Object* MultiplicationOperation::exec( int a, int b ){
    return new Integer( a * b );
}

Object* DivOperation::exec( int a, int b ){
    return new Integer( a / b );
}

Object* OrOperation::exec( int a, int b ){
    return new Boolean( a || b );   
}

Object* AndOperation::exec( int a, int b ){
    return new Boolean( a && b );
}

Object* LessThanOperator::exec( int a, int b ){
    return new Boolean( a < b );
}

Object* LessThanOrEqualOperator::exec( int a, int b ){
    return new Boolean( a <= b );
}

Object* GreaterThanOperator::exec( int a, int b ){
    return new Boolean( a > b );
}

Object* GreaterThanOrEqualOperator::exec( int a, int b ){
    return new Boolean( a >= b );   
}
