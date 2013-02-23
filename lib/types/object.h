#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

#ifndef __OBJECT_TYPE
#define __OBJECT_TYPE
namespace bnk_types{
	class Object{
    	protected:
        	      char    *name;
                int     dataType;
                Object* value;
    	public:
        	      Object( char* n, int type, Object* val ){
            	     name = n;
                   dataType = type;
                   value = val;
              	}

                Object( int type ){
                  dataType = type;
                }

              	int getDataType(void){
                	return dataType;
              	}

                char* getName(void){
                  return name;
                }

                Object* getValue(void){
                  return value;
                }

                virtual void dummy(void){
                  
                }

	};
}
#endif