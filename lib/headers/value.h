#include<iostream>
#include<string>
#include<cstdlib>

#ifndef __BNK_VALUE
#define __BNK_VALUE
using namespace std;
namespace bnk{
    class Value{
        protected:
                    int typeTag; // right now tag is not being used. it may prove useful in future.
                    union BNKValue{
                      int    i32;
                      double real64;
                      string *str;
                    };
                    BNKValue value;
        public:
                Value( int val ){
                    value.i32 = val; 
                }
                Value( double val ){
                    value.real64 = val;
                }
                Value( string *val ){
                    value.str = val;
                }
                int getIntVal(void){
                    return value.i32;
                }
                double getDoubleVal(void){
                    return value.real64;
                }
                string* getStringVal(void){
                    return value.str;
                }
    };
}

#endif
