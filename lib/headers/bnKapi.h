#ifndef __bnKAPI
#define __bnKAPI
#include "object.h"
#include<list>
using namespace bnk_types;


#define CAST_TO( target, source )   \
                           ( dynamic_cast<target*>(source) )

typedef Object* (*BuiltInFunction)(list<Object*> *args);
#endif
