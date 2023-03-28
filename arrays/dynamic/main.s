	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 13, 0	sdk_version 13, 1
	.globl	_main                           ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	$0, -4(%rbp)
	movl	$0, -8(%rbp)
	movl	$2, -12(%rbp)
	movl	$0, -16(%rbp)
	movslq	-12(%rbp), %rdi
	shlq	$2, %rdi
	callq	_malloc
	movq	%rax, -24(%rbp)
LBB0_1:                                 ## =>This Inner Loop Header: Depth=1
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
	leaq	L_.str.1(%rip), %rdi
	leaq	-8(%rbp), %rsi
	movb	$0, %al
	callq	_scanf
	cmpl	$-1, -8(%rbp)
	jne	LBB0_3
## %bb.2:
	jmp	LBB0_7
LBB0_3:                                 ##   in Loop: Header=BB0_1 Depth=1
	movl	-16(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jne	LBB0_5
## %bb.4:                               ##   in Loop: Header=BB0_1 Depth=1
	movl	-12(%rbp), %eax
	shll	$1, %eax
	movl	%eax, -12(%rbp)
	movq	-24(%rbp), %rdi
	movslq	-12(%rbp), %rsi
	callq	_realloc
	movq	%rax, -24(%rbp)
	movl	-12(%rbp), %esi
	leaq	L_.str.2(%rip), %rdi
	movb	$0, %al
	callq	_printf
LBB0_5:                                 ##   in Loop: Header=BB0_1 Depth=1
	movl	-8(%rbp), %edx
	movq	-24(%rbp), %rax
	movslq	-16(%rbp), %rcx
	movl	%edx, (%rax,%rcx,4)
	movl	-16(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -16(%rbp)
## %bb.6:                               ##   in Loop: Header=BB0_1 Depth=1
	cmpl	$-1, -8(%rbp)
	jne	LBB0_1
LBB0_7:
	movl	$0, -28(%rbp)
LBB0_8:                                 ## =>This Inner Loop Header: Depth=1
	movl	-28(%rbp), %eax
	cmpl	-16(%rbp), %eax
	jge	LBB0_11
## %bb.9:                               ##   in Loop: Header=BB0_8 Depth=1
	movl	-28(%rbp), %esi
	movq	-24(%rbp), %rax
	movslq	-28(%rbp), %rcx
	movl	(%rax,%rcx,4), %edx
	leaq	L_.str.3(%rip), %rdi
	movb	$0, %al
	callq	_printf
## %bb.10:                              ##   in Loop: Header=BB0_8 Depth=1
	movl	-28(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -28(%rbp)
	jmp	LBB0_8
LBB0_11:
	movq	-24(%rbp), %rdi
	callq	_free
	xorl	%eax, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Enter (-1 to quite): "

L_.str.1:                               ## @.str.1
	.asciz	"%d"

L_.str.2:                               ## @.str.2
	.asciz	"Array new size = %d\n"

L_.str.3:                               ## @.str.3
	.asciz	"numbers[%d] = %d\n"

.subsections_via_symbols
