/*
dumb-os-alloc.c: operating specific code for allocator
Copyright (C) 2012, 2017 Eric Herman <eric@freesa.org>

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
#include <dumb-os-alloc.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>

#ifndef MAP_ANONYMOUS
#ifdef MAP_ANON
#define MAP_ANONYMOUS MAP_ANON
#else
/* from: /usr/include/asm-generic/mman-common.h */
#define MAP_ANONYMOUS 0x20	/* don't use a file */
#endif
#endif

#ifndef DUMB_ALLOC_MEM_LIMIT
#define DUMB_ALLOC_MEM_LIMIT (1 * 1024 * 1024 * 1024)
#endif

char *dumb_os_mmap(size_t length)
{
	void *memory, *addr;
	int prot, flags, fd, offset;

	addr = NULL;
	prot = PROT_READ | PROT_WRITE;
	flags = MAP_PRIVATE | MAP_ANONYMOUS;
	fd = -1;
	offset = 0;

	/*
	   fprintf(stderr, "requesting %lu bytes.\n", length);
	 */
#ifdef DEBUG
	fprintf(stderr, "addr: NULL\n");
	fprintf(stderr, "len: %lu\n", (unsigned long)length);
	fprintf(stderr, "prot: %x\n", prot);
	fprintf(stderr, "flags: %x\n", flags);
	fprintf(stderr, "fd: %d\n", fd);
	fprintf(stderr, "offset: %d\n", offset);
#endif

	memory = mmap(addr, length, prot, flags, fd, offset);

	if (!memory) {
		fprintf(stderr, "Could not allocate %lu bytes\n",
			(unsigned long)length);
	}

	return (char *)memory;
}

int dumb_os_munmap(void *addr, size_t bytes_length)
{
	return munmap(addr, bytes_length);
}

size_t dumb_os_page_size(void)
{
	return (size_t)sysconf(_SC_PAGESIZE);
}

size_t dumb_os_mem_limit(void)
{
	return DUMB_ALLOC_MEM_LIMIT;
}
