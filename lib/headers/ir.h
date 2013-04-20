#include<iostream>
#include<cstdio>
#include<cstdlib>
#include "node.h"
#include "instr.h"

#ifndef __IRCODE
#define __IRCODE
using namespace bnk_astNodes;

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
}
#endif
