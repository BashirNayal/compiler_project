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
	pushq	%r15
	pushq	%r14
	pushq	%r13
	pushq	%r12
	pushq	%rbx
	subq	$120, %rsp
	.cfi_offset %rbx, -56
	.cfi_offset %r12, -48
	.cfi_offset %r13, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	movabsq	$12884901892, %rax              # imm = 0x300000004
	movq	%rax, -88(%rbp)
	movabsq	$8589934597, %rax               # imm = 0x200000005
	movq	%rax, -80(%rbp)
	movabsq	$12884901889, %rax              # imm = 0x300000001
	movq	%rax, -72(%rbp)
	movabsq	$12884901890, %rax              # imm = 0x300000002
	movq	%rax, -64(%rbp)
	callq	get_time@PLT
	movl	%eax, -48(%rbp)                 # 4-byte Spill
	movq	$7, -160(%rbp)
	movl	$1, %ebx
	.p2align	4, 0x90
.LBB2_1:                                # %entry.while.cond
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB2_3 Depth 2
	testl	%ebx, %ebx
	js	.LBB2_12
# %bb.2:                                # %entry.while.start
                                        #   in Loop: Header=BB2_1 Depth=1
	movslq	%ebx, %rax
	movslq	-160(%rbp,%rax,4), %r15
	leal	-1(%rbx), %r14d
	movl	%r14d, %edi
	movl	$8, %esi
	callq	__check_bounds__@PLT
	movslq	%r14d, %rax
	movl	-160(%rbp,%rax,4), %r14d
	addl	$-2, %ebx
	movq	%rbx, -96(%rbp)                 # 8-byte Spill
	movq	%rsp, %rbx
	leaq	-16(%rbx), %rsp
	movl	%r15d, %edi
	movl	$8, %esi
	callq	__check_bounds__@PLT
	movl	-88(%rbp,%r15,4), %eax
	movl	%eax, -16(%rbx)
	movq	%rsp, %rax
	leaq	-16(%rax), %rcx
	movq	%rcx, -120(%rbp)                # 8-byte Spill
	movq	%rcx, %rsp
	leal	-1(%r14), %ecx
	movl	%ecx, -16(%rax)
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rdx
	movq	%rdx, -112(%rbp)                # 8-byte Spill
	movq	%rdx, %rsp
	movq	%r14, -128(%rbp)                # 8-byte Spill
	movl	%r14d, -16(%rcx)
	movq	%rsp, %rdx
	leaq	-16(%rdx), %rsp
	movq	%r15, -104(%rbp)                # 8-byte Spill
	leal	-1(%r15), %r14d
	movl	%r14d, -16(%rdx)
	movl	-16(%rbx), %r12d
	movl	-16(%rcx), %ebx
	movl	-16(%rax), %eax
	movl	%eax, -44(%rbp)                 # 4-byte Spill
	movl	%r14d, -56(%rbp)                # 4-byte Spill
	movl	%r12d, -52(%rbp)                # 4-byte Spill
	jmp	.LBB2_3
	.p2align	4, 0x90
.LBB2_6:                                # %entry.while.start.while.start.endif
                                        #   in Loop: Header=BB2_3 Depth=2
	incl	%ebx
.LBB2_3:                                # %entry.while.start.while.cond
                                        #   Parent Loop BB2_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	cmpl	%r14d, %ebx
	jg	.LBB2_7
# %bb.4:                                # %entry.while.start.while.start
                                        #   in Loop: Header=BB2_3 Depth=2
	movl	%ebx, %edi
	movl	$8, %esi
	callq	__check_bounds__@PLT
	movslq	%ebx, %r15
	cmpl	%r12d, -88(%rbp,%r15,4)
	jg	.LBB2_6
# %bb.5:                                # %entry.while.start.while.start.if
                                        #   in Loop: Header=BB2_3 Depth=2
	movl	-44(%rbp), %r13d                # 4-byte Reload
	incl	%r13d
	movq	%rsp, %r12
	leaq	-16(%r12), %rsp
	movl	%r13d, %edi
	movl	$8, %esi
	callq	__check_bounds__@PLT
	movl	%r13d, -44(%rbp)                # 4-byte Spill
	movslq	%r13d, %r14
	movl	-88(%rbp,%r14,4), %eax
	movl	%eax, -16(%r12)
	movl	%r14d, %edi
	movl	$8, %esi
	callq	__check_bounds__@PLT
	movl	%ebx, %edi
	movl	$8, %esi
	callq	__check_bounds__@PLT
	movl	-88(%rbp,%r15,4), %eax
	movl	%eax, -88(%rbp,%r14,4)
	movl	-56(%rbp), %r14d                # 4-byte Reload
	movl	%ebx, %edi
	movl	$8, %esi
	callq	__check_bounds__@PLT
	movl	-16(%r12), %eax
	movl	-52(%rbp), %r12d                # 4-byte Reload
	movl	%eax, -88(%rbp,%r15,4)
	jmp	.LBB2_6
	.p2align	4, 0x90
