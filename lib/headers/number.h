#include<iostream>
#include<cstdlib>
#include "object.h"
#include "tokens.h"
#ifndef __NUMBER_TYPE
#define __NUMBER_TYPE
using namespace std;

namespace bnk_types{
class Number : public Object{
    protected:
        union Value{
            int intVal;
            double realVal;
        };
        Value value;
    public:
            Number( int t );
};

class Integer : public Number{    
    public:
            Integer( int num );
            Integer();
            int getValue(void);
            void setValue( int num );
};
}
#endif
