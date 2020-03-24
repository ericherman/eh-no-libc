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
#ifndef _UNISTD_H
#define _UNISTD_H	1

#define _SC_PAGESIZE	30

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2

#include <sys/stat.h>

#if ((defined LINUX_AMD64) || (defined LINUX_I386))

#define close(fd) ehnlc_close(fd)
int ehnlc_close(int fd);

#define read(fd, buf, count) ehnlc_read(fd, buf, count)
ssize_t ehnlc_read(int fd, void *buf, size_t count);

#define stat(pathname, buf) ehnlc_stat(pathname, buf)
int ehnlc_stat(const char *pathname, struct stat *buf);

#define sysconf(name) ehnlc_sysconf(name)
long ehnlc_sysconf(int name);

#define unlink(pathname) ehnlc_unlink(pathname)
int ehnlc_unlink(const char *pathname);

#define write(fd, data, nbytes) ehnlc_write(fd, data, nbytes)
ssize_t ehnlc_write(int fd, void const *data, size_t nbytes);

#endif /* ((defined LINUX_AMD64) || (defined LINUX_I386)) */

#endif /* _UNISTD_H */
