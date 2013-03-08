#include<iostream>
#include<map>
#include "../headers/udf.h"

namespace bnk_types{
    UserDefinedFunction::UserDefinedFunction( list<Node*> *operands ) : Object( __function_t ){
        // get the function name.
        Identifier *name = CAST_TO( Identifier, operands->front() );
		if( name != NULL ){
            functName = name->getName();		
			operands->pop_front();
			// get the formalParameter list.
			fpList = CAST_TO( FormalParameterList, operands->front() );
			if( fpList != NULL ){
			    operands->pop_front();
				// get the returnType.
				Type *dataType = CAST_TO( Type, operands->front() );
				if( dataType != NULL ){
                    returnType = dataType->getDataType();
                    operands->pop_front();
                    // get the statementList of the function.
                    functBody = CAST_TO( StatementList, operands->front() );
                    if( functBody == NULL ){
                        cout<<"Error in udf.."<<endl;
                    }
                }
            }
        }
    }
    // getter functions.
    string UserDefinedFunction::getFunctionName(void){
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

}
