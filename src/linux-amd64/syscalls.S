/*
eh-no-libc - exploring coding without the standard library
Copyright (C) 2017 Eric Herman

This work is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later
version.

This work is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License (COPYING) along with this library; if not, see:

        https://www.gnu.org/licenses/old-licenses/lgpl-2.1.txt
*/

/* enable intel asm syntax without the % prefix for registers */
.intel_syntax noprefix

/* this marks the .text section of a PE executable, which contains
program code */
.text
	/* exports _start, syscall? to other compilation units (files) */
	.globl ehnlc_syscall0, ehnlc_syscall1, ehnlc_syscall2,
	.globl ehnlc_syscall3, ehnlc_syscall4, ehnlc_syscall5,
	.globl ehnlc_syscall6,

	/* Registers %rbp, %rbx and %r12 through %r15 "belong" to the calling
	 * function and the called function is required to preserve their
	 * values. */

	ehnlc_syscall0:
		mov rax,rdi	/* rax (syscall number) = func param 1 (rdi) */
		syscall
		ret

	ehnlc_syscall1:
		mov rax,rdi	/* rax (syscall number) = func param 1 (rdi) */
		mov rdi,rsi	/* rdi (syscall param 1) = func param 2 (rsi) */
		syscall
		ret

	ehnlc_syscall2:
		mov rax,rdi	/* rax (syscall number) = func param 1 (rdi) */
		mov rdi,rsi	/* rdi (syscall param 1) = func param 2 (rsi) */
		mov rsi,rdx	/* rsi (syscall param 2) = func param 3 (rdx) */
		syscall
		ret

	ehnlc_syscall3:
		mov rax,rdi	/* rax (syscall number) = func param 1 (rdi) */
		mov rdi,rsi	/* rdi (syscall param 1) = func param 2 (rsi) */
		mov rsi,rdx	/* rsi (syscall param 2) = func param 3 (rdx) */
		mov rdx,rcx	/* rdx (syscall param 3) = func param 4 (rcx) */
		syscall
		ret

	ehnlc_syscall4:
		mov rax,rdi	/* rax (syscall number) = func param 1 (rdi) */
		mov rdi,rsi	/* rdi (syscall param 1) = func param 2 (rsi) */
		mov rsi,rdx	/* rsi (syscall param 2) = func param 3 (rdx) */
		mov rdx,rcx	/* rdx (syscall param 3) = func param 4 (rcx) */
		mov r10,r8	/* r10 (syscall param 4) = func param 5 (r8) */
		syscall
		ret

	ehnlc_syscall5:
		mov rax,rdi	/* rax (syscall number) = func param 1 (rdi) */
		mov rdi,rsi	/* rdi (syscall param 1) = func param 2 (rsi) */
		mov rsi,rdx	/* rsi (syscall param 2) = func param 3 (rdx) */
		mov rdx,rcx	/* rdx (syscall param 3) = func param 4 (rcx) */
		mov r10,r8	/* r10 (syscall param 4) = func param 5 (r8) */
		mov r8,r9	/* r8 (syscall param 5) = func param 6 (r9) */
		syscall
		ret

	ehnlc_syscall6:
		mov rax,rdi	/* rax (syscall number) = func param 1 (rdi) */
		mov rdi,rsi	/* rdi (syscall param 1) = func param 2 (rsi) */
		mov rsi,rdx	/* rsi (syscall param 2) = func param 3 (rdx) */
		mov rdx,rcx	/* rdx (syscall param 3) = func param 4 (rcx) */
		mov r10,r8	/* r10 (syscall param 4) = func param 5 (r8) */
		mov r8,r9	/* r8 (syscall param 5) = func param 6 (r9) */
		mov r9,[rsp+8]	/* r9 (syscall param 6) = func param 7 (sp+8) */
		syscall
		ret
