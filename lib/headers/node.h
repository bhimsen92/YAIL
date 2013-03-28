#include<iostream>
#include<cstring>
#include<list>
#include<vector>
#include "tokens.h"
#include "bnKapi.h"

#ifndef __NODE_TYPE
#define __NODE_TYPE
using namespace std;
namespace bnk_astNodes{
    
class Node{
    protected:
               int nodeType;
    public:
            Node( int nType );
            int getType(void);
            char* toString(void);
            virtual void dummy(void){}
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
           Identifier( char* n, int position );
           char* getName(void);
           int   getOffset(void);
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
        Integer(int v){
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
            Temp( int tmpIndex, int position ) : Node(-1){
                sprintf( t, "t%d", tmpIndex );
                offset = position;
            }
            char* toString(){
                return t;
            }
};

class Register : public Node{
    private:
            int regType;
            //char regName[8];
    public:
            Register(int t) : Node(-1){
                regType = t;
            }
            
            const char* toString(){
                if(regType == _eax)
                    return "%eax";
                else if(regType == _ecx)
                    return "%ecx";
            }
};
}
#endif
