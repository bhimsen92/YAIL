#include<iostream>
#include<cstdlib>
#include<string>
#include<map>
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
    (*symbolTable)[ ident ] = value;
    //symbolTable->insert( pair< string, Object* >( ident, value ) );
}

Object* Context::get( string ident ){
    Object *rval = (*symbolTable)[ ident ];
    if( rval == NULL ){
        if( enclosingEnv != NULL ){
            rval = enclosingEnv->get( ident );
        }
    }
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
