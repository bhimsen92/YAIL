#include<iostream>
#include<cstdlib>
#include<string>
#include<map>
#include<stack>
#include "headers/context.h"
#include "headers/node.h"

using namespace std;
map< string, Object* > Context::getSymbolTable(){
    return symbolTable;
}
void Context::setSymbolTable( map< string, Object* > symTab ){
    symbolTable = symTab;
}

void Context::put( string ident, Object* value ){
    symbolTable[ ident ] = value;
}

Object* Context::get( string ident ){
    return symbolTable[ ident ];
}

bool Context::isBound( bnk_astNodes::Identifier *id ){
    string varName = id->getName();
    if( symbolTable[ varName ] != NULL ){
        return true;
    }
    else{
        return false;
    }
}
