#include "object.h"
#include<list>
#include<cstdarg>
using namespace bnk_types;

#ifndef __YACL
#define __YACL

#define CAST_TO( target, source )   \
                           ( dynamic_cast<target*>(source) )

typedef Object* (*BuiltInFunction)(list<Object*> *args);

/*void debugMessage( int size, ... ){
    int i;
    char *message;
    va_list args;
    va_start( args, size );
    for( i = 0; i < size; i++ ){
        message = va_arg( args, char* );
        cout<<message<<endl;
    }
}*/

#endif
