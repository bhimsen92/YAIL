#include<iostream>
#include "../headers/object.h"
#include "../headers/string.h"
#include "../headers/udf.h"
#include "../headers/number.h"
#include "../headers/builtins.h"

using namespace std;
using namespace bnk_types;
namespace bnk_builtins{
	Object* __bprint( list<Object*> *args ){
		int length = args->size();
		if( length == 1 ){
			Object *obj = args->front();
			switch( obj->getDataType() ){
				case __string_t:
								bnk_types::String *str;
								str = CAST_TO( bnk_types::String, obj );
								if( str != NULL ){
									cout<<str->getValue()->getStringVal();
								}
								break;
				case __integer_t:
								bnk_types::Integer *integer;
								integer = CAST_TO( bnk_types::Integer, obj );
								if( integer != NULL ){
									cout<<integer->getValue()->getIntVal();
								}
								break;
				case __double_t:
				                bnk_types::Double *realVal;
				                realVal = CAST_TO( bnk_types::Double, obj );
				                if( realVal != NULL ){
				                    cout<<realVal->getValue()->getDoubleVal();
				                }
				                break;
			}
		}
	}
}
