#include<iostream>
#include<map>
#include "../bnKapi.h"
#include "object.h"
#include "../nodes/node.h"

using namespace std;
using namespace bnk_astNodes;
#ifndef __UDF_TYPE
#define __UDF_TYPE

namespace bnk_types{
	class UserDefinedFunction : public Object{
		private:
				string functName;
				FormalParameterList *fpList;
				int returnType;
				StatementList *functBody;
				//map< string, Object*> closureLink;
		public:
				UserDefinedFunction( list<Node*> *operands ) : Object( __function_t ){
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
								returnType = dataType->getType();
								operands->pop_front();
								// get the statementList of the function.
								StatementList *functBody = CAST_TO( StatementList, operands->front() );
							}
						}
					}
				}
				// getter functions.
				string getFunctionName(void){
					return functName;
				}

				FormalParameterList* getFormalParameterList(void){
					return fpList;
				}

				int getReturnType(void){
					return returnType;
				}

				StatementList* getStatementList(void){
					return functBody;
				}

	};
}
#endif