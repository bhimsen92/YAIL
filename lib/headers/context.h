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
            map<string, bnk_astNodes::Node*> *symtab;
            Context *enclosingEnv;
            // for keeping track of variable posistions with respect to stack.
            // useful while codegen.
            int offset;
//            stack<Thread*> spawnStack;
    public:
            Context(void){
                enclosingEnv = NULL;
                symbolTable = new map< string, Object* >();
                symtab = new map<string, bnk_astNodes::Node*>();
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
            void put(string ident, bnk_astNodes::Node *value){
                (*symtab)[ident] = value;
            }
            
            bnk_astNodes::Node* get(string ident, int dummy){
                return (*symtab)[ident];
            }
            
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
            bool isBound( bnk_astNodes::Identifier *id, int dummy){
                string varName = id->getName();
                if( (*symtab)[varName] != NULL ){
                    return true;
                }
                else{
                    return false;
                }
            }
            void updateOffset(int amount){
                offset += amount;
            }
            
            int getOffset(){
                return offset;
            }
};
#endif
