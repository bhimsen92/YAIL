#include<iostream>
#include<cstring>
#include<list>
#include<cmath>
#include "../headers/bnKapi.h"
#include "../headers/node.h"
using namespace std;
namespace yacl{
    namespace ast{
    Node::Node(int nType){
        nodeType = nType;
    }
            
    int Node::getType(void){
        return nodeType;
    }

    Identifier::Identifier(char* n): Node( __identifier ){
        name = new char[strlen(n) + 1];
        strcpy( name, n );
        //offset = position;
    }
           
    char* Identifier::getName(){
        return name;
    }
    
    int Identifier::getOffset(){
        return offset;
    }

    String::String(char* str) : Node( __string ){
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
    
    Double::Double( char *str ): Node( __double ){
        toDouble( str );
    }
    
    void Double::toDouble( char *str ){
        int dotPos = 0;
        double dotLeft = 0.0, dotRight = 0.0, multiplier = 0.0;
        int i, length;
        // go through the string, remember the dot position.
        // then calculate value on the right and left of the dot,
        // sum it, assign it to value.
        for( i = 0; str[i] != '\0'; i++ ){
            if( str[i] == '.' ){
                dotPos = i;
            }
        }
        length = i;
        multiplier = 1 / pow( 10, length - dotPos - 1 );
        for( i = length - 1; i > dotPos; i-- ){
            dotRight += ( ( str[i] - '0' ) * multiplier );
            multiplier *= 10;
        }
        multiplier = 1.0;
        for( i = dotPos - 1; i >= 0; i-- ){
            dotLeft += ( ( str[i] - '0' ) * multiplier );
            multiplier *= 10;
        }
        value = dotLeft + dotRight;
    }
    
    double Double::getValue(){
        return value;
    }
    
    void Double::setValue( double val ){
        value = val;
    }
    
    Type::Type( int _t, int w ): Node( __type ){
        type = _t;
        width = w;
    }

    int Type::getDataType(){
        return type;
    }
    
    int Type::getDataWidth(){
        return width;
    }
    
    void Type::setDataType(int _t){
        type = _t;
    }
    
    void Type::setDataWidth(int w){
        width = w;
    }

    Operator::Operator( int nType, int nOps, Operands *ops ): Node( nType ){
        nops = nOps;
        operands = ops;
    }
    Operands* Operator::getOperands(void){
        return operands;
    }
    int Operator::getOpsLength(void){
        return nops;
    }

    Nothing::Nothing() : Node( __nothing ){
    }
    
    void* Nothing::getValue(void){
        return NULL;
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
    
    ValueList::ValueList() : List( __array_list ){
        
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
    
} // end of ast namespace
} // end of yacl namespace.
