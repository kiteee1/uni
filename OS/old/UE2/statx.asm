	.file	"statx.cpp"
	.text
	.section	.rodata
	.type	_ZStL19piecewise_construct, @object
	.size	_ZStL19piecewise_construct, 1
_ZStL19piecewise_construct:
	.zero	1
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.text
	.globl	_Z8my_statxiPKcijP5statx
	.type	_Z8my_statxiPKcijP5statx, @function
_Z8my_statxiPKcijP5statx:
.LFB1572:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	%edi, -4(%rbp)
	movq	%rsi, -16(%rbp)
	movl	%edx, -8(%rbp)
	movl	%ecx, -20(%rbp)
	movq	%r8, -32(%rbp)
	movq	-32(%rbp), %rdi
	movl	-20(%rbp), %esi
	movl	-8(%rbp), %ecx
	movq	-16(%rbp), %rdx
	movl	-4(%rbp), %eax
	movq	%rdi, %r9
	movl	%esi, %r8d
	movl	%eax, %esi
	movl	$332, %edi
	movl	$0, %eax
	call	syscall@PLT
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1572:
	.size	_Z8my_statxiPKcijP5statx, .-_Z8my_statxiPKcijP5statx
	.globl	_Z14mode_to_stringB5cxx11t
	.type	_Z14mode_to_stringB5cxx11t, @function
