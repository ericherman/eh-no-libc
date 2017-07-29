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

#include "syscalls.h"

.intel_syntax noprefix
.text
	.globl _start,
	.globl syscall0, syscall1, syscall2, syscall3, syscall4, syscall5

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
		mov eax,SYS_exit
		int 0x80
		ret

	syscall0:
		mov eax,[esp+4]
		int 0x80
		ret

	syscall1:
		push ebx
		mov eax,[esp+4+4]
		mov ebx,[esp+8+4]
		int 0x80
		pop ebx
		ret

	syscall2:
		push ebx
		mov eax,[esp+4+4]
		mov ebx,[esp+8+4]
		mov ecx,[esp+12+4]
		int 0x80
		pop ebx
		ret

	syscall3:
		push ebx
		mov eax,[esp+4+4]
		mov ebx,[esp+8+4]
		mov ecx,[esp+12+4]
		mov edx,[esp+16+4]
		int 0x80
		pop ebx
		ret

	syscall4:
		push ebx
		push esi
		mov eax,[esp+4+8]
		mov ebx,[esp+8+8]
		mov ecx,[esp+12+8]
		mov edx,[esp+16+8]
		mov esi,[esp+20+8]
		int 0x80
		pop esi
		pop ebx
		ret

	syscall5:
		push ebx
		push esi
		push edi
		mov eax,[esp+4+12]
		mov ebx,[esp+8+12]
		mov ecx,[esp+12+12]
		mov edx,[esp+16+12]
		mov esi,[esp+20+12]
		mov edi,[esp+24+12]
		int 0x80
		pop edi
		pop esi
		pop ebx
		ret
