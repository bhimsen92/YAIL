#include<iostream>
#include<cstdlib>
#include<string>
#include<map>
#include<stack>
#include "headers/context.h"

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
