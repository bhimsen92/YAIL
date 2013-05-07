/**
    The following code contains Context class which is used to store variables stored in that context.
    The Context Class contains a hash table to store the names and their corresponding objects.
    Before adding any name to the context, it is checked to make sure that it does not exist in the context, 
    If it does error is thrown.
    Created by : Bhimsen S K
*/
#ifndef __CONTEXT
#define __CONTEXT
#include<iostream>
#include<cstdlib>
#include<string>
#include<map>
#include<list>
#include<pthread.h>
#include "object.h"
#include "node.h"

using namespace std;
using namespace bnk_types;
class Context{
    private:
            map<string, Object*> *symbolTable;
            Context *enclosingEnv;
            pthread_mutex_t door;
    public:
            Context(){
                enclosingEnv = NULL;
                symbolTable = new map< string, Object* >();
            }
            ~Context(void){
                //if( enclosingEnv != NULL )
                    //delete enclosingEnv;
                //delete symbolTable;
            }
            map< string, Object* >* getSymbolTable();    
            void setSymbolTable( map< string, Object* > *symTab );
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
