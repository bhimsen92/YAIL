#include<iostream>

#ifndef __TOKENS
#define __TOKENS

enum {
    __identifier = 0,
    __funct_call = 1,
    __integer = 2,
    __double = 3,
    __string = 4,
    __funct_def = 5,
    __params = 6,
    __args = 7,
    __stmtlist = 8,
    __spawn = 9,
    __sync = 10,
    __array_list = 11,
    __assignment = 12,
    __indexOp = 13,
    __integer_t = 14, __double_t = 15, __string_t = 16, __boolean_t = 17, __function_t = 18,
    __nothing_t = 19, empty_t = 20, __return_t = 21, __array_int_t = 22,
    __type = 23,
    __expression = 24,
    __var_definition = 25,
    __or = 26, __and = 27, __not = 28, __equality = 29, __lt = 30, __le = 31, __ge = 32, __gt = 33,
    __addition = 34, __subtraction = 35, __multiplication = 36, __div = 37, __power = 38, __uminus = 39,
    __nothing = 40, __empty = 41, __return = 42,
    __if = 43, __else = 44, __elif = 45, __array_empty_t = 46, __sliceOp = 47
};

enum{
    NumberClass = 0,
    CharClass = 1,
    BooleanClass = 2,
    ListClass = 3,
    NothingClass = 4,
    ReturnClass = 5
};

#endif
