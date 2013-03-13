#include<iostream>
#include<cstdlib>
#include "object.h"
#include "tokens.h"
#include "value.h"
#ifndef __NUMBER_TYPE
#define __NUMBER_TYPE
using namespace std;
using namespace bnk;

namespace bnk_types{
    class Number : public Object{
        public:
                Number( int t );
                Object* getCopy(void){ return NULL; }
    };

    class Integer : public Number{    
        public:
                Integer( int num );
                Integer();
                Object* getCopy(void){
                    return new Integer( value->getIntVal() );
                }
    };

    class Double : public Number{
        public:
                Double( double num );
                Double(void);
                Object* getCopy(void){
                    return new Double( value->getDoubleVal() );
                }
    };
}
#endif
