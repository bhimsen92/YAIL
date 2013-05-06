#include<iostream>
#include<cstdio>
#include<cstdlib>
#include "../../headers/node.h"
#include "../../headers/bnKapi.h"
#include "instr.h"

#ifndef __IRCODE
#define __IRCODE
using namespace yacl::ast;

namespace yacl{
    namespace codegen{
        namespace ir{
        // implementation of quads.
        class IRCode{
            protected:
                    // stores type of instruction.
                    Instr instruction;
                    // self explantory.
                    Node *arg1, *arg2;
                    // self explanatory.
                    Node *result;
            public:
                    IRCode(Instr instrType, Node *a1, Node *a2, Node *r){
                        instruction = instrType;
                        arg1 = a1;
                        arg2 = a2;
                        result = r;
                    }
                    
                    virtual char* emit(){
                        char *buffer = new char[256];
                        sprintf(buffer, "(%d, %s, %s, %s)", instruction, arg1->toString(), arg2->toString(), result->toString());
                        return buffer;
                    }
        };
    
        // allocate instruction.
        class Allocate : public IRCode{
            public:
                    Allocate(Instr instrType, Node *a1, Node *a2, Node *r) : IRCode(instrType, a1, NULL, NULL)
                    {
                        
                    }
                    
                    char* emit(){
                        char *buffer = new char[256];
                        sprintf(buffer, "subq %s, %s\n", arg1->toString(), "%rsp");
                        //sprintf(buffer, "(allocate, %s, NULL, NULL)\n", arg1->toString());
                        return buffer;
                    }
        };
        
        // move instruction.
        class Move : public IRCode{
            public:
                    Move(Instr instrType, Node *a1, Node *a2, Node *r) : IRCode(instrType, a1, NULL, r)
                    {
                        
                    }
                    char* emit(){
                        char *buffer = new char[256];
                        //Identifier *id = CAST_TO(Identifier, result);
                        //if(id != NULL && id->getOffset() > 0)
                            sprintf(buffer, "movq %s, %s\n", arg1->toString(), result->toString());
                        //else if(id == NULL)
                            //sprintf(buffer, "movq %s, %s\n", arg1->toString(), result->toString());
                        //sprintf(buffer, "(mov, %s, , %s)\n", arg1->toString(), result->toString());
                        return buffer;
                    }
        };

        // move address instruction.
        class MoveAddress : public IRCode{
            public:
                    MoveAddress(Instr instrType, Node *a1, Node *a2, Node *r): IRCode(instrType, a1, NULL, r){

                    }

                    char* emit(){
                        char *buffer = new char[256];
                        sprintf(buffer, "movq $%s, %s\n", arg1->toString(), result->toString());
                        //sprintf(buffer, "(mov, %s, , %s)\n", arg1->toString(), result->toString());
                        return buffer;                        
                    }
        };

        // move at address instruction.
        class MoveAtAddress: public IRCode{
            public:
                    MoveAtAddress(Instr instrType, Node *a1, Node *r): IRCode(instrType, a1, NULL, r){

                    }

                    char* emit(){
                        char *buffer = new char[256];
                        sprintf(buffer, "movq (%s), %s\n", arg1->toString(), result->toString());
                        return buffer;
                    }
        };
        
        // add instruction.
        class Add : public IRCode{
            public:
                    Add(Instr instrType, Node *a1, Node *a2, Node *r) : IRCode(instrType, a1, a2, r)
                    {
                        
                    }
                    
                    char* emit(){
                        char *buffer = new char[256];
                        sprintf(buffer, "addq %s, %s\n", arg1->toString(), arg2->toString());//result->toString());
                        //sprintf(buffer, "(add, %s, %s, %s)\n", arg1->toString(), arg2->toString(), result->toString());
                        return buffer;
                    }
        };
        
        // subtract instruction.
        class Sub : public IRCode{
            public:
                    Sub(Instr instrType, Node *a1, Node *a2, Node *r) : IRCode(instrType, a1, a2, r){
                        
                    }
                    
                    char* emit(){
                        char *buffer = new char[256];
                        sprintf(buffer, "subq %s, %s\n", arg1->toString(), arg2->toString());
                        return buffer;
                    }
            
        };
        
        // multiplication instruction.
        class Mul : public IRCode{
            public:
                    Mul(Instr instrType, Node *a1, Node *a2, Node *r) : IRCode(instrType, a1, a2, r){
                        
                    }
                    
