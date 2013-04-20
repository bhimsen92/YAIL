#include<iostream>
#include<cstring>
#include<list>
#include<vector>
#include<cstdio>
#include "tokens.h"
#include "bnKapi.h"
#include "../codegen/headers/instr.h"

#ifndef __NODE_TYPE
#define __NODE_TYPE
using namespace std;
using namespace yacl::codegen;

namespace yacl{
    namespace ast{
// forward declarations.
class Type;
class Register;

    class Node{
        protected:
                   // nodeType is for ast.
                   int nodeType;
                   // this type of value this node contains[ for symantic checking]
                   Type *dataType;
                   // this is for typeClass.
                   int typeClass;
                   int tmpFlag;
        public:
                Node( int nType );
                int getType(void);
                virtual char* toString(void){ cout<<"Node::toString() executed;"<<endl; exit(1);}
                virtual void dummy(void){}
                virtual void addLocation(Node* loc){ cout<<"Node::addLocation() executed"<<endl; exit(1);}
                virtual Node* getLocation(void){ cout<<"Node::getLocation() executed"<<endl; exit(1);}
                virtual void removeLocation(void){ cout<<"Node::removeLocation executed"<<endl; exit(1);}
                virtual bool hasLocationAdded(){ cout<<"Node::hasLocationAdded executed"<<endl; exit(1);}
                bool is(int t){
                    return nodeType == t;
                }
                void setDataType(Type *dtype){
                    dataType = dtype;
                }
                void setTypeClass(int cls){
                    typeClass = cls;
                }
                Type* getDataType(){
                    return dataType;
                }
                int getTypeClass(){
                    return typeClass;
                }
    };

    class Operands{
        protected:
                vector<Node*> operands;
        public:
                void push_back( Node* node ){
                    operands.push_back( node );
                }
            
                Node* get( int index ){
                    if( index < operands.size() ){
                        return operands[ index ];
                    }
                    return NULL;
                }
            
                void pop_front(void){
                    operands.erase( operands.begin() );
                }
                
                int size(void){
                    return operands.size();
                }
    };  

    class Identifier: public Node{
        protected:
                   char* name;
                   // offset is used to calculate the address of
                   // identifier from the frame pointer.
                   int   offset;
                   // address descriptor for storing location,
                   // of the value of this variable.
                   vector<Node*> addressDescriptor;
        public:
               Identifier(char* n);
               char* getName(void);
               int   getOffset(void);
               void  setOffset(int pos){
                   offset = pos;
               }

               void addLocation(Node* loc){
                    addressDescriptor.push_back(loc);
               }
               
               Node* getLocation(void){
                    if(addressDescriptor.size() > 0){
                        return addressDescriptor[0];
                    }
                    else{
                        return NULL;
                    }
               }

               void removeLocation(){
                    if(addressDescriptor.size() > 0){
                        addressDescriptor.erase(addressDescriptor.begin(), addressDescriptor.begin() + 1);
                    }
               }

               bool isInRegister(){
                    if(addressDescriptor.size() != 0)
                        return true;
                    else
                        return false;
               }

               char* toString(){
                    char *buffer = new char[256];
                    if(offset > 0)
                        sprintf(buffer, "-%d(%s)", offset, "%rbp");
                    else{
                        sprintf(buffer, "%d(%s)", offset, "%rbp");
                    }
                    return buffer;
               }
    };

    class String: public Node{
        protected:
                    char* string;
                    int length;
        public:
                 String( char* str );
                 char* getString(void);
                 int getLength(void);
                 char* removeQuotes( char* str, int length );
                 char* toString(){ return string; }
    };

    class Integer: public Node{
        protected:
            int value;
    
        public:
            Integer(char* str);
            Integer(int v) : Node(__integer){
                value = v;
            }
            void toInteger( char* str );
            int getValue(void);
            void setValue( int val );
            char* toString(){
                char *rval = new char[32];
                sprintf(rval, "$%d", value);
                return rval;
            }
    };  

    class Double: public Node{
        protected:
            double value;
        public:
            Double( char *str );
            void toDouble( char *str );
            double getValue(void);
            void setValue( double val );
            char* toString(){
                char *rval = new char[32];
                sprintf(rval, "%f", value);
                return rval;
            }
    };  

    class Type: public Node{
        protected:
                // type holds the datatype info.
                int type;
                // width of the type for storage purpose.
                int width;
        public:
                Type(int _t, int w);
                int getDataType(void);
                int getDataWidth(void);
                void setDataType(int _type);
                void setDataWidth(int w);
                static Type* getType(int dtype){
                    if(dtype == __integer){
                        return new Type(__integer, 8);
                    }
                    return NULL;
                }
                
                static int getTypeClass(Type *dtype){
                    if(dtype == NULL){
                        cout<<"It is null. I am doomed..\n";
                    }
                    int dt = dtype->getDataType();
                    if(dt == __integer || dt == __double)
                        return NumberClass;
                }
    };

