#include<iostream>
#include<cstdlib>
#include<string>
#include<map>
#include<stack>
#include "types/object.h"
#include "concurrent/thread.h"

using namespace std;
using namespace bnk_types;

#ifndef __CONTEXT
#define __CONTEXT

class Context{
    private:
            map<string, Object*> symbolTable;
            stack<Thread*> spawnStack;
    public:
            /** 
            * getter functions 
            */
            map< string, Object* > getSymbolTable(){
                return symbolTable;
            }
            
            stack< Thread* > getSpawnStack(){
                return spawnStack;
            }
            
            /**
            * setter functions.
            */
            void setSymbolTable( map< string, Object* > symTab ){
                symbolTable = symTab;
            }
            
            void setSpawnStack( stack< Thread* > sStack ){
                spawnStack = sStack;
            }
            
            void put( string ident, Object* value ){
                symbolTable[ ident ] = value;
            }
            Object* get( string ident ){

                return symbolTable[ ident ];
            }
};
#endif
