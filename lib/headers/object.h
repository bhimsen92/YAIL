#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

#ifndef __OBJECT_TYPE
#define __OBJECT_TYPE

namespace bnk_types{
	class Object{
    	protected:
                int     dataType;
                int     typeClass;
    	public:
                Object( int t );
                Object( int t, int typeCls );
              	int getDataType(void);
                int getTypeClass(void);
                virtual void dummy(void){}
	};
}
#endif
