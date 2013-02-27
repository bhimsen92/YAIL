#include<iostream>
#include "../types/object.h"
#include "../types/string.h"
#include "../types/udf.h"
#include "../types/number.h"

using namespace std;
using namespace bnk_types;


#ifndef __BUILTINS
#define __BUILTINS

namespace bnk_builtins{
	Object* __bprint( list<Object*> *args ){
		int length = args->size();
		if( length == 1 ){
			bnk_types::String *str= CAST_TO( bnk_types::String, args->front() );
			if( str != NULL ){
				cout<<str->getValue()<<endl;
			}
		}
	}
}
#endif