L3:
	.asciz  "%d\n"
.section .text

.type sub, @function
sub:
pushq %rbp
movq %rsp, %rbp
subq $16, %rsp
movq %rdi, -8(%rbp)
movq %rsi, -16(%rbp)
movq -8(%rbp), %rbx
movq -16(%rbp), %rcx
movq %rbx, %rdx
subq %rcx, %rbx
movq %rbx, %rax
jmp EXIT2
EXIT2:
movq %rbp, %rsp
popq %rbp
ret

.type fibo, @function
fibo:
pushq %rbp
movq %rsp, %rbp
subq $24, %rsp
movq %rdi, -8(%rbp)
movq -8(%rbp), %rbx
movq $0, %rcx
cmpq %rbx, %rcx
je L0
movq -8(%rbp), %rbx
movq $1, %rcx
cmpq %rbx, %rcx
je L1
movq -8(%rbp), %rbx
movq %rbx, %rdi
movq $1, %rbx
movq %rbx, %rsi
call sub
movq %rax, %rdi
call fibo
movq %rax, -16(%rbp)
movq -8(%rbp), %rbx
movq %rbx, %rdi
movq $2, %rbx
movq %rbx, %rsi
call sub
movq %rax, %rdi
call fibo
movq -16(%rbp), %rbx
movq %rax, %rcx
addq %rbx, %rax
jmp EXIT3
L1:
movq $1, %rbx
movq %rbx, %rax
jmp EXIT3
L0:
movq $0, %rbx
movq %rbx, %rax
jmp EXIT3
EXIT3:
movq %rbp, %rsp
popq %rbp
ret
.globl main
.type main, @function
main:
pushq %rbp
movq %rsp, %rbp
movq $L3, %rbx
movq %rbx, %rdi
pushq %rdi
movq $20, %rbx
movq %rbx, %rdi
call fibo
popq %rdi
movq %rax, %rsi
call printf
mov %rbp, %rsp
pop %rbp
ret
