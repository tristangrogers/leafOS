/* Constants for multiboot header */
.set ALIGN,    1 << 0
.set MEMINFO,  1 << 1
.set FLAGS,    ALIGN | MEMINFO
.set MAGIC,    0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

/* Multiboot header */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Stack metadata */
.section .bss
.align 16          # x86 stack must be 16-byte aligned
stack_bottom:
.skip 16384        # 16kb stack
stack_top:

/* 
   start is the entry point for the kernel and the 
   bootloader jumps to this position once the kernel
   has been loaded
*/

.section .text
.global start
.type start, @function
start:
	mov $stack_top, %esp
	call kernel_main
	
	fail:
		cli
		hlt
		jmp fail

.size start, . - start
