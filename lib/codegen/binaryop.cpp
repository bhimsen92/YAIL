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
            Node *rval = this->exec(1,1);
            //Register::clearAll();
            return rval;
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
    //ctx->updateStorage(firstOp->getDataType()->getDataWidth());
    Register *guardVar = CAST_TO(Register, secondOp);
    if(guardVar == NULL || !secondOp->hasLocationAdded()){
        // generate add instruction.
        ctx->addInstruction(new Add(add, firstOp, secondOp, secondOp));
        return secondOp;
    }
    else{
        // secondOp has been attached to a memory location.
        // need to spit out it.
        if(!Register::areAvailable() && secondOp->hasLocationAdded()){
            // if registers are not avaiable.
            // remove the registers in a fifo manner.
            Register *spilledReg = Register::spill();
            // generate a move instruction from spilledReg to the location.
            Node *loc = spilledReg->getLocation();
            // remove the var location from the spilledReg.
            spilledReg->removeLocation();
            // remove the register ref from location var.
            loc->removeLocation();
            // generate move instruction from spilledReg to location var.
            ctx->addInstruction(new Move(mov, spilledReg, NULL, loc));
        }
        if(secondOp->hasLocationAdded()){
            Register *reg = Register::getRegister(__reg);
            // add location from secondOp to this newly created reg.
            Node *location = secondOp->getLocation();
            location->removeLocation();
            location->addLocation(reg);
            reg->addLocation(location);
            secondOp->removeLocation();
            // generate an instruction which moves data from secondOp
            // to newly crated register.
            ctx->addInstruction(new Move(mov, secondOp, NULL, reg));
        }
        // generate add instruction.
        ctx->addInstruction(new Add(add, firstOp, secondOp, secondOp));
        return secondOp;
    }
    // control will never come here.
}

Node* AdditionOperation::exec( double a, double b ){
}

bool AdditionOperation::isTypeCompatible(void){
    // Addition operation is defined for NumberClass, CharClass and ListClass.
    // if the operands(both) belong to one of this classes then interpreter can
    // proceed with the operation.
    return true;
}

Node* SubtractionOperation::exec( int a, int b ){
    Register *guardVar = CAST_TO(Register, firstOp);
    if(guardVar == NULL || !firstOp->hasLocationAdded()){
        // generate add instruction.
        ctx->addInstruction(new Sub(sub, secondOp, firstOp, firstOp));
        return secondOp;
    }
    else{
        // secondOp has been attached to a memory location.
        // need to spit out it.
        if(!Register::areAvailable() && firstOp->hasLocationAdded()){
            // if registers are not avaiable.
            // remove the registers in a fifo manner.
            Register *spilledReg = Register::spill();
            // generate a move instruction from spilledReg to the location.
            Node *loc = spilledReg->getLocation();
            // remove the var location from the spilledReg.
            spilledReg->removeLocation();
            // remove the register ref from location var.
            loc->removeLocation();
            // generate move instruction from spilledReg to location var.
            ctx->addInstruction(new Move(mov, spilledReg, NULL, loc));
        }
        if(firstOp->hasLocationAdded()){
            Register *reg = Register::getRegister(__reg);
            // add location from secondOp to this newly created reg.
            Node *location = firstOp->getLocation();
            location->removeLocation();
            location->addLocation(reg);
            reg->addLocation(location);
            secondOp->removeLocation();
            // generate an instruction which moves data from secondOp
            // to newly crated register.
            ctx->addInstruction(new Move(mov, firstOp, NULL, reg));
        }
        // generate add instruction.
        ctx->addInstruction(new Sub(sub, secondOp, firstOp, firstOp));
        return firstOp;
    }
}


Node* SubtractionOperation::exec( double a, double b ){
}


Node* MultiplicationOperation::exec( int a, int b ){
Register *guardVar = CAST_TO(Register, secondOp);
    if(guardVar == NULL || !secondOp->hasLocationAdded()){
        // generate add instruction.
        ctx->addInstruction(new Mul(imul, firstOp, secondOp, secondOp));
        return secondOp;
    }
    else{
        // secondOp has been attached to a memory location.
        // need to spit out it.
        if(!Register::areAvailable() && secondOp->hasLocationAdded()){
            // if registers are not avaiable.
            // remove the registers in a fifo manner.
            Register *spilledReg = Register::spill();
            // generate a move instruction from spilledReg to the location.
            Node *loc = spilledReg->getLocation();
            // remove the var location from the spilledReg.
            spilledReg->removeLocation();
            // remove the register ref from location var.
            loc->removeLocation();
            // generate move instruction from spilledReg to location var.
            ctx->addInstruction(new Move(mov, spilledReg, NULL, loc));
        }
        if(secondOp->hasLocationAdded()){
            Register *reg = Register::getRegister(__reg);
            // add location from secondOp to this newly created reg.
            Node *location = secondOp->getLocation();
            location->removeLocation();
            location->addLocation(reg);
            reg->addLocation(location);
            secondOp->removeLocation();
            // generate an instruction which moves data from secondOp
            // to newly crated register.
            ctx->addInstruction(new Move(mov, secondOp, NULL, reg));
        }
        // generate add instruction.
        ctx->addInstruction(new Mul(imul, firstOp, secondOp, secondOp));
        return secondOp;
    }    
}

Node* MultiplicationOperation::exec( double a, double b ){
}
/*
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
*/
Node* EqualityOperator::exec( int a, int b ){
    // generate cmp instruction.
    ctx->addInstruction(new Compare(cmp, firstOp, secondOp, NULL));
    // create a new label.
    Label *label = new Label();
    // generate jump instruction.
    ctx->addInstruction(new JumpIfEqual(je, label, NULL, NULL));
    return label;
}
