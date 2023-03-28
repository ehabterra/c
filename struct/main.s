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
	subq	$64, %rsp
	movl	$0, -4(%rbp)
	leaq	-56(%rbp), %rdi
	xorl	%esi, %esi
	movl	$48, %edx
	callq	_memset
	movl	$4, -56(%rbp)
	leaq	L_.str(%rip), %rax
	movq	%rax, -48(%rbp)
	movl	$13, -40(%rbp)
	leaq	L_.str.1(%rip), %rax
	movq	%rax, -24(%rbp)
	leaq	L_.str.2(%rip), %rax
	movq	%rax, -16(%rbp)
	movl	-56(%rbp), %esi
	leaq	L_.str.3(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-48(%rbp), %rsi
	leaq	L_.str.4(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-24(%rbp), %rsi
	movq	-16(%rbp), %rdx
	leaq	L_.str.5(%rip), %rdi
	movb	$0, %al
	callq	_printf
	xorl	%eax, %eax
	addq	$64, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"Ehab Terra"

L_.str.1:                               ## @.str.1
	.asciz	"Giza"

L_.str.2:                               ## @.str.2
	.asciz	"Egypt"

L_.str.3:                               ## @.str.3
	.asciz	"Student id = %d\n"

L_.str.4:                               ## @.str.4
	.asciz	"Student name = %s\n"

L_.str.5:                               ## @.str.5
	.asciz	"Student address = %s, %s\n"

.subsections_via_symbols
