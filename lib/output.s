.section .text

.type sub, @function
sub:
push %rbp
mov %rsp, %rbp
sub $16, %rsp
mov %rdi, -8(%rbp)
mov %rsi, -16(%rbp)
mov -8(%rbp), %rbx
mov -16(%rbp), %rcx
mov %rbx, %rdx
sub %rcx, %rbx
mov %rbx, %rax
jmp EXIT2
EXIT2:
mov %rbp, %rsp
pop %rbp
ret
.globl _start
_start:
push %rbp
mov %rsp, %rbp
sub $0, %rsp
mov $5, %rbx
mov %rbx, %rdi
mov $3, %rbx
mov %rbx, %rsi
call sub
mov %rax, %rdi
mov $60, %rax
syscall
