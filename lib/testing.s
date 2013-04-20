	.file	"testing.c"
	.text
	.globl	fun
	.type	fun, @function
fun:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movsd	%xmm0, -24(%rbp)
	movsd	%xmm1, -32(%rbp)
	movabsq	$4623074495985101046, %rax
	movq	%rax, -8(%rbp)
	movsd	-24(%rbp), %xmm0
	ucomisd	-32(%rbp), %xmm0
	seta	%al
	testb	%al, %al
	je	.L2
	movsd	-24(%rbp), %xmm0
	ucomisd	-32(%rbp), %xmm0
	seta	%al
	testb	%al, %al
	je	.L2
	movsd	-24(%rbp), %xmm0
	jmp	.L3
.L2:
	movsd	-24(%rbp), %xmm1
	movsd	.LC1(%rip), %xmm0
	addsd	%xmm1, %xmm0
	movsd	-32(%rbp), %xmm1
	call	fun
	addsd	-24(%rbp), %xmm0
.L3:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	fun, .-fun
	.section	.rodata
	.align 8
.LC1:
	.long	0
	.long	1072693248
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
