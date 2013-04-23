#include<iostream>
#include<cstdlib>
#include "./headers/bnKapi.h"
#include "./headers/object.h"
#include "./headers/tokens.h"
#include "./headers/binaryop.h"
#include "./headers/number.h"
#include "./headers/bool.h"
#include "./headers/array.h"

using namespace std;
using namespace bnk_types;

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
    else if(fOpType == __array_int_t || fOpType == __array_empty_t){
        if(sOpType == __array_int_t || sOpType == __array_empty_t){
            Array *aa = CAST_TO(Array, firstOp);
            Array *ab = CAST_TO(Array, secondOp);
            rval = this->exec(aa, ab);
        }
        else{
            cout<<"can only add array of same type.\n";
            exit(1);
        }
    }
    return rval;
}

bool BinaryOperation::isTypeCompatible(void){
    return ( ( firstOp->getTypeClass() == NumberClass ) && ( secondOp->getTypeClass() == NumberClass ) );
}

Object* AdditionOperation::exec( int a, int b ){
    return new Integer( a + b );
}

Object* AdditionOperation::exec( double a, double b ){
    return new Double( a + b );
}

Object* AdditionOperation::exec(Array *a, Array *b){
    int al = a->getLength(), bl = b->getLength();
    int t = a->getDataType();
    if(t == __array_empty_t){
        t = b->getDataType();
    }
    Array *rval = new Array(t, al + bl);
    for(int i = 0; i < al; i++){
        rval->push_back(a->index(i));
    }
    for(int i = 0; i < bl; i++){
        rval->push_back(b->index(i));
    }
    return rval;
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

Object* SubtractionOperation::exec( double a, double b ){
    return new Double( a - b );
}

Object* MultiplicationOperation::exec( int a, int b ){
    return new Integer( a * b );
}

Object* MultiplicationOperation::exec( double a, double b ){
    return new Double( a * b );    
}

Object* DivOperation::exec( int a, int b ){
    return new Integer( a / b );
}

Object* DivOperation::exec( double a, double b ){
    return new Double( a / b );    
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

Object* EqualityOperator::exec( int a, int b ){
    return new Boolean( a == b );
}
