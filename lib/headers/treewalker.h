#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
#include<cstring>
#include<map>
#include "bnKapi.h"
#include "node.h"
#include "tokens.h"
#include "context.h"
#include "object.h"
#include "binaryop.h"
#include "ir.h"

using namespace std;
using namespace bnk_astNodes;
//using namespace bnk_builtins;

#ifndef __TREEWALKER
#define __TREEWALKER

class TreeWalker{
    private:
            //map<string, BuiltInFunction> builtins;
            int insideFunctionCounter;
            int offset;
            vector<IRCode> irCodeList;
    public:
        Interpreter(){
            //this->loadBuiltIns();
            insideFunctionCounter = 0;
            irCodeList = new vector<IRCode>();
            offset = 0;
        }
        //bool isCallable( Object* obj );
        bnk_types::Object* evaluate( Node* astNode, Context* execContext, int dataTypeInfo );
        Object* execOperation( Operator* opNode, Context* execContext, BinaryOperation *op );
        bool isBuiltInFunction( Identifier *functName );
        bool isUserDefinedFunction( Identifier *functName, Context *execContext );
        Object* evaluateBuiltInFunction( Identifier *functName, Operands *operands, Context *execContext );
        Object* evaluateUserDefinedFunction( Identifier *functName, Operands *operands, Context *execContext );
        //void loadBuiltIns(void);
        //BuiltInFunction getBuiltInFunction( Identifier *functName );
        void errorMessage( int size, ... );
        bool isReturnType( Object *obj );
        void add(IRCode *irc){
            irCodeList.push_back(irc);
        }
        void updateOffset(int size){
            offset += size;
        }
        int getCurrentOffset(){
            return offset;
        }
};
#endif
