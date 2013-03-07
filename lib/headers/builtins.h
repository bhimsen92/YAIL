#include<iostream>
#include "object.h"

using namespace std;
using namespace bnk_types;

#ifndef __BUILTINS
#define __BUILTINS
namespace bnk_builtins{
	Object* __bprint( list<Object*> *args );
}
#endif