                    char* emit(){
                        char *buffer = new char[256];
                        sprintf(buffer, "imulq %s, %s\n", arg1->toString(), arg2->toString());
                        return buffer;                 
                    }
            
        };
        
        class Compare : public IRCode{
            public:
                    Compare(Instr instrType, Node *a1, Node *a2, Node *r) : IRCode(instrType, a1, a2, NULL)
                    {
                        
                    }
                    
                    char* emit(){
                        char *buffer = new char[256];
                        sprintf(buffer, "cmpq %s, %s\n", arg1->toString(), arg2->toString());
                        //sprintf(buffer, "(cmp %s, %s)\n", arg1->toString(), arg2->toString());
                        return buffer;
                    }
            
        };
        
        // Jump Instruction. [je, jne, jg, jge, jl, jle]
        class JumpIfEqual : public IRCode{
            public:
                    JumpIfEqual(Instr instrType, Node *a1, Node *a2, Node* r) : IRCode(instrType, a1, NULL, NULL)
                    {
                        
                    }
                    
                    char* emit(){
                        char *buffer = new char[256];
                        sprintf(buffer, "je %s\n", arg1->toString());
                        //sprintf(buffer, "(je, %s)\n", arg1->toString());
                        return buffer;
                    }
        };
        
        // unconditional jump instruction.
        class Jump : public IRCode{
            public:
                    Jump(Instr instrType, Node *a1, Node *a2, Node *r) : IRCode(instrType, a1, NULL, NULL)
                    {
                        
                    }
                    
                    char* emit(){
                        char *buffer = new char[256];
                        sprintf(buffer, "jmp %s\n", arg1->toString());
                        //sprintf(buffer, "(jmp, %s)\n", arg1->toString());
                        return buffer;
                    }
        };
        
        class EmitLabel : public IRCode{
            public:
                    EmitLabel(Instr instrType, Node *a1, Node *a2, Node *r) : IRCode(instrType, a1, NULL, NULL)
                    {
                        
                    }
                    
                    char* emit(){
                        char *buffer = new char[256];
                        sprintf(buffer, "%s:\n", arg1->toString());
                        return buffer;
                    }
            
        };
        
        // push instruction.
        class Push : public IRCode{
            public:
                    Push(Instr instrType, Node *a1) : IRCode(instrType, a1, NULL, NULL)
                    {
                        
                    }
                    
                    char* emit(){
                        char *buffer = new char[256];
                        sprintf(buffer, "pushq %s\n", arg1->toString());
                        //sprintf(buffer, "(push, %s)\n", arg1->toString());
                        return buffer;
                    }
        };

        // pop instruction.
        class Pop : public IRCode{
            public:
                    Pop(Instr instrType, Node *a1) : IRCode(instrType, a1, NULL, NULL){

                    }

                    char* emit(){
                        char *buffer = new char[256];
                        sprintf(buffer, "popq %s\n", arg1->toString());
                        //sprintf(buffer, "(pop, %s)\n", arg1->toString());
                        return buffer;
                    }
        };

        // return statement.
        class Return : public IRCode{
            public:
                    Return(Instr instrType) : IRCode(instrType, NULL, NULL, NULL){

                    }

                    char* emit(){
                        char* buffer = new char[256];
                        sprintf(buffer, "ret\n");
                        //sprintf(buffer, "(ret)\n");
                        return buffer;
                    }
        };

        // call statement.
        class Call : public IRCode{
            public:
                    Call(Instr instrType, Node *a1) : IRCode(instrType, a1, NULL, NULL){

                    }

                    char* emit(){
                        char* buffer = new char[256];
                        Identifier *id = CAST_TO(Identifier, arg1);
                        sprintf(buffer, "call %s\n", id->getName());
                        //sprintf(buffer, "(call %s)\n", arg1->toString());
                        return buffer;
                    }

        };

        // indirect function call.
        class IndirectCall: public IRCode{
            public:
                    IndirectCall(Instr instrType, Node *a1): IRCode(instrType, a1, NULL, NULL){

                    }

                    char* emit(){
                        char* buffer = new char[256];
                        sprintf(buffer, "call *%s\n", arg1->toString());
                        return buffer;
                    }
        };

        // emit instruction.
        class Emit : public IRCode{
            public:
                    Emit(Instr instrType, Node* a1) : IRCode(instrType, a1, NULL, NULL){

                    }

                    char* emit(){
                        char* buffer = new char[256];
                        sprintf(buffer, "%s\n", arg1->toString());
                        return buffer;
                    }
        };
    }// end of ir namespace.
  }// end of codegen namespace.   
}// end of yacl namespace.
#endif  
