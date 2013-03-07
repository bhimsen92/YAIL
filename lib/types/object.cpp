#include<iostream>
#include<cstdlib>
#include<cstring>
#include "../headers/object.h"
#include "../headers/value.h"
using namespace std;
using namespace bnk;

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
    
    Value* Object::getValue(void){
        return value;
    }
    
    void Object::setValue( Value *val ){
        value = val;
    }
}
