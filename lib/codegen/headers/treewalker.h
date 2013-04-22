#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<cstring>
#include<map>
#ifndef __TREEWALKER
#define __TREEWALKER
#include "../../headers/bnKapi.h"
#include "../../headers/tokens.h"
#include "../../headers/node.h"
#include "../../headers/context.h"
#include "binaryop.h"
#include "ir.h"

using namespace std;
using namespace yacl::ast;
using namespace yacl::codegen::ir;
using namespace yacl::codegen::binaryop;

class TreeWalker{
    private:
            //map<string, BuiltInFunction> builtins;
            int insideFunctionCounter;
            vector<Context*> *contexts;
            vector<Data*> staticDataValues;
    public:
        TreeWalker(){
            //this->loadBuiltIns();
            insideFunctionCounter = 0;
            contexts = new vector<Context*>();
        }
        //bool isCallable( Object* obj );
        Node* evaluate( Node* astNode, Context* execContext, Type *dtype );
        Node* execOperation( Operator* opNode, Context* execContext, BinaryOperation *op );
        bool isBuiltInFunction( Identifier *functName );
        bool isUserDefinedFunction( Identifier *functName, Context *execContext );
        Node* evaluateBuiltInFunction( Identifier *functName, Operands *operands, Context *execContext );
        Node* evaluateUserDefinedFunction( Identifier *functName, Operands *operands, Context *execContext );
        //void loadBuiltIns(void);
        //BuiltInFunction getBuiltInFunction( Identifier *functName );
        void errorMessage( int size, ... );
        bool isReturnType( Node *node );

        void addContext(Context *ctx){
            contexts->push_back(ctx);
        }
        
        vector<Context*>* getContexts(){
            return contexts;
        }

        char* pre(){
            char *buffer = new char[1024  * (staticDataValues.size() + 1)];
            char *tmpBuffer = new char[2048];
            int length = staticDataValues.size();
            memset(buffer, '\0', 1024  * (staticDataValues.size() + 1));
            for(int i = 0; i < length; i++){
                //cout<<"Hello world...\n";
                sprintf(tmpBuffer, "%s", staticDataValues[i]->toString());
                strcat(buffer, tmpBuffer);
            }
            sprintf(tmpBuffer, "%s", ".section .text\n");
            //cout<<"In pre: "<<tmpBuffer<<endl;
            strcat(buffer, tmpBuffer);
            return buffer;
        }

        char* post(){
            const char* buffer = ".globl main\n.type main, @function\n""main:\n";
            //const char* buffer = "main:\n";
            return (char*)buffer;
        }

        char* end(){
            //const char* buffer = "mov %rax, %rdi\nmov $60, %rax\nsyscall\n";
            const char* buffer = "mov %rbp, %rsp\n" "pop %rbp\n" "ret\n";
            return (char*)buffer;
        }

        void addDataObject(Data *obj){
            staticDataValues.push_back(obj);
        }
};
#endif
