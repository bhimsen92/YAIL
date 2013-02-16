#include<iostream>

#ifndef __TOKENS
#define __TOKENS

enum {
    __ident,
    __funct_call,
    __number,
    __string,
    __funct_def,
    __params,
    __args,
    __stmtlist,
    __spawn,
    __sync
};
#endif
