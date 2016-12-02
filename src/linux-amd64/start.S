#include "syscalls.h"

/* enable intel asm syntax without the % prefix for registers */
.intel_syntax noprefix

/* this marks the .text section of a PE executable, which contains
program code */
.text
	/* exports _start, syscall? to other compilation units (files) */
	.globl _start,
	.globl syscall0, syscall1, syscall2, syscall3, syscall4, syscall5

	_start:
		xor rbp,rbp /* xoring a value with itself = 0 */
		pop rdi /* rdi = argc */

		/* the pop instruction already added 8 to rsp */
		mov rsi,rsp /* rest of the stack as an array of char ptr */

		/* zero the las 4 bits of rsp, aligning it to 16 bytes
		same as "and rsp,0xfffffffffffffff0" because negative
		numbers are represented as
		max_unsigned_value + 1 - abs(negative_num) */
		and rsp,-16
		call main

		mov rdi,rax /* syscall param 1 = rax (ret value of main) */
		mov rax,sys_exit
		syscall

		ret /* should never be reached, but if the OS somehow fails
		to kill us, it will cause a segmentation fault */
		ret

	syscall0:
		mov rax,rdi	/* rax (syscall number) = func param 1 (rdi) */
		syscall
		ret

	syscall1:
		mov rax,rdi	/* rax (syscall number) = func param 1 (rdi) */
		mov rdi,rsi	/* rdi (syscall param 1) = func param 2 (rsi) */
		syscall
		ret

	syscall2:
		mov rax,rdi	/* rax (syscall number) = func param 1 (rdi) */
		mov rdi,rsi	/* rdi (syscall param 1) = func param 2 (rsi) */
		mov rsi,rdx	/* rsi (syscall param 2) = func param 3 (rdx) */
		syscall
		ret

	syscall3:
		mov rax,rdi	/* rax (syscall number) = func param 1 (rdi) */
		mov rdi,rsi	/* rdi (syscall param 1) = func param 2 (rsi) */
		mov rsi,rdx	/* rsi (syscall param 2) = func param 3 (rdx) */
		mov rdx,rcx	/* rdx (syscall param 3) = func param 4 (rcx) */
		syscall
		ret

	syscall4:
		mov rax,rdi	/* rax (syscall number) = func param 1 (rdi) */
		mov rdi,rsi	/* rdi (syscall param 1) = func param 2 (rsi) */
		mov rsi,rdx	/* rsi (syscall param 2) = func param 3 (rdx) */
		mov rdx,rcx	/* rdx (syscall param 3) = func param 4 (rcx) */
		mov r10,r8	/* r10 (syscall param 4) = func param 5 (r8) */
		syscall
		ret

	syscall5:
		mov rax,rdi	/* rax (syscall number) = func param 1 (rdi) */
		mov rdi,rsi	/* rdi (syscall param 1) = func param 2 (rsi) */
		mov rsi,rdx	/* rsi (syscall param 2) = func param 3 (rdx) */
		mov rdx,rcx	/* rdx (syscall param 3) = func param 4 (rcx) */
		mov r10,r8	/* r10 (syscall param 4) = func param 5 (r8) */
		mov r8,r9	/* r8 (syscall param 5) = func param 6 (r9) */
		syscall
		ret