#include<iostream>
#include<cstdlib>
#include<cstring>
#include "object.h"
#include "../nodes/tokens.h"
using namespace std;

#ifndef __STRING_TYPE
#define __STRING_TYPE
namespace bnk_types{
class String : public Object{
    protected:
              char *str;
              int   length;
    public:
            String( char* strData ) : Object( __string_t ){
                length = strlen( strData );
                str = new char[ length + 1 ];
                strcpy( str, strData );
            }
            char* getValue(void){
                return str;
            }
            int getLength(void){
                return length;
            }
};
}
#endif
