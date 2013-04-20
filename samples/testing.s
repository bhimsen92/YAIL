.section .data

.section .text

.globl _start

_start:
        call main
        movl $1, %eax
        int $0x80

.type main, @function
main:
    pushq %rbp  
    movq  %rsp, %rbp
    
    pushq $4
    call fact
    
    movq %rbp, %rsp
    popq %rbp
    ret

.type fact, @function
fact:
    pushq %rbp
    movq %rsp, %rbp
    
    movq 8(%rsp), %rax
    cmpq $1, %rax
    je fact_end
    
    decq %rax
    pushq %rax
    call fact
    movq 8(%rbp), %rbx
    imulq %rbx, %rax
    
    fact_end:
            movq %rbp, %rsp
            popq %rbp
            ret

