#include<iostream>
#include<cstdlib>
#include<string>
#include<map>
#include<vector>
//#include "object.h"
#include "node.h"
#include "../codegen/headers/ir.h"

#ifndef __CONTEXT
#define __CONTEXT
using namespace std;
using namespace yacl::ast;
using namespace yacl::codegen::ir;
class Context{
    private:
            //map<string, Object*> *symbolTable;
            // this symtab var is for treewalker
            map<string, Node*> *symtab;
            //Context *enclosingEnv;
            // for keeping track of variable posistions with respect to stack.
            // useful while codegen.
            int offset;
            // memory field will hold the amount storage that needs to be allocated on 
            // the stack.
            int memory;
            // variable declaration list, holds the variables that are defined in this context.
            // order matters. this list will help in generating the addresses for the vars, has 
            // nothing to do with symtab var defined above. If somebody says it consumes memory, i do not care.
            vector<Identifier*> variables;
            // for temps, same reason as above.
            vector<Temp*> temps;
            // list of instructions that needs to be executed in this context.
            vector<IRCode*> instructions;
//            stack<Thread*> spawnStack;
    public:
            Context(void){
                //enclosingEnv = NULL;
                //symbolTable = new map< string, Object* >();
                symtab = new map<string, Node*>();
                offset = 0;
                memory = 0;
            }
            ~Context(void){                
                //if( enclosingEnv != NULL )
                //    delete enclosingEnv;
                //delete symbolTable;
                delete symtab;                
            }
//            map< string, Object* >* getSymbolTable();    
//            stack< Thread* > getSpawnStack();
            void setSymbolTable( map< string, Object* > *symTab );
//            void setSpawnStack( stack< Thread* > sStack );
//            void put( string ident, Object* value );
            void put(string ident, Node *value){
                (*symtab)[ident] = value;
            }
            
            Node* get(string ident, int dummy){
                return (*symtab)[ident];
            }
            
//            void setEnclosingContext( Context *altContext ){
//                enclosingEnv = altContext;
//            }
//            bool hasEnclosingContextSet(void){
//                return enclosingEnv != NULL;
//            }
//            Context* getEnclosingContext(void){
//                return enclosingEnv;
//            }
//            Object* get( string ident );
//            bool isBound( Identifier *id );
            bool isBound(Identifier *id, int dummy){
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
            
            void updateStorage(int byThisMuch){
                memory += byThisMuch;
            }
            
            void addVar(Identifier *id){
                variables.push_back(id);
            }
            
            void addTemp(Temp *tmp){
                temps.push_back(tmp);
            }
            
            void addInstruction(IRCode* ircode){
                instructions.push_back(ircode);
            }
            
            void generateCode(){
                // logic for generating code.
                // first allocate the memory with value stored in memory field.
                // then update the offsets for variables and temps.
                // then generate the instructions.
                
                // update offsets of variables.
                for(int i = 0, len = variables.size(); i < len; i++){
                    Identifier *id = variables[i];
                    id->setOffset(getOffset());
                    updateOffset(id->getDataType()->getDataWidth());
                }
                
                // update offsets of temps.
                for(int i= 0, len = temps.size(); i < len; i++){
                    Temp *tmp = temps[i];
                    tmp->setOffset(getOffset());
                    updateOffset(tmp->getDataType()->getDataWidth());
                }
                
                // generate allocate instructions.
                IRCode *allocInstr = new Allocate(allocate, new Integer(memory), NULL, NULL);
                cout<<allocInstr->emit()<<endl;
                // now go through instructions present in this context and emit.
                for(int i = 0, len = instructions.size(); i < len; i++){
                    IRCode *instr = instructions[i];
                    cout<<instr->emit()<<endl;
                }
            }
};
#endif
