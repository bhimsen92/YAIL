#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

#ifndef __OBJECT_TYPE
#define __OBJECT_TYPE

class Object{
    protected:
              char type[64];
    public:
              Object( const char* typeString ){
                strcpy( type, typeString );
              }
              char* getType(void){
                return type;
              }
};
#endif
