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
#include <syscall.h>

#if ((defined LINUX_I386) || (defined LINUX_AMD64))

static void ehnlc_segfault(void)
{
	*((int *)(NULL)) = -1;
}

void ehnlc_crash(const char *msg, size_t len)
{
	void *stderr_vpfd = (void *)2;

	ehnlc_syscall3(SYS_write, stderr_vpfd, (void *)"FATAL ERROR '",
		       (void *)13);
	ehnlc_syscall3(SYS_write, stderr_vpfd, (void *)msg, (void *)len);
	ehnlc_syscall3(SYS_write, stderr_vpfd, (void *)"', HALT.\n", (void *)9);

	ehnlc_segfault();
}

#endif /* if ((defined LINUX_I386) || (defined LINUX_AMD64)) */
