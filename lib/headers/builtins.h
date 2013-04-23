#ifndef __BUILTINS
#define __BUILTINS

#include<iostream>
#include "object.h"

using namespace std;
using namespace bnk_types;

namespace bnk_builtins{
	Object* __bprint( list<Object*> *args );
	Object* __emit(list<Object*> *args);
}
#endif
