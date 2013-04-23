#include<iostream>
#include<list>
#include<cstdlib>
#include "bnKapi.h"
#include "object.h"
#include "array.h"

#ifndef __BINARYOP
#define __BINARYOP
using namespace std;
using namespace bnk_types;

class BinaryOperation{
    protected:
              Object *firstOp, *secondOp;
    public:
            BinaryOperation(){
                firstOp = NULL;
                secondOp = NULL;
            }
            Object* executeOperation(void);
            virtual Object* exec( int, int ) = 0;
            virtual Object* exec( int, double ) = 0;
            virtual Object* exec( double, double ) = 0;
            virtual Object* exec(Array*, Array*){}
            virtual bool isTypeCompatible(void);
            
            Object* getFirstOperand(void){
                return firstOp;
            }
            
            Object* getSecondOperand(void){
                return secondOp;
            }
            
            void setFirstOperand( Object* op ){
                firstOp = op;
            }
            
            void setSecondOperand( Object* op ){
                secondOp = op;
            }
    
};

class AdditionOperation: public BinaryOperation{
    public:
            AdditionOperation(){
            }
            bool isTypeCompatible(void);
            Object* exec( int, int );
            Object* exec( int, double ){ return NULL; }
            Object* exec( double, double );
            Object* exec(Array*, Array*);
};

class SubtractionOperation: public BinaryOperation{
    public:
            SubtractionOperation(){                
            }
            Object* exec( int, int );
            Object* exec( int, double ){ return NULL; }
            Object* exec( double, double );
};

class MultiplicationOperation: public BinaryOperation{
    public:
            MultiplicationOperation(){
            }
            Object* exec( int, int );
            Object* exec( int, double ){ return NULL; }
            Object* exec( double, double );
};

class DivOperation: public BinaryOperation{
    public:
            DivOperation(){
            }
            Object* exec( int, int );
            Object* exec( int, double ){ return NULL; }
            Object* exec( double, double );
};

class OrOperation: public BinaryOperation{
    public:
            OrOperation(){
            }
            Object* exec( int, int );
            Object* exec( int, double ){ return NULL; }
            Object* exec( double, double ){ return NULL; }
};

class AndOperation: public BinaryOperation{
    public:
            AndOperation(){
            }
            Object* exec( int, int );
            Object* exec( int, double ){ return NULL; }
            Object* exec( double, double ){ return NULL; }
};

class LessThanOperator: public BinaryOperation{
    public:
            LessThanOperator(){
            }
            Object* exec( int, int );
            Object* exec( int, double ){ return NULL; }
            Object* exec( double, double ){ return NULL; }
};

class GreaterThanOperator: public BinaryOperation{
    public:
            GreaterThanOperator(){
            }
            Object* exec( int, int );
            Object* exec( int, double ){ return NULL; }
            Object* exec( double, double ){ return NULL; }
};

class LessThanOrEqualOperator: public BinaryOperation{
    public:
            LessThanOrEqualOperator(){
            }
            Object* exec( int, int );
            Object* exec( int, double ){ return NULL; }
            Object* exec( double, double ){ return NULL; }
};

class GreaterThanOrEqualOperator: public BinaryOperation{
    public:
            GreaterThanOrEqualOperator(){
            }
            Object* exec( int, int );
            Object* exec( int, double ){ return NULL; }
            Object* exec( double, double ){ return NULL; }
};

class EqualityOperator : public BinaryOperation{
    public:
            EqualityOperator(){
                
            }
            Object* exec( int, int );
            Object* exec( int, double ){ return NULL; }
            Object* exec( double, double ){ return NULL; }
};

#endif