.LBB2_7:                                # %entry.while.start.while.end
                                        #   in Loop: Header=BB2_1 Depth=1
	movq	-112(%rbp), %rax                # 8-byte Reload
	movl	%ebx, (%rax)
	movq	-120(%rbp), %r12                # 8-byte Reload
	movl	-44(%rbp), %eax                 # 4-byte Reload
	movl	%eax, (%r12)
	movq	%rsp, %r14
	leaq	-16(%r14), %rsp
	movl	(%r12), %ebx
	incl	%ebx
	movl	%ebx, %edi
	movl	$8, %esi
	callq	__check_bounds__@PLT
	movslq	%ebx, %rax
	movl	-88(%rbp,%rax,4), %eax
	movl	%eax, -16(%r14)
	movl	(%r12), %ebx
	incl	%ebx
	movl	%ebx, %edi
	movl	$8, %esi
	callq	__check_bounds__@PLT
	movslq	%ebx, %r15
	movq	-104(%rbp), %rbx                # 8-byte Reload
	movl	%ebx, %edi
	movl	$8, %esi
	callq	__check_bounds__@PLT
	movslq	%ebx, %r13
	movl	-88(%rbp,%r13,4), %eax
	movl	%eax, -88(%rbp,%r15,4)
	movl	%ebx, %edi
	movl	$8, %esi
	callq	__check_bounds__@PLT
	movl	-16(%r14), %eax
	movl	%eax, -88(%rbp,%r13,4)
	movq	%rsp, %rax
	leaq	-16(%rax), %r14
	movq	%r14, %rsp
	movl	(%r12), %ecx
	incl	%ecx
	movl	%ecx, -16(%rax)
	movq	%rsp, %rcx
	leaq	-16(%rcx), %rsp
	movl	-16(%rax), %eax
	decl	%eax
	movl	%eax, -16(%rcx)
	movq	-128(%rbp), %r13                # 8-byte Reload
	cmpl	%r13d, %eax
	jle	.LBB2_8
# %bb.9:                                # %entry.while.start.while.end.if
                                        #   in Loop: Header=BB2_1 Depth=1
	movq	-96(%rbp), %rbx                 # 8-byte Reload
	leal	1(%rbx), %r15d
	movl	%r15d, %edi
	movl	$8, %esi
	callq	__check_bounds__@PLT
	movslq	%r15d, %rax
	movl	%r13d, -160(%rbp,%rax,4)
	addl	$2, %ebx
	movl	%ebx, %edi
	movl	$8, %esi
	callq	__check_bounds__@PLT
	movslq	%ebx, %rax
	movl	(%r14), %ecx
	decl	%ecx
	movl	%ecx, -160(%rbp,%rax,4)
	jmp	.LBB2_10
	.p2align	4, 0x90
.LBB2_8:                                #   in Loop: Header=BB2_1 Depth=1
	movq	-96(%rbp), %rbx                 # 8-byte Reload
.LBB2_10:                               # %entry.while.start.while.end.endif
                                        #   in Loop: Header=BB2_1 Depth=1
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	(%r14), %ecx
	incl	%ecx
	movl	%ecx, -16(%rax)
	movq	-104(%rbp), %r12                # 8-byte Reload
	cmpl	%r12d, %ecx
	jge	.LBB2_1
# %bb.11:                               # %entry.while.start.while.end.endif.if
                                        #   in Loop: Header=BB2_1 Depth=1
	leal	1(%rbx), %r15d
	movl	%r15d, %edi
	movl	$8, %esi
	callq	__check_bounds__@PLT
	movslq	%r15d, %rax
	movl	(%r14), %ecx
	incl	%ecx
	movl	%ecx, -160(%rbp,%rax,4)
	addl	$2, %ebx
	movl	%ebx, %edi
	movl	$8, %esi
	callq	__check_bounds__@PLT
	movslq	%ebx, %rax
	movl	%r12d, -160(%rbp,%rax,4)
	jmp	.LBB2_1
.LBB2_12:                               # %entry.while.end
	movq	%rsp, %rbx
	leaq	-16(%rbx), %rsp
	callq	get_time@PLT
	movl	%eax, -16(%rbx)
	movq	%rsp, %rax
	leaq	-16(%rax), %rsp
	movl	$0, -16(%rax)
	movl	-16(%rbx), %esi
	subl	-48(%rbp), %esi                 # 4-byte Folded Reload
	movq	__unnamed_2@GOTPCREL(%rip), %rdi
	xorl	%eax, %eax
	callq	printf@PLT
	xorl	%eax, %eax
	leaq	-40(%rbp), %rsp
	popq	%rbx
	popq	%r12
	popq	%r13
	popq	%r14
	popq	%r15
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
