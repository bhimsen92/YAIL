#include<iostream>
#include<cstdlib>
#include<cstring>
#include "object.h"
#include "tokens.h"
using namespace std;

#ifndef __STRING_TYPE
#define __STRING_TYPE
namespace bnk_types{
class Char : public Object{
    public:
            Char( int t);
};

class String : public Char{
    protected:
              char *str;
              int   length;
    public:
            String( char* strData );
            char* getValue(void);
            int getLength(void);
};
}
#endif
