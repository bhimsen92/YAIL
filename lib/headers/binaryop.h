#include<iostream>
#include<list>
#include<cstdlib>
#include "bnKapi.h"
#include "object.h"

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
            virtual int exec( int, int ) = 0;
            virtual double exec( int, double ) = 0;
            virtual double exec( double, double ) = 0;
            bool isCompatible(void);
            
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
            int exec( int, int );
            double exec( int, double ){ return 0.0; }
            double exec( double, double ){ return 0.0; }
};

class SubtractionOperation: public BinaryOperation{
    public:
            SubtractionOperation(){                
            }
            int exec( int, int );
            double exec( int, double ){ return 0.0; }
            double exec( double, double ){ return 0.0; }            
};

class MultiplicationOperation: public BinaryOperation{
    public:
            MultiplicationOperation(){
            }
            int exec( int, int );
            double exec( int, double ){ return 0.0; }
            double exec( double, double ){ return 0.0; }            
};

class DivOperation: public BinaryOperation{
    public:
            DivOperation(){
            }
            int exec( int, int );
            double exec( int, double ){ return 0.0; }
            double exec( double, double ){ return 0.0; }            
};
#endif
