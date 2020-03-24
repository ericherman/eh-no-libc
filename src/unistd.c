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
#include <limits.h>
#include <fcntl.h>
#include <stdarg.h>

#if ((defined LINUX_I386) || (defined LINUX_AMD64))

int ehnlc_open(const char *pathname, int flags, ...)
{
	mode_t mode;

	if ((flags & O_CREAT) || (flags & O_TMPFILE)) {
		va_list arg;
		va_start(arg, flags);
		mode = va_arg(arg, mode_t);
		va_end(arg);
	} else {
		mode = 0;
	}

	return (int)(ssize_t)ehnlc_syscall3(SYS_open, (void *)pathname,
					    (void *)(ssize_t)flags,
					    (void *)(ssize_t)mode);
}

int ehnlc_close(int fd)
{
	return (int)(ssize_t)ehnlc_syscall1(SYS_close, (void *)(ssize_t)fd);
}

ssize_t ehnlc_read(int fd, void *buf, size_t count)
{
	return (ssize_t)ehnlc_syscall3(SYS_read, (void *)(ssize_t)fd,
				       (void *)buf, (void *)count);
}

int ehnlc_unlink(const char *pathname)
{
	return (int)(ssize_t)ehnlc_syscall1(SYS_close, (void *)pathname);
}

ssize_t ehnlc_write(int fd, void const *data, size_t nbytes)
{
	void *vpfd;

	/* avoid WARN if sizeof(ssize_t) != sizeof(int) */
	vpfd = (void *)(ssize_t)fd;

	return (ssize_t)ehnlc_syscall3(SYS_write, vpfd, (void *)data,
				       (void *)nbytes);
}

int ehnlc_stat(const char *pathname, struct stat *buf)
{
	return (int)(ssize_t)ehnlc_syscall2(SYS_stat, (void *)pathname,
					    (void *)buf);
}

long ehnlc_sysconf(int name)
{
	switch (name) {
	case 30 /* _SC_PAGESIZE */ :
		return 4096;
	default:
		return -1;
	}
}

#endif
