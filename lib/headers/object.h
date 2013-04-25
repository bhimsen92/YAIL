/**
    The following code contains Class file Object, the root for all the types in the language.
    This class holds information, regarding the type class and datatype of the respective types and
    also the value associated with that object.
    create by : Bhimsen S K.
*/
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<vector>
#include "tokens.h"

#ifndef __OBJECT_TYPE
#define __OBJECT_TYPE
using namespace std;

namespace bnk_types{
	class Value;
	class Object{
    	protected:
                int     dataType;
                int     typeClass;
                Value   *value;
    	public:
                Object( int t );
                Object( int t, int typeCls );
              	int getDataType(void);
                void setDataType(int t){
                    dataType = t;
                }
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

    class Value{
        protected:
                    int typeTag; // right now tag is not being used. it may prove useful in future.
                    union YACLValue{
                      int    i32;
                      double real64;
                      char*  str;
                      bool   truthValue;
                      vector<Object*> *yail_array;
                    };
                    YACLValue value;
        public:
                // empty constuctor is for yail_array.
                Value( void ){
                    value.yail_array = NULL;
                }
                Value( int val ){
                    value.i32 = val; 
                }
                
                Value( double val ){
                    value.real64 = val;
                }
                
                Value( char *val ){
                    value.str = val;
                }
                
                Value( bool val ){
                    value.truthValue = val;
                }

                void setYailArrayVal(vector<Object*>*arr){
                    value.yail_array = arr;
                }
                
                int getIntVal(void){
                    return value.i32;
                }
                
                double getDoubleVal(void){
                    return value.real64;
                }
                
                char* getStringVal(void){
                    return value.str;
                }
                
                bool getBooleanValue(void){
                    return value.truthValue;
                }
                
                vector<Object*>* getYailArrayVal(void){
                    return value.yail_array;
                }
    };
}
#endif
