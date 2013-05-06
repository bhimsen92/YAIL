L0:
	.asciz  "Hello world: %d\n"
.section .text
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $8, %rsp
movq $12, %rbx
movq %rbx, -8(%rbp)
movq $L0, %rbx
movq %rbx, %rdi
movq -8(%rbp), %rbx
movq %rbx, %rsi
call printf
mov %rbp, %rsp
pop %rbp
ret
