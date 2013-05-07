L3:
	.asciz  "%d "
L5:
	.asciz  "\n"
.section .text

.type fact, @function
fact:
pushq %rbp
movq %rsp, %rbp
subq $8, %rsp
movq %rdi, -8(%rbp)
movq -8(%rbp), %rbx
movq $0, %rcx
cmpq %rbx, %rcx
je L0
movq -8(%rbp), %rbx
movq %rbx, -8(%rbp)
movq -8(%rbp), %rbx
movq $1, %rcx
movq %rbx, %rdx
subq %rcx, %rbx
movq %rbx, %rdi
movq $0, %rax
call fact
imulq -8(%rbp), %rax
jmp EXIT2
L0:
movq $1, %rbx
movq %rbx, %rax
jmp EXIT2
EXIT2:
movq %rbp, %rsp
popq %rbp
ret

.type printArray, @function
printArray:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
movq %rdi, -8(%rbp)
movq %rsi, -16(%rbp)
movq %rdx, -24(%rbp)
movq -16(%rbp), %rbx
movq -8(%rbp), %rcx
movq 0(%rcx), %rdx
cmpq %rbx, %rdx
je L2
movq $L3, %rbx
movq %rbx, %rdi
pushq %rdi
movq -16(%rbp), %rbx
addq $1, %rbx
imulq $8, %rbx
movq -8(%rbp), %rcx
addq %rbx, %rcx
movq (%rcx), %rbx
movq %rbx, %rdi
movq -24(%rbp), %rbx
call *%rbx
popq %rdi
movq %rax, %rsi
movq $0, %rax
call printf
pushq %rax
movq -8(%rbp), %rbx
movq %rbx, %rdi
movq -16(%rbp), %rbx
movq $1, %rcx
addq %rbx, %rcx
movq %rcx, %rsi
movq -24(%rbp), %rcx
movq %rcx, %rdx
movq $0, %rax
call printArray
popq %rax
jmp L4
L2:
movq $L5, %rbx
movq %rbx, %rdi
movq $0, %rax
call printf
L4:
EXIT3:
movq %rbp, %rsp
popq %rbp
ret
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
movq $1, %rbx
pushq %rbx
movq $64, %rdi
call malloc
movq %rax, -16(%rbp)
popq %rbx
movq -16(%rbp), %rcx
movq $7, 0(%rcx)
movq %rbx, 8(%rcx)
movq $2, %rbx
movq %rbx, 16(%rcx)
movq $4, %rbx
movq %rbx, 24(%rcx)
movq $5, %rbx
movq %rbx, 32(%rcx)
movq $8, %rbx
movq %rbx, 40(%rcx)
movq $7, %rbx
movq %rbx, 48(%rcx)
movq $3, %rbx
movq %rbx, 56(%rcx)
movq %rcx, -8(%rbp)
movq -8(%rbp), %rbx
movq %rbx, %rdi
movq $0, %rbx
movq %rbx, %rsi
movq $fact, %rbx
movq %rbx, %rdx
movq $0, %rax
call printArray
mov %rbp, %rsp
pop %rbp
ret
