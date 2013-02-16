#include<iostream>
#include<cstdlib>
#include "object.h"
using namespace std;

#ifndef __NUMBER_TYPE
#define __NUMBER_TYPE

class Number : public Object{
    protected:
              int number;
    public:
            Number( int num ) : Object( "number" ){
                number = num;
            }
            Number() : Object( "number" ){
                number = 0;
            }
            int getValue(void){
                return number;
            }
            void setValue( int num ){
                number = num;
            }
};
#endif
