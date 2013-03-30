#include<iostream>
using namespace std;

#ifndef __INSTR
#define __INSTR
namespace yacl{
    namespace codegen{
        enum Instr{
            allocate,
            mov,
            add  
        };

        enum Reg{
            eax = 0,
            ecx,
            ebx,
            edi
        };
    }
}
#endif
