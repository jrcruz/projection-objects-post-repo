	.file	"decomposition-comparison.cpp"
	.text
	.globl	main
	.type	main, @function
main:
.LFB271:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$1, -4(%rbp)
	movl	$1, -8(%rbp)
	movl	$1, -12(%rbp)
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE271:
	.size	main, .-main
	.ident	"GCC: (GNU) 13.1.1 20230614 (Red Hat 13.1.1-4)"
	.section	.note.GNU-stack,"",@progbits
