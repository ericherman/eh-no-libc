/*
eh-no-libc - exploring coding without the standard library
Copyright (C) 2020 Eric Herman

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
#include <sys/random.h>
#include <unistd.h>
#include <syscall.h>

ssize_t ehnlc_getrandom(void *buf, size_t buflen, unsigned int flags)
{
	return (ssize_t)ehnlc_syscall3(SYS_getrandom, buf, (void *)buflen,
				       (void *)(size_t)flags);
}
