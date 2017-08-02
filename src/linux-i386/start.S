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

.intel_syntax noprefix
.text
	.globl _start,

	_start:
		xor ebp,ebp
		pop esi /* argc */
		mov ecx,esp /* argv */

		/* 16-byte stack alignment is not mandatory here but
		according to glibc it improves SSE performance */
		and esp,-16
		push 0x4badc0de
		push 0x68f1dead
		push ecx /* argv */
		push esi /* argc */
		call main

		/* on i386 it's up to the caller to clean up the stack. we can
		either pop them into scratch registers or just add the total
		size of the parameters in bytes to the stack pointer */
		add esp,16

		mov ebx,eax
		mov eax,1 /* SYS_exit */
		int 0x80
		ret
