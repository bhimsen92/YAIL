#include<iostream>
#include<cstdlib>
#include<string>
#include<map>
#include<pthread.h>
#include "headers/context.h"
#include "headers/node.h"

using namespace std;
map< string, Object* >* Context::getSymbolTable(){
    return symbolTable;
}
void Context::setSymbolTable( map< string, Object* > *symTab ){
    symbolTable = symTab;
}

void Context::put( string ident, Object* value ){
    //pthread_mutex_lock(&door);
    (*symbolTable)[ ident ] = value;
    //pthread_mutex_unlock(&door);
    //symbolTable->insert( pair< string, Object* >( ident, value ) );
}

Object* Context::get( string ident ){
    //cout<<"In context get..."<<endl;
    Object *rval = NULL;
    //pthread_mutex_lock(&door);
    if(symbolTable->count(ident) > 0){
        rval = (*symbolTable)[ident];
    }
    if(rval == NULL){
        Context *tmp = enclosingEnv;
        while( tmp != NULL && rval == NULL){
            rval = tmp->get(ident);
            tmp = tmp->getEnclosingContext();
        }
    }
    //pthread_mutex_unlock(&door);
    return rval;
}

bool Context::isBound( bnk_astNodes::Identifier *id ){
    string varName = id->getName();
    if( (*symbolTable)[ varName ] != NULL ){
        return true;
    }
    else{
        return false;
    }
}
