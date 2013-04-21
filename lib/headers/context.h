#include<iostream>
#include<cstdlib>
#include<string>
#include<map>
#include<vector>
//#include "object.h"
#include "bnKapi.h"
#include "node.h"
#include "tokens.h"
#include "../codegen/headers/instr.h"
#include "../codegen/headers/ir.h"

#ifndef __CONTEXT
#define __CONTEXT
using namespace std;
using namespace yacl::ast;
using namespace yacl::codegen::ir;
class Context{
    private:
            // this symtab var is for treewalker
            int contextId;
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
            // Register related attributes.
            int reg[16];
            bool alreadyUsed[16];
            bool instanciated[16];
            int  len;
            vector<Register*> registerAllocated;
            static int exitLabelCounter;
            static int contextIdCounter;
    public:
            Context(void){
                offset = 8;
                reverseOffset = 0;
                memory = 0;
                len = 16;
                ctxChain = NULL;
                exitLabelCounter++;
                // initialize alreadyUsed array to false.
                for(int i = 0; i < len; i++){
                    alreadyUsed[i] = false;
                    instanciated[i] = false;
                    reg[i] = i;
                }
                contextId = contextIdCounter;
                Context::contextIdCounter++;
                //cout<<"Context instanciated...: "<<contextIdCounter<<endl;
            }

            ~Context(void){
            }

            int getContextId(){
                return contextId;
            }

            Register* getRegister(){
                int _register = getReg();
                if(_register == -1){
                    return NULL;
                }
                else if(!instanciated[_register]){
                    // create the register object.
                    // set the respective instantiated bit to true.
                    // return the object.
                    Register *val = new Register(__reg, _register);
                    instanciated[_register] = true;
                    registerAllocated.push_back(val);
                    //cout<<"Reg: "<<val->toString()<<", Register allocated: "<<registerAllocated.size()<<endl;
                    return val;
                }
                else{
                    return getRegisterFromAllocated(_register);                    
                }
            }

            Register* getRegister(int _register){
                alreadyUsed[_register] = true;
                if(!instanciated[_register]){
                    Register *val = new Register(__reg, _register);
                    instanciated[_register] = true;
                    registerAllocated.push_back(val);
                    //cout<<"Reg: "<<val->toString()<<", Register allocated: "<<registerAllocated.size()<<endl;
                    return val;                    
                }
                else{
                    return getRegisterFromAllocated(_register);
                }
            }

            int getReg(){
                for(int i = 0; i < len; i++){
                    if(!alreadyUsed[i]){
                        alreadyUsed[i] = true;
                        return i;
                    }
                }
                return -1;
            }

            bool free(int _register){
                return !alreadyUsed[_register];
            }

            void setAvailabilityFlag(int _register){
                alreadyUsed[_register] = true;
            }

            void unsetAvailabilityFlag(int _register){
                alreadyUsed[_register] = false;
            }

            Register* getRegisterFromAllocated(int _register){
                int length = registerAllocated.size();
                for(int i = 0; i < length; i++){
                    if(registerAllocated[i]->is((Reg)_register)){
                        return registerAllocated[i];
                    }
                }
                return NULL;
            }

            void clearAll(){
                int length = registerAllocated.size();
                for(int i = 0; i < len; i++){
                    alreadyUsed[i] =false;
                }
                //cout<<"Length: "<<length<<endl;
                for(int i = 0; i < length; i++){
                    //cout<<"i: "<<i<<endl;
                    if(registerAllocated[i] != NULL)
                        registerAllocated[i]->removeLocation();
                }
            }

            Register* spill(){
                int length = registerAllocated.size(), i = 0;
                vector<Register*>::iterator it = registerAllocated.begin();
                while(i < length){
                    Register *reg = *it;
                    if(!reg->is(rax) && !reg->is(rsp) && !reg->is(rbp) && alreadyUsed[reg->getRegIndex()]){
                        alreadyUsed[reg->getRegIndex()] = false;
                        return reg;
                    }
                    i++;
                    it++;
                }
                return NULL;
            }

            int getRegisterAllocatedLength(){
                return registerAllocated.size();
            }

            bool areAvailable(){
                for(int i = 0; i < len; i++){
                    if(!alreadyUsed[i])
                        return true;
                }
                return false;
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
            void printUsed(){
                    for(int i = 0; i < len; i++){
                        if(alreadyUsed[i]){
                            cout<<"used: "<<i<<" ";
                        }
                    }
                    cout<<endl;
            }            
};
#endif