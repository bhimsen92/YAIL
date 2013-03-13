#include<iostream>
#include<cstdlib>
#include<cstring>
#include "value.h"
#include "tokens.h"
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
                //virtual void dummy(void){}
                virtual Object* getCopy(void)=0;
	};
	
	// no need to create a file for this.
	class Nothing : public Object{
	    public:
	              Nothing( void* val ): Object( __nothing_t, NothingClass ){
	                  value = NULL;
	              }
	              Object* getCopy(void){
	                  return new Nothing(NULL);
	              }
	};
	// no need to create a file for this.
	class ReturnValue : public Object{
	    protected:
	            Object *value;
	    public:
	            ReturnValue( Object *val ) : Object( __return_t, ReturnClass ){
	                value = val;
	            }
	            Object* getObject(void){
	                return value;
	            }
	            Object* getCopy(void){
	                return new ReturnValue( value );
	            }
	};
}
#endif
