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
	.globl syscall0, syscall1, syscall2, syscall3, syscall4, syscall5
	.globl syscall6

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

	/* XXX FIXME this is broken */
	syscall6:
		push ebx
		push esi
		push edi
		push ebp

		mov eax,[esp+4+16]
		mov ebx,[esp+8+16]
		mov ecx,[esp+12+16]
		mov edx,[esp+16+16]
		mov esi,[esp+20+16]
		mov edi,[esp+24+16]
		mov ebp,[esp+28+16]

		int 0x80

		pop ebp
		pop edi
		pop esi
		pop ebx
		ret