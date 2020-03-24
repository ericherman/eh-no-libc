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
#include <sys/mman.h>
#include <syscall.h>
#include <errno.h>
#include <unistd.h>

#if ((!defined(USE_LEGACY_MMAP)) && defined(LINUX_I386))
#define USE_LEGACY_MMAP 1
#endif

#ifndef USE_LEGACY_MMAP
#define USE_LEGACY_MMAP 0
#endif

static void *ehnlc_legacy_mmap(void *addr, size_t len, int prot, int flags,
			       int fd, off_t offset)
{
	void *params[7];
	long page_size;

	page_size = sysconf(_SC_PAGESIZE);
	if (offset % page_size) {
		offset = page_size * (1 + (offset / page_size));
	}
	if (len % page_size) {
		len = page_size * (1 + (len / page_size));
	}

	params[0] = addr;
	params[1] = (void *)((long)len);
	params[2] = (void *)((long)prot);
	params[3] = (void *)((long)flags);
	params[4] = (void *)((long)fd);
	params[5] = (void *)((long)offset);
	params[6] = NULL;

	return ehnlc_syscall1(SYS_mmap, (void *)params);
}

void *ehnlc_mmap(void *addr, size_t len, int prot, int flags, int fd,
		 off_t offset)
{
	void *rv;
	long s_rv;

	if (USE_LEGACY_MMAP) {
		rv = ehnlc_legacy_mmap(addr, len, prot, flags, fd, offset);
	} else {
		rv = ehnlc_syscall6(SYS_mmap, addr, (void *)len,
				    (void *)(ssize_t)prot,
				    (void *)(ssize_t)flags,
				    (void *)(ssize_t)fd,
				    (void *)(ssize_t)offset);
	}
	s_rv = (long)((ssize_t)rv);

	if (s_rv < 0 && s_rv >= -4096) {
		errno = -s_rv;
	}

	return (s_rv < 0 && s_rv >= -4096) ? NULL : rv;
}

/* returns zero on succuess */
int ehnlc_munmap(void *addr, size_t len)
{
	void *rv;

	rv = ehnlc_syscall2(SYS_munmap, addr, (void *)len);

	return rv == NULL ? 0 : -1;
}
