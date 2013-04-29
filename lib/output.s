L0:
	.asciz  "%d\n"
.section .text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
movq $1, %rbx
pushq %rbx
movq $24, %rdi
call malloc
movq %rax, -16(%rbp)
popq %rbx
movq -16(%rbp), %rcx
movq $2, 0(%rcx)
movq %rbx, 8(%rcx)
movq $2, %rbx
movq %rbx, 16(%rcx)
movq %rcx, -8(%rbp)
movq $L0, %rbx
movq %rbx, %rdi
movq $2, %rbx
movq %rbx, %rsi
call printf
mov %rbp, %rsp
pop %rbp
ret
