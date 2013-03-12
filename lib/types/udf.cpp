#include<iostream>
#include<map>
#include<cstring>
#include "../headers/udf.h"
#include "../headers/node.h"

namespace bnk_types{
    UserDefinedFunction::UserDefinedFunction( Operands *operands ) : Object( __function_t ){
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
                    if( functBody == NULL ){
                        cout<<"Error in udf.."<<endl;
                    }
                }
            }
        }
    }
    // getter functions.
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

}
