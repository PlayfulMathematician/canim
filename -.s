	.file	"-"
	.text
	.globl	f                               # -- Begin function f
	.p2align	4
	.type	f,@function
f:                                      # @f
	.cfi_startproc
# %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	bswapl	%eax
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	f, .Lfunc_end0-f
	.cfi_endproc
                                        # -- End function
	.ident	"clang version 21.1.6"
	.section	".note.GNU-stack","",@progbits
	.addrsig
