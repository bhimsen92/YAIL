L0:
	.asciz  "%d\n"
.section .text

.type add, @function
add:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
movq %rdi, -8(%rbp)
movq %rsi, -16(%rbp)
movq -8(%rbp), %rbx
movq -16(%rbp), %rcx
movq %rcx, %rdx
addq %rbx, %rcx
movq %rcx, %rax
jmp EXIT2
EXIT2:
movq %rbp, %rsp
popq %rbp
ret
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
movq $L0, %rbx
movq %rbx, %rdi
pushq %rdi
movq $1, %rbx
movq %rbx, %rdi
movq $3, %rbx
movq %rbx, %rsi
call add
popq %rdi
movq %rax, %rsi
call printf
mov %rbp, %rsp
pop %rbp
ret
