#include<iostream>
#include<cstdlib>
#include<string>
#include<map>
#include<stack>
#include "object.h"
#include "node.h"

#ifndef __CONTEXT
#define __CONTEXT
using namespace std;
using namespace bnk_types;
class Context{
    private:
            map<string, Object*> symbolTable;
//            stack<Thread*> spawnStack;
    public:
            /** 
            * getter functions 
            */
            map< string, Object* > getSymbolTable();            
//            stack< Thread* > getSpawnStack();
            void setSymbolTable( map< string, Object* > symTab );
//            void setSpawnStack( stack< Thread* > sStack );
            void put( string ident, Object* value );
            Object* get( string ident );
            bool isBound( bnk_astNodes::Identifier *id );
};
#endif
