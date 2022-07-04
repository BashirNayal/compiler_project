	.text
	.file	"comp"
	.globl	get_time                        # -- Begin function get_time
	.p2align	4, 0x90
	.type	get_time,@function
get_time:                               # @get_time
	.cfi_startproc
# %bb.0:                                # %entry
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	leaq	8(%rsp), %rdi
	xorl	%esi, %esi
	callq	gettimeofday@PLT
	movl	16(%rsp), %eax
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	retq
.Lfunc_end0:
	.size	get_time, .Lfunc_end0-get_time
	.cfi_endproc
                                        # -- End function
	.globl	__check_bounds__                # -- Begin function __check_bounds__
	.p2align	4, 0x90
	.type	__check_bounds__,@function
__check_bounds__:                       # @__check_bounds__
	.cfi_startproc
# %bb.0:                                # %entry
	cmpl	%esi, %edi
	jl	.LBB1_2
# %bb.1:                                # %memory_err
	pushq	%rax
	.cfi_def_cfa_offset 16
	movq	__unnamed_1@GOTPCREL(%rip), %rdi
	xorl	%eax, %eax
	callq	printf@PLT
	movl	$1, %edi
	callq	exit@PLT
	popq	%rax
	.cfi_def_cfa_offset 8
.LBB1_2:                                # %memory_ok
	retq
.Lfunc_end1:
	.size	__check_bounds__, .Lfunc_end1-__check_bounds__
	.cfi_endproc
                                        # -- End function
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r14
	pushq	%rbx
	subq	$4000, %rsp                     # imm = 0xFA0
	.cfi_offset %rbx, -32
	.cfi_offset %r14, -24
	callq	get_time@PLT
	movl	%eax, %r14d
	movl	$999, %eax                      # imm = 0x3E7
	testl	%eax, %eax
	jle	.LBB2_3
	.p2align	4, 0x90
.LBB2_2:                                # %entry.while.start
                                        # =>This Inner Loop Header: Depth=1
	decl	%eax
	testl	%eax, %eax
	jg	.LBB2_2
.LBB2_3:                                # %entry.while.end
	movq	%rsp, %rbx
	leaq	-16(%rbx), %rsp
	callq	get_time@PLT
	movl	%eax, -16(%rbx)
	subl	%r14d, %eax
	movq	__unnamed_2@GOTPCREL(%rip), %rdi
	movl	%eax, %esi
	xorl	%eax, %eax
	callq	printf@PLT
	xorl	%eax, %eax
	leaq	-16(%rbp), %rsp
	popq	%rbx
	popq	%r14
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end2:
	.size	main, .Lfunc_end2-main
	.cfi_endproc
                                        # -- End function
	.type	__unnamed_1,@object             # @0
	.section	.rodata.str1.16,"aMS",@progbits,1
	.weak	__unnamed_1
	.p2align	4
__unnamed_1:
	.asciz	"error: memory violation\n"
	.size	__unnamed_1, 25

	.type	__unnamed_2,@object             # @1
	.section	.rodata.str1.1,"aMS",@progbits,1
	.weak	__unnamed_2
__unnamed_2:
	.asciz	"%d\n"
	.size	__unnamed_2, 4

	.section	".note.GNU-stack","",@progbits