    class Expression: public Node{
        private:
                Node *expNode;
        public:
                Expression( Node* n );
                Node* getNode(void);
                void setNode( Node* n );
    };  

    class Operator: public Node{
        protected:
                  Operands *operands;
                  int nops;
        public:
                Operator( int nType, int nOps, Operands *ops );
                Operands* getOperands(void);
                int getOpsLength(void);
    };  

    class Nothing: public Node{
        public:
                  Nothing(void);
                  void* getValue(void);
    };  

    class List : public Node{
        protected:
                  list<Node*> nodeList;
        public:
                 List( int nodeType );
                 void push_back( Node* node );
                 Node* pop_front(void);
                 Node* get( int index );
                 int getLength(void);
                 void clear();
                 int empty();
    };  

    class VariableList : public List{
        public:
            VariableList( int nodeType );
    };

    class FormalParameterList : public List{
        public:
                 FormalParameterList();
    };  

    class ValueList : public List{
        public:
                ValueList();
    };  

    class FormalParameter: public Node{
        private:
                int   dataType;
                char* parameterName;
        public:
                FormalParameter( int _type, char* pName );
                FormalParameter( Node* _type, Node* ident );
                int getDataType(void);
                char* getParameterName(void);
    };  

    class ArgumentList : public List{
        public:
                 ArgumentList(void);
    };  

    class StatementList : public List{
        public:
                 StatementList(void);
    };

    class Temp : public Node{
        private:
                char t[32];
                int  offset;
        public:
                Temp(int dtype) : Node(dtype){
                    sprintf(t, "temp");
                    tmpFlag = true;
                }
                
                void setOffset(int pos){
                    offset = pos;
                }
                
                int getOffset(){
                    return offset;
                }
                
                char* toString(){
                    char *buffer = new char[256];
                    sprintf(buffer, "%d(temp)", offset);
                    return buffer;
                }
    };

    class Register : public Node{
        private:
                Reg _register;
                static int reg[16];
                static bool alreadyUsed[16];
                static bool instanciated[16];
                static int  len;
                static vector<Register*> registerAllocated;
                vector<Node*> registerDescriptor;
                //char regName[8];
        public:
                Register(int dtype) : Node(dtype){
                    /*len = 16;
                    for(int i = 0; i < len; i++){
                        reg[i] = i;
                    }*/                   
                    _register = (Reg)getReg();
                    instanciated[_register] = true;
                    registerAllocated.push_back(this);
                }
                
                Register(int dtype, int regt): Node(dtype){
                    _register = (Reg)regt;
                    if(!instanciated[_register]){
                        instanciated[_register] = true;
                        registerAllocated.push_back(this);
                    }
                    alreadyUsed[_register] = true;
                }

                static Register* getRegister(int dtype){
                    Reg r = (Reg)getReg();
                    if(!instanciated[r]){
                        return new Register(dtype, r);
                    }
                    else if( r != -1){
                        return getRegisterFromAllocated(dtype, r);
                    }
                    else{
                        return Register::spill();
                    }
                }

                static Register* getRegister(int dtype, int regt){                    
                    if(!instanciated[regt]){
                        return new Register(dtype, regt);
                    }
                    else{
                        return getRegisterFromAllocated(dtype, regt);
                    }
                }

                static int allocatedRegisterLength(){
                    //return registerAllocated.size();
                    int val = 0;
                    for(int i = 0; i < len; i++){
                        if(alreadyUsed[i])
                            val++;
                    }
                    return val;
                }

                static Register* getRegisterFromAllocated(int dtype, int reg){
                    for(int i = 0; i < registerAllocated.size(); i++){
                        if(reg != rax && reg != rsp && reg != rbp && 
                           registerAllocated[i]->_register == reg){
                            Register::setReg(reg);
                            Register::alreadyUsed[reg] = true;
                            return registerAllocated[i];
                        }
                    }
                    return new Register(dtype, reg);
                }

                static Register* spill(){
                    int size = registerAllocated.size();
                    int index = 0;
                    vector<Register*>::iterator it = registerAllocated.begin();
                    while(index < size){                        
                        Register *reg = *it;
                        if(!reg->is(rsp) && !reg->is(rbp) && Register::alreadyUsed[reg->_register]){
                            // remove this register from the list.                    
                            Register::alreadyUsed[reg->_register] = false;
                            registerAllocated.erase(it, it + 1);
                            registerAllocated.push_back(*it);
                            return reg;
                        }
                        /*else if(!reg->is(rsp) && !reg->is(rbp)){
                            registerAllocated.erase(it, it + 1);
                            registerAllocated.push_back(*it);
                            Register::alreadyUsed[reg->_register] = false;
                            return reg;
                        }*/
                        index++;
                        it++;
                    }
                    // if control comes upto this => no registers have been 
                    // allocated.
                    return NULL;
                }
                
