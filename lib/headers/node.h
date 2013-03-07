#include<iostream>
#include<cstring>
#include<list>
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
    private:
        int value;

    public:
        Integer( char* str );
        void toInteger( char* str );
        int getValue(void);
        void setValue( int val );
};

class Type: public Node{
    private:
            int type;
    public:
            Type( int _type );
            int getType(void);
            void setType(int _type);
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
              list<Node*> *operands;
              int nops;
    public:
            Operator( int nType, int nOps, list<Node*> *ops );
            list<Node*>* getOperands(void);
            int getOpsLength(void);
};

class Nothing: public Node{
    public:
              Nothing();
};

class Empty: public Node{
    public:
              Empty();
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
