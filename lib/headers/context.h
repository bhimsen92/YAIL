#include<iostream>
#include<cstdlib>
#include<string>
#include<map>
#include<list>
#include "object.h"
#include "node.h"

#ifndef __CONTEXT
#define __CONTEXT
using namespace std;
using namespace bnk_types;
class Context{
    private:
            map<string, Object*> *symbolTable;
            Context *enclosingEnv;
//            stack<Thread*> spawnStack;
    public:
            Context(void){
                enclosingEnv = NULL;
                symbolTable = new map< string, Object* >();
            }
            ~Context(void){                
                if( enclosingEnv != NULL )
                    delete enclosingEnv;
                delete symbolTable;
            }
            map< string, Object* >* getSymbolTable();    
//            stack< Thread* > getSpawnStack();
            void setSymbolTable( map< string, Object* > *symTab );
//            void setSpawnStack( stack< Thread* > sStack );
            void put( string ident, Object* value );
            void setEnclosingContext( Context *altContext ){
                enclosingEnv = altContext;
            }
            bool hasEnclosingContextSet(void){
                return enclosingEnv != NULL;
            }
            Context* getEnclosingContext(void){
                return enclosingEnv;
            }
            Object* get( string ident );
            bool isBound( bnk_astNodes::Identifier *id );
};
#endif
