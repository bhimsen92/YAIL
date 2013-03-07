#include<iostream>
#include<cstdlib>
#include "../headers/number.h"
using namespace std;
namespace bnk_types{
    Number::Number( int t ): Object( t, NumberClass ){

    }

    Integer::Integer( int num ) : Number( __integer_t ){
        value.intVal = num;
    }
    Integer::Integer() : Number( __integer_t ){
        value.intVal = 0;
    }
    int Integer::getValue(void){
        return value.intVal;
    }
    void Integer::setValue( int num ){
        value.intVal = num;
    }
}
