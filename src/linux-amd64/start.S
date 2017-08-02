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
	.globl _start,

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
		mov rax,60 /* SYS_exit */
		syscall

		ret /* should never be reached, but if the OS somehow fails
		to kill us, it will cause a segmentation fault */
		ret
