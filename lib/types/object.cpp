#include<iostream>
#include<cstdlib>
#include<cstring>
#include "../headers/object.h"
using namespace std;

namespace bnk_types{
    Object::Object( int t ){
        dataType = t;
    }

    Object::Object( int t, int typeCls ){
        dataType = t;
        typeClass = typeCls;
    }

    int Object::getDataType(void){
        return dataType;
    }

    int Object::getTypeClass(void){
        return typeClass;
    }
}
