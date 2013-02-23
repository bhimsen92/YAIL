#include<iostream>
#include<cstdlib>
#include "object.h"
#include "../nodes/tokens.h"
using namespace std;

#ifndef __NUMBER_TYPE
#define __NUMBER_TYPE

namespace bnk_types{
class Integer : public Object{
    protected:
              int value;
    public:
            Integer( int num ) : Object( __integer_t ){
                value = num;
            }
            Integer() : Object( __integer_t ){
                value = 0;
            }
            int getValue(void){
                return value;
            }
            void setValue( int num ){
                value = num;
            }
};
}
#endif