_Z14mode_to_stringB5cxx11t:
.LFB1573:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA1573
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movq	%rdi, -40(%rbp)
	movl	%esi, %eax
	movw	%ax, -44(%rbp)
	leaq	-17(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcEC1Ev@PLT
	leaq	-17(%rbp), %rdx
	movq	-40(%rbp), %rax
	movq	%rdx, %rcx
	movl	$45, %edx
	movl	$10, %esi
	movq	%rax, %rdi
.LEHB0:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EmcRKS3_@PLT
.LEHE0:
	leaq	-17(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movzwl	-44(%rbp), %eax
	andl	$61440, %eax
	cmpl	$16384, %eax
	jne	.L4
	movq	-40(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
.LEHB1:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEixEm@PLT
	movb	$100, (%rax)
	jmp	.L5
.L4:
	movzwl	-44(%rbp), %eax
	andl	$61440, %eax
	cmpl	$40960, %eax
	jne	.L6
	movq	-40(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEixEm@PLT
	movb	$108, (%rax)
	jmp	.L5
.L6:
	movzwl	-44(%rbp), %eax
	andl	$61440, %eax
	cmpl	$8192, %eax
	jne	.L7
	movq	-40(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEixEm@PLT
	movb	$99, (%rax)
	jmp	.L5
.L7:
	movzwl	-44(%rbp), %eax
	andl	$61440, %eax
	cmpl	$24576, %eax
	jne	.L8
	movq	-40(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEixEm@PLT
	movb	$98, (%rax)
	jmp	.L5
.L8:
	movzwl	-44(%rbp), %eax
	andl	$61440, %eax
	cmpl	$4096, %eax
	jne	.L9
	movq	-40(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEixEm@PLT
	movb	$112, (%rax)
	jmp	.L5
.L9:
	movzwl	-44(%rbp), %eax
	andl	$61440, %eax
	cmpl	$49152, %eax
	jne	.L10
	movq	-40(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEixEm@PLT
	movb	$115, (%rax)
	jmp	.L5
.L10:
	movq	-40(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEixEm@PLT
	movb	$45, (%rax)
.L5:
	movzwl	-44(%rbp), %eax
	andl	$256, %eax
	testl	%eax, %eax
	je	.L11
	movq	-40(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEixEm@PLT
	movb	$114, (%rax)
.L11:
	movzwl	-44(%rbp), %eax
	andl	$128, %eax
	testl	%eax, %eax
	je	.L12
	movq	-40(%rbp), %rax
	movl	$2, %esi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEixEm@PLT
	movb	$119, (%rax)
.L12:
	movzwl	-44(%rbp), %eax
	andl	$64, %eax
	testl	%eax, %eax
	je	.L13
	movq	-40(%rbp), %rax
	movl	$3, %esi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEixEm@PLT
	movb	$120, (%rax)
.L13:
	movzwl	-44(%rbp), %eax
	andl	$32, %eax
	testl	%eax, %eax
	je	.L14
	movq	-40(%rbp), %rax
	movl	$4, %esi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEixEm@PLT
	movb	$114, (%rax)
.L14:
	movzwl	-44(%rbp), %eax
	andl	$16, %eax
	testl	%eax, %eax
	je	.L15
	movq	-40(%rbp), %rax
	movl	$5, %esi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEixEm@PLT
	movb	$119, (%rax)
.L15:
	movzwl	-44(%rbp), %eax
	andl	$8, %eax
	testl	%eax, %eax
	je	.L16
	movq	-40(%rbp), %rax
	movl	$6, %esi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEixEm@PLT
	movb	$120, (%rax)
.L16:
	movzwl	-44(%rbp), %eax
	andl	$4, %eax
	testl	%eax, %eax
	je	.L17
	movq	-40(%rbp), %rax
	movl	$7, %esi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEixEm@PLT
	movb	$114, (%rax)
.L17:
	movzwl	-44(%rbp), %eax
	andl	$2, %eax
	testl	%eax, %eax
	je	.L18
	movq	-40(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEixEm@PLT
	movb	$119, (%rax)
.L18:
	movzwl	-44(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L25
	movq	-40(%rbp), %rax
	movl	$9, %esi
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEixEm@PLT
.LEHE1:
	movb	$120, (%rax)
	jmp	.L25
.L23:
	movq	%rax, %rbx
	leaq	-17(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSaIcED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB2:
	call	_Unwind_Resume@PLT
.L24:
	movq	%rax, %rbx
	movq	-40(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
	call	_Unwind_Resume@PLT
.LEHE2:
.L25:
	nop
	movq	-40(%rbp), %rax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1573:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA1573:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1573-.LLSDACSB1573
.LLSDACSB1573:
	.uleb128 .LEHB0-.LFB1573
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L23-.LFB1573
	.uleb128 0
	.uleb128 .LEHB1-.LFB1573
	.uleb128 .LEHE1-.LEHB1
	.uleb128 .L24-.LFB1573
	.uleb128 0
	.uleb128 .LEHB2-.LFB1573
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
.LLSDACSE1573:
	.text
	.size	_Z14mode_to_stringB5cxx11t, .-_Z14mode_to_stringB5cxx11t
	.section	.rodata
.LC0:
	.string	"Usage: "
.LC1:
	.string	" <filename>"
	.align 8
.LC2:
	.string	"Error getting statx for file: "
.LC3:
	.string	"UID: "
.LC4:
	.string	", GID: "
.LC5:
	.string	"Size: "
	.text
	.globl	main
	.type	main, @function
main:
.LFB1574:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA1574
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$328, %rsp
	.cfi_offset 3, -24
	movl	%edi, -324(%rbp)
	movq	%rsi, -336(%rbp)
	cmpl	$2, -324(%rbp)
	je	.L27
	leaq	.LC0(%rip), %rsi
	leaq	_ZSt4cerr(%rip), %rdi
.LEHB3:
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movq	-336(%rbp), %rax
	movq	(%rax), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	leaq	.LC1(%rip), %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPFRSoS_E@PLT
	movl	$1, %eax
	jmp	.L33
.L27:
	movq	-336(%rbp), %rax
	movq	8(%rax), %rax
	movq	%rax, -24(%rbp)
	leaq	-320(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %r8
	movl	$2047, %ecx
	movl	$0, %edx
	movq	%rax, %rsi
	movl	$-100, %edi
	call	_Z8my_statxiPKcijP5statx
	cmpl	$-1, %eax
	sete	%al
	testb	%al, %al
	je	.L29
	leaq	.LC2(%rip), %rsi
	leaq	_ZSt4cerr(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rbx
	call	__errno_location@PLT
	movl	(%rax), %eax
	movl	%eax, %edi
	call	strerror@PLT
	movq	%rax, %rsi
	movq	%rbx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPFRSoS_E@PLT
	movl	$1, %eax
	jmp	.L33
.L29:
	leaq	.LC3(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movl	-300(%rbp), %eax
	movl	%eax, %esi
	movq	%rdx, %rdi
	call	_ZNSolsEj@PLT
	leaq	.LC4(%rip), %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movl	-296(%rbp), %eax
	movl	%eax, %esi
	movq	%rdx, %rdi
	call	_ZNSolsEj@PLT
	movq	%rax, %rdx
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPFRSoS_E@PLT
	leaq	.LC5(%rip), %rsi
	leaq	_ZSt4cout(%rip), %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movq	-280(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEy@PLT
	movq	%rax, %rdx
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPFRSoS_E@PLT
	movzwl	-292(%rbp), %eax
	movzwl	%ax, %edx
	leaq	-64(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	_Z14mode_to_stringB5cxx11t
.LEHE3:
	leaq	-64(%rbp), %rax
	movq	%rax, %rsi
	leaq	_ZSt4cout(%rip), %rdi
.LEHB4:
	call	_ZStlsIcSt11char_traitsIcESaIcEERSt13basic_ostreamIT_T0_ES7_RKNSt7__cxx1112basic_stringIS4_S5_T1_EE@PLT
	movq	%rax, %rdx
	movq	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@GOTPCREL(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEPFRSoS_E@PLT
.LEHE4:
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movl	$0, %eax
	jmp	.L33
.L32:
	movq	%rax, %rbx
	leaq	-64(%rbp), %rax
	movq	%rax, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	%rbx, %rax
	movq	%rax, %rdi
.LEHB5:
	call	_Unwind_Resume@PLT
.LEHE5:
.L33:
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1574:
	.section	.gcc_except_table
.LLSDA1574:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE1574-.LLSDACSB1574
.LLSDACSB1574:
	.uleb128 .LEHB3-.LFB1574
	.uleb128 .LEHE3-.LEHB3
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB4-.LFB1574
	.uleb128 .LEHE4-.LEHB4
	.uleb128 .L32-.LFB1574
	.uleb128 0
	.uleb128 .LEHB5-.LFB1574
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0
	.uleb128 0
.LLSDACSE1574:
	.text
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB2078:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L36
	cmpl	$65535, -8(%rbp)
	jne	.L36
	leaq	_ZStL8__ioinit(%rip), %rdi
	call	_ZNSt8ios_base4InitC1Ev@PLT
	leaq	__dso_handle(%rip), %rdx
	leaq	_ZStL8__ioinit(%rip), %rsi
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rax
	movq	%rax, %rdi
	call	__cxa_atexit@PLT
.L36:
	nop
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2078:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I__Z8my_statxiPKcijP5statx, @function
_GLOBAL__sub_I__Z8my_statxiPKcijP5statx:
.LFB2079:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2079:
	.size	_GLOBAL__sub_I__Z8my_statxiPKcijP5statx, .-_GLOBAL__sub_I__Z8my_statxiPKcijP5statx
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I__Z8my_statxiPKcijP5statx
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.hidden	__dso_handle
	.ident	"GCC: (Debian 10.2.1-6) 10.2.1 20210110"
	.section	.note.GNU-stack,"",@progbits
