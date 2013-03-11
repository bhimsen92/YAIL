#include<iostream>

#ifndef __TOKENS
#define __TOKENS

enum {
    __identifier,
    __funct_call,
    __integer,
    __double,
    __string,
    __funct_def,
    __params,
    __args,
    __stmtlist,
    __spawn,
    __sync,
    __assignment,
    __integer_t, __double_t, __string_t, __boolean_t, __function_t, __list_t,
    __nothing_t, empty_t,
    __type,
    __expression,
    __var_definition,
    __or, __and, __not, __equality, __lt, __le, __ge, __gt,
    __addition, __subtraction, __multiplication, __div, __power, __uminus,
    __nothing, __empty,
    __if, __ifelse
};

enum{
    NumberClass,
    CharClass,
    BooleanClass,
    ListClass,
    NothingClass
};

#endif
