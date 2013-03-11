#include<iostream>
#include<map>
#include "bnKapi.h"
#include "object.h"
#include "node.h"

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
				UserDefinedFunction( Operands *operands );
				// getter functions.
				string getFunctionName(void);
				FormalParameterList* getFormalParameterList(void);
				int getReturnType(void);
				StatementList* getStatementList(void);
	};
}
#endif
