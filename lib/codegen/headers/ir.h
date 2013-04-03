#include<iostream>
#include<cstdio>
#include<cstdlib>
#include "../../headers/node.h"
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
                        sprintf(buffer, "(allocate, %s, NULL, NULL)\n", arg1->toString());
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
                        sprintf(buffer, "(mov, %s, , %s)\n", arg1->toString(), result->toString());
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
                        sprintf(buffer, "(add, %s, %s, %s)\n", arg1->toString(), arg2->toString(), result->toString());
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
                        sprintf(buffer, "(cmp %s, %s)\n", arg1->toString(), arg2->toString());
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
    }// end of ir namespace.
  }// end of codegen namespace.   
}// end of yacl namespace.
#endif  
