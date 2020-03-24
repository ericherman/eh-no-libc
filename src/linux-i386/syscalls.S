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
	.globl ehnlc_syscall0, ehnlc_syscall1, ehnlc_syscall2
	.globl ehnlc_syscall3, ehnlc_syscall4, ehnlc_syscall5
	.globl ehnlc_syscall6

	ehnlc_syscall0:
		mov eax,[esp+4]
		int 0x80
		ret

	ehnlc_syscall1:
		push ebx
		mov eax,[esp+4+4]
		mov ebx,[esp+4+8]
		int 0x80
		pop ebx
		ret

	ehnlc_syscall2:
		push ebx
		mov eax,[esp+4+4]
		mov ebx,[esp+4+8]
		mov ecx,[esp+4+12]
		int 0x80
		pop ebx
		ret

	ehnlc_syscall3:
		push ebx
		mov eax,[esp+4+4]
		mov ebx,[esp+4+8]
		mov ecx,[esp+4+12]
		mov edx,[esp+4+16]
		int 0x80
		pop ebx
		ret

	ehnlc_syscall4:
		push ebx
		push esi
		mov eax,[esp+8+4]
		mov ebx,[esp+8+8]
		mov ecx,[esp+8+12]
		mov edx,[esp+8+16]
		mov esi,[esp+8+20]
		int 0x80
		pop esi
		pop ebx
		ret

	ehnlc_syscall5:
		push ebx
		push esi
		push edi
		mov eax,[esp+12+4]
		mov ebx,[esp+12+8]
		mov ecx,[esp+12+12]
		mov edx,[esp+12+16]
		mov esi,[esp+12+20]
		mov edi,[esp+12+24]
		int 0x80
		pop edi
		pop esi
		pop ebx
		ret

	ehnlc_syscall6:
		push ebx
		push esi
		push edi
		push ebp

		mov eax,[esp+16+4]
		mov ebx,[esp+16+8]
		mov ecx,[esp+16+12]
		mov edx,[esp+16+16]
		mov esi,[esp+16+20]
		mov edi,[esp+16+24]
		mov ebp,[esp+16+28]

		int 0x80

		pop ebp
		pop edi
		pop esi
		pop ebx
		ret
