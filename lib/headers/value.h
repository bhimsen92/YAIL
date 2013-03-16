#include<iostream>
#include<string>
#include<cstdlib>
//#include "object.h"

#ifndef __BNK_VALUE
#define __BNK_VALUE
using namespace std;
namespace bnk{
    class Value{
        protected:
                    int typeTag; // right now tag is not being used. it may prove useful in future.
                    union YACLValue{
                      int    i32;
                      double real64;
                      char*  str;
                      bool   truthValue;
                      //vector<Object*> *yail_array;
                    };
                    YACLValue value;
        public:
                // empty constuctor is for yail_array.
                Value( void ){
                    //value.yail_array = NULL;
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
                
                /*Object* getYailArrayVal(void){
                    return value.yail_array;
                }*/
    };
}

#endif
