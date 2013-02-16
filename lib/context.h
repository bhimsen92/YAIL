#include<iostream>
#include<cstdlib>
#include<map>
#include<stack>
#include "types/object.h"
#include "concurrent/thread.h"

using namespace std;
#ifndef __CONTEXT
#define __CONTEXT

class Context{
    private:
            map<char*, Object*> symbolTable;
            stack<Thread*> spawnStack;
    public:
            /** 
            * getter functions 
            */
            map< char*, Object* > getSymbolTable(){
                return symbolTable;
            }
            
            stack< Thread* > getSpawnStack(){
                return spawnStack;
            }
            
            /**
            * setter functions.
            */
            void setSymbolTable( map< char*, Object* > symTab ){
                symbolTable = symTab;
            }
            
            void setSpawnStack( stack< Thread* > sStack ){
                spawnStack = sStack;
            }
            
            void put( char* ident, Object* value ){
                symbolTable[ ident ] = value;
            }
            Object* get( char* ident ){
                return symbolTable[ ident ];
            }
};
#endif
