.section .text

.type power, @function
power:
push %rbp
mov %rsp, %rbp
sub $16, %rsp
mov %rdi, -8(%rbp)
mov %rsi, -16(%rbp)
mov -16(%rbp), %rax
mov $0, %rbx
cmp %rax, %rbx
je L0
mov -8(%rbp), %rcx
mov %rcx, %rdi
mov %rcx, -8(%rbp)
mov $1, %rcx
mov %rax, %rdx
sub %rcx, %rax
mov %rax, %rsi
call power
imul -8(%rbp), %rax
jmp EXIT2
L0:
mov $1, %rax
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
mov $6, %rax
mov %rax, %rdi
mov $3, %rax
mov %rax, %rsi
call power
mov %rax, %rdi
mov $60, %rax
syscall
