#include<iostream>
#include<cstring>
#include<list>
#include "tokens.h"
#include "../bnKapi.h"
using namespace std;

#ifndef __NODE_TYPE
#define __NODE_TYPE
namespace bnk_astNodes{

class Node{
    protected:
               int nodeType;
    public:
            Node( int nType ){
                nodeType = nType;
            }
            
            int getType(void){
                return nodeType;
            }
            
            virtual void dummy(void){
            }
};

class Identifier: public Node{
    protected:
               char* name;
    public:
           Identifier( char* n ): Node( __identifier ){
                name = new char[ strlen(n) + 1 ];
                strcpy( name, n );
           }
           
           char* getName(void){
                return name;
           }
};

class String: public Node{
    protected:
                char* string;
                int length;
    public:
             String( char* str ) : Node( __string ){
                length = strlen(str);
                string = removeQuotes( str, length );                
             }
             
             char* getString(void){
                return string;
             }
             
             int getLength(void){
                return length;
             }
             
             char* removeQuotes( char* str, int length ){
                char *target = new char[ length - 1 ];
                int j = 0;
                for( int i = 0; str[i] != '\0'; i++ ){
                    if( str[i] != '"' ){
                        target[j++] = str[i];
                    }
                }
                target[j] = '\0';
                return target;
             }
};

class Integer: public Node{
    private:
        int value;

    public:
        Integer( char* str ): Node( __integer ){
            toInteger(str);
        }
        void toInteger( char* str ){            
            char *pEnd = str + strlen( str ) - 1;
            int multiplier = 1;
            value = 0;
            for( ; pEnd >= str; pEnd-- ){
                value += ( (*pEnd - '0') * multiplier );
                multiplier *= 10;
            }
        }
        int getValue(void){
            return value;
        }
        void setValue( int val ){
            value = val;
        }
};

class Type: public Node{
    private:
            int type;
    public:
            Type( int _type ): Node( __type ){
                type = _type;
            }

            int getType(void){
                return type;
            }

            void setType(int _type){
                type = _type;
            }
};

class Expression: public Node{
    private:
            Node *expNode;
    public:
            Expression( Node* n ): Node( __expression ){
                expNode = n;
            }

            Node* getNode(void){
                return expNode;
            }

            void setNode( Node* n ){
                expNode = n;
            }
};

class Operator: public Node{
    protected:
              list<Node*> *operands;
              int nops;
    public:
            Operator( int nType, int nOps, list<Node*> *ops ): Node( nType ){
                nops = nOps;
                operands = ops;
            }
            list<Node*>* getOperands(void){
                return operands;
            }
            int getOpsLength(void){
                return nops;
            }
};

class List : public Node{
    protected:
              list<Node*> nodeList;
    public:
             List( int nodeType ): Node( nodeType ){
             }
             
             void push_back( Node* node ){
                nodeList.push_back(node);
             }
             
             Node* pop_front(void){
                Node* rval = nodeList.front();
                nodeList.pop_front();
                return rval;
             }
             
             Node* get( int index ){
                list<Node*>::iterator it;
                it = nodeList.begin();
                for( int i = 0; i < index && it != nodeList.end(); ++it, i++ );
                return *it;
             }
             
             int getLength(void){
                return nodeList.size();
             }
             
             void clear(){
                nodeList.clear();
             }

             int empty(){
                return nodeList.empty();
             }
};

class VariableList : public List{
    public:
        VariableList( int nodeType ): List( nodeType )
        {

        }
};

class FormalParameterList : public List{
    public:
             FormalParameterList() : List( __params ){
             }
};

class FormalParameter: public Node{
    private:
            int   dataType;
            char* parameterName;
    public:
            FormalParameter( int _type, char* pName ): Node( __params ){
                dataType = _type;
                parameterName = pName;
            }

            FormalParameter( Node* _type, Node* ident ): Node( __params ){
                dataType = _type->getType();
                Identifier *id = CAST_TO( Identifier, ident );
                if( id != NULL ){
                    parameterName = id->getName();
                }
            }

            int getDataType(void){
                return dataType;
            }

            char* getParameterName(void){
                return parameterName;
            }            
};

class ArgumentList : public List{
    public:
             ArgumentList() : List( __args ){
             }
};

class StatementList : public List{
    public:
             StatementList(): List( __stmtlist ){
             }
};

/*class FunctionCall : public Node{
    protected:
              Identifier *functName;
              ParameterList *plist;
    public:
            FunctionCall( Identifier *ident, ParameterList *pList ) : Node( __funct_call ){
                functName = ident;
                plist = pList;
            }
};

class FunctionDefinition : public Node{
    protected:
              Identifier    *functName;
              ArgumentList  *arglist;
              StatementList *statementList;
    public:
           FunctionDefinition( Identifier *ident, ArgumentList *argList, StatementList *stmtList ): Node( __funct_def ){
                functName = ident;
                arglist = argList;
                statementList = stmtList;
           }
           
           StatementList* getStatementList(void){
                return statementList;
           }
           
           ArgumentList* getArgumentList(void){
                return arglist;
           }
           
           Identifier* getFunctName(void){
                return functName;
           }
};*/
}
#endif