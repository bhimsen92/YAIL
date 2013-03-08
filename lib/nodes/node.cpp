#include<iostream>
#include<cstring>
#include<list>
#include "../headers/bnKapi.h"
#include "../headers/node.h"
using namespace std;
namespace bnk_astNodes{
    Node::Node( int nType ){
        nodeType = nType;
    }
            
    int Node::getType(void){
        return nodeType;
    }

    Identifier::Identifier( char* n ): Node( __identifier ){
        name = new char[ strlen(n) + 1 ];
        strcpy( name, n );
    }
           
    char* Identifier::getName(void){
        return name;
    }

    String::String( char* str ) : Node( __string ){
        length = strlen(str);
        string = removeQuotes( str, length );                
    }
             
    char* String::getString(void){
        return string;
    }
             
    int String::getLength(void){
        return length;
    }
             
    char* String::removeQuotes( char* str, int length ){
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
    
    Integer::Integer( char* str ): Node( __integer ){
        toInteger(str);
    }
    
    void Integer::toInteger( char* str ){            
        char *pEnd = str + strlen( str ) - 1;
        int multiplier = 1;
        value = 0;
        for( ; pEnd >= str; pEnd-- ){
            value += ( (*pEnd - '0') * multiplier );
            multiplier *= 10;
        }
     }
     int Integer::getValue(void){
        return value;
     }
     void Integer::setValue( int val ){
        value = val;
     }

    Type::Type( int _type ): Node( __type ){
        type = _type;
    }

    int Type::getDataType(void){
        return type;
    }

    void Type::setDataType(int _type){
        type = _type;
    }
/*
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
};*/

    Operator::Operator( int nType, int nOps, list<Node*> *ops ): Node( nType ){
        nops = nOps;
        operands = ops;
    }
    list<Node*>* Operator::getOperands(void){
        return operands;
    }
    int Operator::getOpsLength(void){
        return nops;
    }

    Nothing::Nothing():Node( __nothing ){

    }

    Empty::Empty():Node( __empty ){
                
    }

    List::List( int nodeType ): Node( nodeType ){
    }
             
    void List::push_back( Node* node ){
        nodeList.push_back(node);
    }
             
    Node* List::pop_front(void){
        Node* rval = nodeList.front();
        nodeList.pop_front();
        return rval;
    }
             
    Node* List::get( int index ){
        list<Node*>::iterator it;
        it = nodeList.begin();
        for( int i = 0; i < index && it != nodeList.end(); ++it, i++ );
        return *it;
    }
             
    int List::getLength(void){
        return nodeList.size();
    }
             
    void List::clear(){
        nodeList.clear();
    }

    int List::empty(){
        return nodeList.empty();
    }
    
    VariableList::VariableList( int nodeType ): List( nodeType )
    {
         ;
    }

    FormalParameterList::FormalParameterList() : List( __params ){
    }

    FormalParameter::FormalParameter( int _type, char* pName ): Node( __params ){
        dataType = _type;
        parameterName = pName;
    }

    FormalParameter::FormalParameter( Node* _type, Node* ident ): Node( __params ){
        Type *t = CAST_TO( Type, _type );
        if( t != NULL ){
            dataType = t->getDataType();
            Identifier *id = CAST_TO( Identifier, ident );
            if( id != NULL ){
                parameterName = id->getName();
            }
        }
        else{
            cout<<"formal parameter error."<<endl;
            exit(1);
        }
    }

    int FormalParameter::getDataType(void){
        return dataType;
    }

    char* FormalParameter::getParameterName(void){
                    return parameterName;
    }

    ArgumentList::ArgumentList() : List( __args ){
    }
    
    StatementList::StatementList(): List( __stmtlist ){
    }
    
} // end of bnk_astNodes namespace
