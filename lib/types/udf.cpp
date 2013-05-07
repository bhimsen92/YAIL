/**
    Following code contains class UserDefinedFunctionObject, which is used to store
    information regarding a function defined in this language.
    This class stores, ReturnType info, statments that will be executed in respective function, 
    And a link to the enclosing context[in case of closure] if one exist.
*/
#include<iostream>
#include<map>
#include<cstring>
#include "../headers/udf.h"
#include "../headers/node.h"
#include "../headers/context.h"

namespace bnk_types{
    UserDefinedFunction::UserDefinedFunction( Operands *operands ) : Object( __function_t ){
        closureLink = NULL;
        // get the function name.
        Identifier *name = CAST_TO( Identifier, operands->get(0) );
		if( name != NULL ){
		    char *tmpName = name->getName();		    
            functName = new char[ strlen(tmpName) + 1 ];
            strcpy( functName, tmpName );
			//operands->pop_front();
			// get the formalParameter list.
			fpList = CAST_TO( FormalParameterList, operands->get(1) );
			if( fpList != NULL ){
			    //operands->pop_front();
				// get the returnType.
				Type *dataType = CAST_TO( Type, operands->get(2) );
				if( dataType != NULL ){
                    returnType = dataType->getDataType();
                    //operands->pop_front();
                    // get the statementList of the function.
                    functBody = CAST_TO( StatementList, operands->get(3) );
                    arglist = new ArgumentList();
                    if( functBody == NULL ){
                        cout<<"Error in udf.."<<endl;
                    }
                }
            }
        }
    }
    UserDefinedFunction::UserDefinedFunction( char* fName, FormalParameterList *fpl, int rt, StatementList *stList, Context* enclosingLink ): Object( __function_t ){
        fpList = fpl;
        returnType = rt;
        functBody = stList;
        closureLink = enclosingLink;
        functName = new char[ strlen( fName ) + 1 ];
        strcpy( functName, fName );
        arglist = new ArgumentList();
    }
    // getter functions.
    Object* UserDefinedFunction::getCopy(){
        return new UserDefinedFunction( functName, fpList, returnType, functBody, closureLink );
    }
    char* UserDefinedFunction::getFunctionName(void){
        return functName;
    }

    FormalParameterList* UserDefinedFunction::getFormalParameterList(void){
        return fpList;
    }

    int UserDefinedFunction::getReturnType(void){
        return returnType;
    }

    StatementList* UserDefinedFunction::getStatementList(void){
        return functBody;
    }
        
    void UserDefinedFunction::createClosure( Context *oContext ){
        // create a new context.
        if( !this->closureExist() )
            closureLink = new Context();
        map< string, Object* > *enclosingEnv = oContext->getSymbolTable();
        map< string, Object* >::iterator it = enclosingEnv->begin();
        for( ; it != enclosingEnv->end(); ++it ){
            string key = it->first;
            Object *value = it->second;
            if( value != NULL && !closureLink->isBound(new Identifier((char*)key.c_str())))
                closureLink->put(key, value->getCopy() );
        }
    }
    
    bool UserDefinedFunction::closureExist(){
        return closureLink != NULL;
    }
    
    Context* UserDefinedFunction::getClosureContext(){
        return closureLink;
    }
}
