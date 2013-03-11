#include<iostream>
#include<cstdlib>
#include<cstring>
#include "../headers/string.h"
using namespace std;
namespace bnk_types{
    Char::Char( int t): Object( t, CharClass ){
                
    }

    String::String( char* strData ) : Char( __string_t ){
        char *str;
        length = strlen( strData );
        str = new char[ length + 1 ];
        strcpy( str, strData );
        // put it inside a value.
        value = new Value( str );
    }
    int String::getLength(void){
        return length;
    }
}
