.section .text

.type power, @function
power:
push %rbp
mov %rsp, %rbp
sub $16, %rsp
mov %rdi, -8(%rbp)
mov %rsi, -16(%rbp)
mov -16(%rbp), %rbx
mov $0, %rcx
cmp %rbx, %rcx
je L0
mov -8(%rbp), %rdx
mov %rbx, -16(%rbp)
push %rcx
mov %rdx, -8(%rbp)
mov -8(%rbp), %rbx
mov %rbx, %rdi
mov -16(%rbp), %rbx
mov $1, %rcx
mov %rbx, %rdx
sub %rcx, %rbx
mov %rbx, %rsi
call power
pop %rcx
imul -8(%rbp), %rax
jmp EXIT2
L0:
mov $1, %rbx
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
mov $6, %rbx
mov %rbx, %rdi
mov $3, %rbx
mov %rbx, %rsi
call power
mov %rax, %rdi
mov $60, %rax
syscall
