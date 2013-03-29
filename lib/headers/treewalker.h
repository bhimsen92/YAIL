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
using namespace ir;
//using namespace bnk_builtins;

#ifndef __TREEWALKER
#define __TREEWALKER

class TreeWalker{
    private:
            //map<string, BuiltInFunction> builtins;
            int insideFunctionCounter;
            int offset;
            vector<IRCode*> irCodeList;
    public:
        TreeWalker(){
            //this->loadBuiltIns();
            insideFunctionCounter = 0;
            //irCodeList = new vector<IRCode*>();
            offset = 0;
        }
        //bool isCallable( Object* obj );
        bnk_astNodes::Node* evaluate( Node* astNode, Context* execContext, Type *dtype );
        Node* execOperation( Operator* opNode, Context* execContext, BinaryOperation *op );
        bool isBuiltInFunction( Identifier *functName );
        bool isUserDefinedFunction( Identifier *functName, Context *execContext );
        Node* evaluateBuiltInFunction( Identifier *functName, Operands *operands, Context *execContext );
        Node* evaluateUserDefinedFunction( Identifier *functName, Operands *operands, Context *execContext );
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
        
        void generateIRCode(){
            int i;
            cout<<"Generating code.."<<endl;
            for(i = 0; i < irCodeList.size(); i++){
                cout<<irCodeList[i]->emit();
            }
        }
};
#endif
