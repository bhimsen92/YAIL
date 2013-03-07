#include<iostream>
#include<cstdlib>
#include "../headers/number.h"
using namespace std;
namespace bnk_types{
    Number::Number( int t ): Object( t, NumberClass ){ 
    }

    Integer::Integer( int num ) : Number( __integer_t ){
        value = new Value( num );
    }
    Integer::Integer() : Number( __integer_t ){
        value = new Value( 0 );
    }
}
