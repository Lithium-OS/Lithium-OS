	.file	"fat32.c"
	.globl	fat1_location
	.bss
	.align 4
	.type	fat1_location, @object
	.size	fat1_location, 4
fat1_location:
	.zero	4
	.globl	fat_length
	.align 4
	.type	fat_length, @object
	.size	fat_length, 4
fat_length:
	.zero	4
	.globl	root_dir_location
	.align 4
	.type	root_dir_location, @object
	.size	root_dir_location, 4
root_dir_location:
	.zero	4
	.globl	data_location
	.align 4
	.type	data_location, @object
	.size	data_location, 4
data_location:
	.zero	4
	.globl	fat_ptr
	.align 4
	.type	fat_ptr, @object
	.size	fat_ptr, 4
fat_ptr:
	.zero	4
	.text
	.type	fat32_init_func, @function
fat32_init_func:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	movl	8(%ebp), %eax
	movl	%eax, fat1_location
	movl	12(%ebp), %eax
	movl	%eax, fat_length
	movl	16(%ebp), %eax
	movl	%eax, root_dir_location
	movl	20(%ebp), %eax
	movl	%eax, data_location
	nop
	popl	%ebp
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	fat32_init_func, .-fat32_init_func
	.globl	sec_temp
	.data
	.align 32
	.type	sec_temp, @object
	.size	sec_temp, 512
sec_temp:
	.byte	1
	.zero	511
	.text
	.globl	utest
	.type	utest, @function
utest:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$4, %esp
	movl	8(%ebp), %eax
	movb	%al, -4(%ebp)
	movb	$15, -4(%ebp)
	movzbl	-4(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	utest, .-utest
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	$65
	call	utest
	addl	$4, %esp
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.12) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
