#include<iostream>
#include<list>
#include<cstdlib>
#include "../../headers/bnKapi.h"
#include "../../headers/node.h"

#ifndef __BINARYOP
#define __BINARYOP
using namespace std;
using namespace yacl::ast;
namespace yacl{
    namespace codegen{
        namespace binaryop{
            class BinaryOperation{
                protected:
                      Node *firstOp, *secondOp;
                public:
                    BinaryOperation(){
                        firstOp = NULL;
                        secondOp = NULL;
                    }
                    Node* executeOperation(void);
                    virtual Node* exec( int, int ) = 0;
                    virtual Node* exec( int, double ) = 0;
                    virtual Node* exec( double, double ) = 0;
                    virtual bool isTypeCompatible(void);
                
                    Node* getFirstOperand(void){
                        return firstOp;
                    }
            
                    Node* getSecondOperand(void){
                        return secondOp;
                    }
                
                    void setFirstOperand( Node* op ){
                        firstOp = op;
                    }
            
                    void setSecondOperand( Node* op ){
                        secondOp = op;
                    }
        
            };

            class AdditionOperation: public BinaryOperation{
                public:
                    AdditionOperation(){
                    }
                    bool isTypeCompatible(void);
                    Node* exec( int, int );
                    Node* exec( int, double ){ return NULL; }
                    Node* exec( double, double );
            };

            class SubtractionOperation: public BinaryOperation{
                public:
                SubtractionOperation(){                
                }
                Node* exec( int, int );
                Node* exec( int, double ){ return NULL; }
                Node* exec( double, double );
            };

            class MultiplicationOperation: public BinaryOperation{
                public:
                MultiplicationOperation(){
                }
                Node* exec( int, int );
                Node* exec( int, double ){ return NULL; }
                Node* exec( double, double );
            };

            class DivOperation: public BinaryOperation{
                public:
                    DivOperation(){
                    }
                    Node* exec( int, int );
                    Node* exec( int, double ){ return NULL; }
                    Node* exec( double, double );
            };

            class OrOperation: public BinaryOperation{
                public:
                    OrOperation(){
                    }
                    Node* exec( int, int );
                    Node* exec( int, double ){ return NULL; }
                    Node* exec( double, double ){ return NULL; }
            };

class AndOperation: public BinaryOperation{
    public:
            AndOperation(){
            }
            Node* exec( int, int );
            Node* exec( int, double ){ return NULL; }
            Node* exec( double, double ){ return NULL; }
};

class LessThanOperator: public BinaryOperation{
    public:
            LessThanOperator(){
            }
            Node* exec( int, int );
            Node* exec( int, double ){ return NULL; }
            Node* exec( double, double ){ return NULL; }
};

class GreaterThanOperator: public BinaryOperation{
    public:
            GreaterThanOperator(){
            }
            Node* exec( int, int );
            Node* exec( int, double ){ return NULL; }
            Node* exec( double, double ){ return NULL; }
};

class LessThanOrEqualOperator: public BinaryOperation{
    public:
            LessThanOrEqualOperator(){
            }
            Node* exec( int, int );
            Node* exec( int, double ){ return NULL; }
            Node* exec( double, double ){ return NULL; }
};

class GreaterThanOrEqualOperator: public BinaryOperation{
    public:
            GreaterThanOrEqualOperator(){
            }
            Node* exec( int, int );
            Node* exec( int, double ){ return NULL; }
            Node* exec( double, double ){ return NULL; }
};

class EqualityOperator : public BinaryOperation{
    public:
            EqualityOperator(){
                
            }
            Node* exec( int, int );
            Node* exec( int, double ){ return NULL; }
            Node* exec( double, double ){ return NULL; }
};
} // end of binaryop namespace
} // end of codegen namespace
}// end of yacl namespace
#endif
