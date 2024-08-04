	.file	"a.cpp"
	.text
#APP
	.globl _ZSt21ios_base_library_initv
#NO_APP
	.globl	main
	.type	main, @function
main:
.LFB1983:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movw	$1, -64(%rbp)
	movw	$2, -62(%rbp)
	movw	$3, -60(%rbp)
	movw	$1, -58(%rbp)
	movw	$1, -56(%rbp)
	movw	$2, -54(%rbp)
	movw	$1, -52(%rbp)
	movw	$5, -50(%rbp)
	movw	$5, -48(%rbp)
	movw	$7, -46(%rbp)
	movw	$15, -44(%rbp)
	movw	$1, -42(%rbp)
	movw	$3, -30(%rbp)
	movw	$4, -32(%rbp)
	movl	$-5, -80(%rbp)
	movl	$-3, -76(%rbp)
	movl	$-9, -72(%rbp)
	movl	$-10, -68(%rbp)
	movl	$0, -96(%rbp)
	movl	$1, -92(%rbp)
	movl	$2, -88(%rbp)
	movl	$3, -84(%rbp)
.L2:
	movw	$0, -2(%rbp)
	jmp	.L3
.L7:
	movw	$-32768, -4(%rbp)
	movw	$0, -6(%rbp)
	jmp	.L4
.L6:
	movswl	-6(%rbp), %edx
	movswl	-32(%rbp), %eax
	imull	%eax, %edx
	movswl	-2(%rbp), %eax
	addl	%edx, %eax
	cltq
	movzwl	-64(%rbp,%rax,2), %eax
	cmpw	%ax, -4(%rbp)
	jge	.L5
	movswl	-6(%rbp), %edx
	movswl	-32(%rbp), %eax
	imull	%eax, %edx
	movswl	-2(%rbp), %eax
	addl	%edx, %eax
	cltq
	movzwl	-64(%rbp,%rax,2), %eax
	movw	%ax, -4(%rbp)
.L5:
	movzwl	-6(%rbp), %eax
	addl	$1, %eax
	movw	%ax, -6(%rbp)
.L4:
	movzwl	-6(%rbp), %eax
	cmpw	-30(%rbp), %ax
	jl	.L6
	movswl	-2(%rbp), %eax
	movswl	-4(%rbp), %edx
	cltq
	movl	%edx, -80(%rbp,%rax,4)
	movzwl	-2(%rbp), %eax
	addl	$1, %eax
	movw	%ax, -2(%rbp)
.L3:
	movzwl	-2(%rbp), %eax
	cmpw	-32(%rbp), %ax
	jl	.L7
	movw	$0, -8(%rbp)
	jmp	.L8
.L9:
	movswl	-8(%rbp), %eax
	cltq
	movl	-80(%rbp,%rax,4), %eax
	movl	%eax, %esi
	leaq	_ZSt4cout(%rip), %rax
	movq	%rax, %rdi
	call	_ZNSolsEi@PLT
	movl	$32, %esi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@PLT
	movzwl	-8(%rbp), %eax
	addl	$1, %eax
	movw	%ax, -8(%rbp)
.L8:
	movzwl	-8(%rbp), %eax
	cmpw	-32(%rbp), %ax
	jl	.L9
	nop
