#include<iostream>
using namespace std;

#ifndef __INSTR
#define __INSTR
namespace yacl{
    namespace codegen{
        enum Instr{
            allocate,
            mov,
            add,
            sub,
            imul,
            div,
            je,
            jg,
            jge,
            jl,
            jle,
            jmp,
            cmp,
            push,
            pop,
            ret,
            call,
            emit,
            emitlabel
        };

        enum Reg{
            rax = 0,
            rbx = 1,
            rcx = 2, // 4th argument.
            rdx = 3, // 3rd argument.
            rsi = 4, // 2nd argument.
            rdi = 5, // 1st argument.
            rbp = 6, // base pointer.
            rsp = 7, // stack pointer.
            r8 = 8,  // 5th argument.
            r9 = 9, // 6th register.
            r10 = 10,
            r11 = 11,
            r12 = 12,
            r13 = 13,
            r14 = 14,
            r15 = 15
        };
    }
}
#endif
