#include<iostream>
#include<map>
#include "bnKapi.h"
#include "object.h"
#include "node.h"
#include "context.h"

using namespace std;
using namespace bnk_astNodes;
#ifndef __UDF_TYPE
#define __UDF_TYPE

namespace bnk_types{
	class UserDefinedFunction : public Object{
		private:
				char* functName;
				FormalParameterList *fpList;
				int returnType;
				StatementList *functBody;
				Context *closureLink;
				// Argument list member used for currying.
				ArgumentList *arglist;				
		public:
				UserDefinedFunction( Operands *operands );
                UserDefinedFunction( char* fName, FormalParameterList *fpl, int rt, StatementList *stList, Context* enclosingLink );
				void createClosure( Context *oContext );
				bool closureExist(void);
				// getter functions.
				char* getFunctionName(void);
				FormalParameterList* getFormalParameterList(void);
				int getReturnType(void);
				StatementList* getStatementList(void);
				Context* getClosureContext(void);
				Object* getCopy(void);

				// used for currying.
				ArgumentList* getArgumentList(){
					return arglist;
				}

				void setArgumentList(ArgumentList *alist){
					arglist = alist;
				}

	};
}
#endif
