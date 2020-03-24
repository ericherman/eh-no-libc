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
#ifndef _SYSCALL_H
#define _SYSCALL_H	1

#include <stdint.h>

#if ((defined LINUX_I386) || (defined LINUX_AMD64))

#if defined LINUX_AMD64
#include "linux-amd64/syscalls.h"
#elif defined LINUX_I386
#include "linux-i386/syscalls.h"
#endif

void *ehnlc_syscall0(size_t number);
void *ehnlc_syscall1(size_t number, void *arg1);
void *ehnlc_syscall2(size_t number, void *arg1, void *arg2);
void *ehnlc_syscall3(size_t number, void *arg1, void *arg2, void *arg3);
void *ehnlc_syscall4(size_t number, void *arg1, void *arg2, void *arg3,
		     void *arg4);
void *ehnlc_syscall5(size_t number, void *arg1, void *arg2, void *arg3,
		     void *arg4, void *arg5);
void *ehnlc_syscall6(size_t number, void *arg1, void *arg2, void *arg3,
		     void *arg4, void *arg5, void *arg6);
void *ehnlc_syscall7(size_t number, void *arg1, void *arg2, void *arg3,
		     void *arg4, void *arg5, void *arg6, void *arg7);

void ehnlc_crash(const char *msg, size_t len);

#endif /* if ((defined LINUX_I386) || (defined LINUX_AMD64)) */

#endif /* _SYSCALL_H */
