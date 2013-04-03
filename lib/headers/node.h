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
// forward declaration.
class Type;
        
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
                virtual char* toString(void){}
                virtual void dummy(void){}
                bool isTmp(){
                    return tmpFlag;
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
        public:
               Identifier(char* n);
               char* getName(void);
               int   getOffset(void);
               void  setOffset(int pos){
                   offset = pos;
               }
               char* toString(){ return name; }
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
                sprintf(rval, "%d", value);
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
                int reg[4];
                static bool alreadyUsed[4];
                static int  len;
                //char regName[8];
        public:
                Register(int dtype) : Node(dtype){
                    len = 4;
                    for(int i = 0; i < len; i++){
                        reg[i] = i;
                    }
                    _register = getReg();
                }
                
                char* toString(){
                    if(_register == eax)
                        return (char*)"%eax";
                    else if(_register == ecx)
                        return (char*)"%ecx";
                    else if(_register == ebx)
                        return (char*)"%ebx";
                    else if(_register == edi)
                        return (char*)"%edi";
                }
                
                Reg getReg(){
                    // go through "used" array.
                    // return first unused register.
                    for(int i = 0; i < len; i++){
                        if(!alreadyUsed[i]){
                            alreadyUsed[i] = true;
                            return (Reg)reg[i];
                        }
                    }
                }
                
                void unsetReg(int i){
                    alreadyUsed[i] = false;
                }
                
                void static clearAll(){
                    for(int i = 0; i < len; i++){
                        alreadyUsed[i] = false;
                    }
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
                
                char* toString(){
                    return label;
                }
    };
    
  } // end of ast namespace.
} // end of yacl namespace.
#endif
