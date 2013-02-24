#include<iostream>

#ifndef __TOKENS
#define __TOKENS

enum {
    __identifier,
    __funct_call,
    __integer,
    __string,
    __funct_def,
    __params,
    __args,
    __stmtlist,
    __spawn,
    __sync,
    __assignment,
    __integer_t,
    __double_t,
    __string_t,
    __function_t,
    __list_t,
    __type,
    __expression,
    __var_definition
};
#endif
