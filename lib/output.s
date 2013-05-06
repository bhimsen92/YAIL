L1:
	.asciz  "move disk %d from %d to %d\n"
L3:
	.asciz  "move disk 1 from peg: %d to %d\n"
.section .text

.type move, @function
move:
pushq %rbp
movq %rsp, %rbp
subq $32, %rsp
movq %rdi, -8(%rbp)
movq %rsi, -16(%rbp)
movq %rdx, -24(%rbp)
movq %rcx, -32(%rbp)
movq -8(%rbp), %rbx
movq $1, %rcx
cmpq %rbx, %rcx
je L0
movq -8(%rbp), %rbx
movq $1, %rcx
movq %rbx, %rdx
subq %rcx, %rbx
movq %rbx, %rdi
movq -16(%rbp), %rbx
movq %rbx, %rsi
movq -32(%rbp), %rbx
movq %rbx, %rdx
movq -24(%rbp), %rbx
movq %rbx, %rcx
call move
pushq %rax
movq $L1, %rbx
movq %rbx, %rdi
movq -8(%rbp), %rbx
movq %rbx, %rsi
movq -16(%rbp), %rbx
movq %rbx, %rdx
movq -24(%rbp), %rbx
movq %rbx, %rcx
call printf
popq %rax
pushq %rax
movq -8(%rbp), %rbx
movq $1, %rcx
movq %rbx, %rdx
subq %rcx, %rbx
movq %rbx, %rdi
movq -32(%rbp), %rbx
movq %rbx, %rsi
movq -24(%rbp), %rbx
movq %rbx, %rdx
movq -16(%rbp), %rbx
movq %rbx, %rcx
call move
popq %rax
jmp L2
L0:
movq $L3, %rbx
movq %rbx, %rdi
movq -16(%rbp), %rbx
movq %rbx, %rsi
movq -24(%rbp), %rbx
movq %rbx, %rdx
call printf
L2:
EXIT2:
movq %rbp, %rsp
popq %rbp
ret
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
movq $20, %rbx
movq %rbx, %rdi
movq $1, %rbx
movq %rbx, %rsi
movq $2, %rbx
movq %rbx, %rdx
movq $3, %rbx
movq %rbx, %rcx
call move
mov %rbp, %rsp
pop %rbp
ret
