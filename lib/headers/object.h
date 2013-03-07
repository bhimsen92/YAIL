#include<iostream>
#include<cstdlib>
#include<cstring>
#include "value.h"
#ifndef __OBJECT_TYPE
#define __OBJECT_TYPE
using namespace std;
using namespace bnk;

namespace bnk_types{
	class Object{
    	protected:
                int     dataType;
                int     typeClass;
                Value   *value;
    	public:
                Object( int t );
                Object( int t, int typeCls );
              	int getDataType(void);
                int getTypeClass(void);
                Value* getValue(void);
                void   setValue(Value *val);
                virtual void dummy(void){}
	};
}
#endif
