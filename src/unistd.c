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
#include <unistd.h>
#include <sys/stat.h>
#include <syscall.h>

#if ((defined LINUX_I386) || (defined LINUX_AMD64))
ssize_t write(int fd, void const *data, size_t nbytes)
{
	void *vpfd;

	/* avoid WARN if sizeof(ssize_t) != sizeof(int) */
	vpfd = (void *)(ssize_t)fd;

	return (ssize_t)syscall3(SYS_write, vpfd, (void *)data, (void *)nbytes);
}

int stat(const char *pathname, struct stat *buf)
{
	return (int)(ssize_t)syscall2(SYS_stat, (void *)pathname, (void *)buf);
}
#endif
