#include<iostream>
#include<cstdlib>
#include "object.h"
#include "tokens.h"

#ifndef __BOOL_TYPE
#define __BOOL_TYPE
using namespace std;

namespace bnk_types{
    class Boolean: public Object{
        public:
                Boolean( bool val ): Object( __boolean_t, BooleanClass ){
                    value = new Value( val );
                }
                Object* getCopy(void){
                    return new Boolean( value->getBooleanValue() );
                }
    };
}
#endif
