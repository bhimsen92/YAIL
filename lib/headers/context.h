#include<iostream>
#include<cstdlib>
#include<string>
#include<map>
#include<vector>
//#include "object.h"
#include "bnKapi.h"
#include "node.h"
#include "tokens.h"
#include "../codegen/headers/ir.h"

#ifndef __CONTEXT
#define __CONTEXT
using namespace std;
using namespace yacl::ast;
using namespace yacl::codegen::ir;
class Context{
    private:
            // this symtab var is for treewalker
            map<string, Node*> symtab;
            Context *ctxChain;
            //vector<Symbol*> symtab;
            // for keeping track of variable posistions with respect to stack.
            // useful while codegen.
            int offset;
            // for accessing function paramters.
            int reverseOffset;
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
            // list of ids for arguments to the function.
            vector<Identifier*> firstSixArgs;
            vector<Identifier*> arguments;
            static int exitLabelCounter;
    public:
            Context(void){
                //symtab = new map<string, Node*>();
                offset = 8;
                reverseOffset = 0;
                memory = 0;
                ctxChain = NULL;
                exitLabelCounter++;
            }
            ~Context(void){
                //cout<<"Herr: "<<endl;
                //char ch;
                //cin>>ch;
                //delete symtab;
                //cout<<"Destruction called[Context]"<<endl;
            }
            void setSymbolTable( map< string, Object* > *symTab );
            void put(string ident, Node *value){
                symtab[ident] = value;
            }
            
            Node* get(string ident, int dummy){
                Node *val = symtab[ident];
                if(val == NULL){
                    Context *chain = ctxChain;
                    while(chain != NULL){
                        val = chain->get(ident, dummy);
                        if(val == NULL){
                            chain = chain->ctxChain;
                        }
                        else{
                            break;
                        }
                    }
                }
                return val;
            }
            
            void attachContext(Context *ctx){
                ctxChain = ctx;
            }
            bool isBound(Identifier *id, int dummy){
                string varName = id->getName();
                if( symtab[varName] != NULL ){
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
            
            void generateCode(bool flag = false, bool nonFunctionFlag = false){
                // logic for generating code.
                // first allocate the memory with value stored in memory field.
                // then update the offsets for variables and temps.
                // then generate the instructions.
                // for function paramters.
                for(int i = 0, len = firstSixArgs.size(); i < len; i++){
                    Identifier *id = firstSixArgs[i];
                    id->setOffset(getOffset());
                    updateOffset(id->getDataType()->getDataWidth());
                    updateStorage(id->getDataType()->getDataWidth());
                }
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
                //cout<<allocInstr->emit();
                if(!flag){
                    vector<IRCode*>::iterator it = instructions.begin() + 4;
                    instructions.insert(it, allocInstr);
                }
                else if(nonFunctionFlag){
                    vector<IRCode*>::iterator it = instructions.begin() + 2;
                    instructions.insert(it, allocInstr);
                }
                // now go through instructions present in this context and emit.
                for(int i = 0, len = instructions.size(); i < len; i++){
                    IRCode *instr = instructions[i];
                    cout<<instr->emit();
                }
            }            
            void addFunctionParamter(Identifier *id){
                int len = firstSixArgs.size();
                if(len < 6){
                    firstSixArgs.push_back(id);
                }
                else{
                    arguments.push_back(id);
                }
            }

            void clearLocations(){
                map<string, Node*>::iterator it = symtab.begin();
                for(; it != symtab.end(); it++){
                    if(it->second && it->second->is(__identifier))
                        it->second->removeLocation();
                }
            }
            
            char* getExitLabel(){
                char *label = new char[32];
                sprintf(label, "EXIT%d", exitLabelCounter);
                return label;
            }
};
#endif