.L10:
	movl	$1, -12(%rbp)
	movswl	-32(%rbp), %eax
	subl	$1, %eax
	movl	%eax, -16(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, -20(%rbp)
	jmp	.L11
.L21:
	movl	-20(%rbp), %eax
	cltq
	movl	-80(%rbp,%rax,4), %eax
	movl	%eax, -100(%rbp)
	movl	-12(%rbp), %eax
	cltq
	movl	-80(%rbp,%rax,4), %eax
	movl	%eax, -104(%rbp)
	movl	-20(%rbp), %eax
	cltq
	movl	-96(%rbp,%rax,4), %eax
	movl	%eax, -108(%rbp)
	movl	-12(%rbp), %eax
	cltq
	movl	-96(%rbp,%rax,4), %eax
	movl	%eax, -112(%rbp)
	movl	-100(%rbp), %edx
	movl	-104(%rbp), %eax
	cmpl	%eax, %edx
	jge	.L13
	leaq	-104(%rbp), %rdx
	leaq	-100(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZSt4swapIiENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS4_ESt18is_move_assignableIS4_EEE5valueEvE4typeERS4_SE_
	leaq	-112(%rbp), %rdx
	leaq	-108(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZSt4swapIiENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS4_ESt18is_move_assignableIS4_EEE5valueEvE4typeERS4_SE_
	jmp	.L13
.L16:
	movl	-20(%rbp), %eax
	leal	2(%rax), %ecx
	movl	-20(%rbp), %eax
	cltq
	movl	-80(%rbp,%rax,4), %edx
	movslq	%ecx, %rax
	movl	%edx, -80(%rbp,%rax,4)
	movl	-20(%rbp), %eax
	leal	2(%rax), %ecx
	movl	-20(%rbp), %eax
	cltq
	movl	-96(%rbp,%rax,4), %edx
	movslq	%ecx, %rax
	movl	%edx, -96(%rbp,%rax,4)
.L13:
	cmpl	$0, -20(%rbp)
	jle	.L14
	subl	$1, -20(%rbp)
	movl	-20(%rbp), %eax
	cltq
	movl	-80(%rbp,%rax,4), %edx
	movl	-100(%rbp), %eax
	cmpl	%eax, %edx
	jle	.L14
	movl	$1, %eax
	jmp	.L15
.L14:
	movl	$0, %eax
.L15:
	testb	%al, %al
	jne	.L16
	movl	-100(%rbp), %edx
	addl	$1, -20(%rbp)
	movl	-20(%rbp), %eax
	addl	$1, %eax
	cltq
	movl	%edx, -80(%rbp,%rax,4)
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	-108(%rbp), %edx
	cltq
	movl	%edx, -96(%rbp,%rax,4)
	jmp	.L17
.L20:
	movl	-20(%rbp), %eax
	leal	1(%rax), %ecx
	movl	-20(%rbp), %eax
	cltq
	movl	-80(%rbp,%rax,4), %edx
	movslq	%ecx, %rax
	movl	%edx, -80(%rbp,%rax,4)
	movl	-20(%rbp), %eax
	leal	1(%rax), %ecx
	movl	-20(%rbp), %eax
	cltq
	movl	-96(%rbp,%rax,4), %edx
	movslq	%ecx, %rax
	movl	%edx, -96(%rbp,%rax,4)
.L17:
	cmpl	$0, -20(%rbp)
	jle	.L18
	subl	$1, -20(%rbp)
	movl	-20(%rbp), %eax
	cltq
	movl	-80(%rbp,%rax,4), %edx
	movl	-104(%rbp), %eax
	cmpl	%eax, %edx
	jle	.L18
	movl	$1, %eax
	jmp	.L19
.L18:
	movl	$0, %eax
.L19:
	testb	%al, %al
	jne	.L20
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	-104(%rbp), %edx
	cltq
	movl	%edx, -80(%rbp,%rax,4)
	movl	-20(%rbp), %eax
	addl	$1, %eax
	movl	-112(%rbp), %edx
	cltq
	movl	%edx, -96(%rbp,%rax,4)
	addl	$1, -12(%rbp)
	movl	-12(%rbp), %eax
	movl	%eax, -20(%rbp)
.L11:
	addl	$1, -12(%rbp)
	movl	-12(%rbp), %eax
	cmpl	-16(%rbp), %eax
	setle	%al
	testb	%al, %al
	jne	.L21
	movl	-16(%rbp), %eax
	cltq
	movl	-80(%rbp,%rax,4), %eax
	movl	%eax, -36(%rbp)
	movl	-16(%rbp), %eax
	cltq
	movl	-96(%rbp,%rax,4), %eax
	movl	%eax, -40(%rbp)
	jmp	.L22
.L25:
	movl	-16(%rbp), %eax
	leal	1(%rax), %ecx
	movl	-16(%rbp), %eax
	cltq
	movl	-80(%rbp,%rax,4), %edx
	movslq	%ecx, %rax
	movl	%edx, -80(%rbp,%rax,4)
	movl	-16(%rbp), %eax
	leal	1(%rax), %ecx
	movl	-16(%rbp), %eax
	cltq
	movl	-96(%rbp,%rax,4), %edx
	movslq	%ecx, %rax
	movl	%edx, -96(%rbp,%rax,4)
.L22:
	cmpl	$0, -16(%rbp)
	jle	.L23
	subl	$1, -16(%rbp)
	movl	-16(%rbp), %eax
	cltq
	movl	-80(%rbp,%rax,4), %eax
	cmpl	%eax, -36(%rbp)
	jge	.L23
	movl	$1, %eax
	jmp	.L24
.L23:
	movl	$0, %eax
.L24:
	testb	%al, %al
	jne	.L25
	movl	-16(%rbp), %eax
	addl	$1, %eax
	cltq
	movl	-36(%rbp), %edx
	movl	%edx, -80(%rbp,%rax,4)
	movl	-16(%rbp), %eax
	addl	$1, %eax
	cltq
	movl	-40(%rbp), %edx
	movl	%edx, -96(%rbp,%rax,4)
.L26:
	movl	$10, %esi
	leaq	_ZSt4cout(%rip), %rax
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@PLT
	movl	$0, -24(%rbp)
	jmp	.L27
.L28:
	movl	-24(%rbp), %eax
	cltq
	movl	-80(%rbp,%rax,4), %eax
	movl	%eax, %esi
	leaq	_ZSt4cout(%rip), %rax
	movq	%rax, %rdi
	call	_ZNSolsEi@PLT
	movl	$32, %esi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@PLT
	addl	$1, -24(%rbp)
.L27:
	movswl	-32(%rbp), %eax
	cmpl	%eax, -24(%rbp)
	jl	.L28
	movl	$10, %esi
	leaq	_ZSt4cout(%rip), %rax
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@PLT
	movl	$0, -28(%rbp)
	jmp	.L29
.L30:
	movl	-28(%rbp), %eax
	cltq
	movl	-96(%rbp,%rax,4), %eax
	movl	%eax, %esi
	leaq	_ZSt4cout(%rip), %rax
	movq	%rax, %rdi
	call	_ZNSolsEi@PLT
	movl	$32, %esi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@PLT
	addl	$1, -28(%rbp)
.L29:
	movswl	-32(%rbp), %eax
	cmpl	%eax, -28(%rbp)
	jl	.L30
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1983:
	.size	main, .-main
	.section	.text._ZSt4swapIiENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS4_ESt18is_move_assignableIS4_EEE5valueEvE4typeERS4_SE_,"axG",@progbits,_ZSt4swapIiENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS4_ESt18is_move_assignableIS4_EEE5valueEvE4typeERS4_SE_,comdat
	.weak	_ZSt4swapIiENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS4_ESt18is_move_assignableIS4_EEE5valueEvE4typeERS4_SE_
	.type	_ZSt4swapIiENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS4_ESt18is_move_assignableIS4_EEE5valueEvE4typeERS4_SE_, @function
_ZSt4swapIiENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS4_ESt18is_move_assignableIS4_EEE5valueEvE4typeERS4_SE_:
.LFB2240:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	movl	(%rax), %eax
	movl	%eax, -4(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	movl	(%rax), %edx
	movq	-24(%rbp), %rax
	movl	%edx, (%rax)
	leaq	-4(%rbp), %rax
	movq	%rax, %rdi
	call	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	movl	(%rax), %edx
	movq	-32(%rbp), %rax
	movl	%edx, (%rax)
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2240:
	.size	_ZSt4swapIiENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS4_ESt18is_move_assignableIS4_EEE5valueEvE4typeERS4_SE_, .-_ZSt4swapIiENSt9enable_ifIXsrSt6__and_IJSt6__not_ISt15__is_tuple_likeIT_EESt21is_move_constructibleIS4_ESt18is_move_assignableIS4_EEE5valueEvE4typeERS4_SE_
	.section	.text._ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_,"axG",@progbits,_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_,comdat
	.weak	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	.type	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_, @function
_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_:
.LFB2340:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2340:
	.size	_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_, .-_ZSt4moveIRiEONSt16remove_referenceIT_E4typeEOS2_
	.section	.rodata
	.type	_ZNSt8__detail30__integer_to_chars_is_unsignedIjEE, @object
	.size	_ZNSt8__detail30__integer_to_chars_is_unsignedIjEE, 1
_ZNSt8__detail30__integer_to_chars_is_unsignedIjEE:
	.byte	1
	.type	_ZNSt8__detail30__integer_to_chars_is_unsignedImEE, @object
	.size	_ZNSt8__detail30__integer_to_chars_is_unsignedImEE, 1
_ZNSt8__detail30__integer_to_chars_is_unsignedImEE:
	.byte	1
	.type	_ZNSt8__detail30__integer_to_chars_is_unsignedIyEE, @object
	.size	_ZNSt8__detail30__integer_to_chars_is_unsignedIyEE, 1
_ZNSt8__detail30__integer_to_chars_is_unsignedIyEE:
	.byte	1
	.ident	"GCC: (Debian 13.2.0-13) 13.2.0"
	.section	.note.GNU-stack,"",@progbits
