#include<iostream>
#include<cstdlib>
#include "../headers/tokens.h"
#include "../headers/node.h"
#include "./headers/binaryop.h"

using namespace std;
using namespace yacl::ast;
using namespace yacl::codegen::binaryop;

Node* BinaryOperation::executeOperation(void){
}

bool BinaryOperation::isTypeCompatible(void){
}

Node* AdditionOperation::exec( int a, int b ){
}

Node* AdditionOperation::exec( double a, double b ){
}

bool AdditionOperation::isTypeCompatible(void){
    // Addition operation is defined for NumberClass, CharClass and ListClass.
    // if the operands(both) belong to one of this classes then interpreter can
    // proceed with the operation.
}

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
}
