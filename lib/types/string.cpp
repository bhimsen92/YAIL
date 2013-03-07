#include<iostream>
#include<cstdlib>
#include<cstring>
#include "../headers/string.h"
using namespace std;
namespace bnk_types{
    Char::Char( int t): Object( t, CharClass ){
                
    }

    String::String( char* strData ) : Char( __string_t ){
        length = strlen( strData );
        str = new char[ length + 1 ];
        strcpy( str, strData );
    }
    char* String::getValue(void){
        return str;
    }
    int String::getLength(void){
        return length;
    }
}