                bool isFree(){
                    return !alreadyUsed[_register];
                }
                
                bool is(Reg reg){
                    return _register == reg;
                }

                char* toString(){
                    if(_register == rax)
                        return (char*)"%rax";
                    else if(_register == rbx)
                        return (char*)"%rbx";
                    else if(_register == rcx)
                        return (char*)"%rcx";
                    else if(_register == rdx)
                        return (char*)"%rdx";
                    else if(_register == rsi)
                        return (char*)"%rsi";
                    else if(_register == rdi)
                        return (char*)"%rdi";
                    else if(_register == rbp)
                        return (char*)"%rbp";
                    else if(_register == rsp)
                        return (char*)"%rsp";
                    else if(_register == r8)
                        return (char*)"%r8";
                    else if(_register == r9)
                        return (char*)"%r9";
                    else if(_register == r10)
                        return (char*)"%r10";
                    else if(_register == r11)
                        return (char*)"%r11";
                    else if(_register == r12)
                        return (char*)"%r12";
                    else if(_register == r13)
                        return (char*)"%r13";
                    else if(_register == r14)
                        return (char*)"%r14";
                    else if(_register == r15)
                        return (char*)"%r15";                                                                                                                                                                    
                }
                
                static int getReg(){
                    // go through "used" array.
                    // return first unused register.
                    for(int i = 0; i < len; i++){
                        if(!alreadyUsed[i] && i != rax && i != rsp && i != rbp){
                            alreadyUsed[i] = true;
                            return reg[i];
                        }
                    }
                    return -1;
                }
                
                static bool areAvailable(){
                    for(int i = 0; i < len; i++){
                        if(!alreadyUsed[i])
                            return true;
                    }
                    return false;
                }

                /*static Register* getRegister(Reg reg){
                    Register *val = NULL;
                    for(int i = 0; i < registerAllocated.size(); i++){
                        if(registerAllocated[i]->_register == reg){
                            return registerAllocated[i];
                        }
                    }
                    if(!Register::alreadyUsed[reg]){
                        return new Register(__reg, reg);
                    }
                    else{
                        cout<<"Error..."<<endl;
                        exit(1);
                    }
                }*/

                void unsetReg(){
                    alreadyUsed[_register] = false;
                }

                static void printUsed(){
                    for(int i = 0; i < len; i++){
                        if(alreadyUsed[i]){
                            cout<<"used: "<<i<<" ";
                        }
                    }
                    cout<<endl;
                }
                
                static void setReg(int i){
                    alreadyUsed[i] = true;
                }

                static void clearAll(){
                    for(int i = 0; i < len; i++){
                        alreadyUsed[i] = false;
//                        if(registerAllocated.size() > 0)
//                            registerAllocated.pop_back();
                    }
                }
                
                bool equals(Node *reg){
                    Register *other = CAST_TO(Register, reg);
                    if(reg != NULL){
                        return other->_register == this->_register;
                    }
                    else
                        return false;
                }

                void addLocation(Node* loc){
                    registerDescriptor.push_back(loc);
                }

                Node* getLocation(void){
                    if(registerDescriptor.size() > 0){
                        return registerDescriptor[0];
                    }
                    else{
                        return NULL;
                    }
                }

                void removeLocation(){
                    if(registerDescriptor.size() > 0){
                        registerDescriptor.erase(registerDescriptor.begin(), registerDescriptor.begin() + 1);
                    }
                }

                bool hasLocationAdded(){
                    if(registerDescriptor.size() > 0)
                        return true;
                    else
                        return false;
                }

                int getRegIndex(){
                    return (int)_register;
                }

                static Reg functReg(int i){
                    int functRegisters[] = { rdi, rsi, rdx, rcx, r8, r9};
                    return (Reg)functRegisters[i];
                }
    };
    
    class Label : public Node{
        private:
                char *label;
                static int counter;
        public:
                Label() : Node(-1){
                    label = new char[256];
                    sprintf(label, "L%d", counter);
                    counter++;
                }
                
                Label(Identifier *id) : Node(-1){
                    char *l = id->getName();
                    label = new char[strlen(l) + 1];
                    strcpy(label, l);
                }
                char* toString(){
                    return label;
                }
    };
    
    class Function : public Node{
        protected:
                vector<Identifier*> parameters;
                Type *returnType;
        public:
                Function() : Node(-1){
                    
                }
                
                void addParamterType(Identifier *fp){
                    parameters.push_back(fp);
                }
                
                void addReturnType(Type *rt){
                    returnType = rt;
                }

                Type* getReturnType(){
                    return returnType;
                }
    };
    
  } // end of ast namespace.
} // end of yacl namespace.
#endif
