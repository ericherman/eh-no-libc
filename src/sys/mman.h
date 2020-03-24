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
#ifndef _SYS_MMAN_H
#define _SYS_MMAN_H	1

#include <stdint.h>

#define PROT_NONE	0x00
#define PROT_READ	0x01
#define PROT_WRITE	0x02
#define PROT_EXEC	0x04

#define MAP_FILE	0x00
#define MAP_SHARED      0x01
#define MAP_PRIVATE     0x02
#define MAP_FIXED	0x10
#define MAP_ANONYMOUS	0x20
#define MAP_ANON	MAP_ANONYMOUS

#define MAP_GROWSDOWN	0x00100
#define MAP_DENYWRITE	0x00800
#define MAP_EXECUTABLE	0x01000
#define MAP_LOCKED	0x02000
#define MAP_NORESERVE	0x04000
#define MAP_POPULATE	0x08000
#define MAP_NONBLOCK	0x10000
#define MAP_STACK	0x20000
#define MAP_HUGETLB	0x40000

#define PROT_GROWSDOWN	0x01000000
#define PROT_GROWSUP	0x02000000

#define mmap(addr, len, prot, flags, fd, offset) \
  ehnlc_mmap(addr, len, prot, flags, fd, offset)
void *ehnlc_mmap(void *addr, size_t len, int prot, int flags, int fd,
		 off_t offset);

#define munmap(addr, len) ehnlc_munmap(addr, len)
int ehnlc_munmap(void *addr, size_t len);

#endif /* _SYS_MMAN_H */
