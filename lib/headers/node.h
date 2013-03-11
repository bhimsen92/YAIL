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
    public:
           Identifier( char* n );
           char* getName(void);
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
};

class Integer: public Node{
    protected:
        int value;

    public:
        Integer( char* str );
        void toInteger( char* str );
        int getValue(void);
        void setValue( int val );
};

class Double: public Node{
    protected:
        double value;
    public:
        Double( char *str );
        void toDouble( char *str );
        double getValue(void);
        void setValue( double val );
};

class Type: public Node{
    protected:
            int type;
    public:
            Type( int _type );
            int getDataType(void);
            void setDataType(int _type);
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
}
#endif
