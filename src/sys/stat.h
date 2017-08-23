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
#ifndef _SYS_STAT_H
#define _SYS_STAT_H	1

#include <stdint.h>
#include <sys/time.h>
#include <linux/stat.h>

typedef uint64_t dev_t;

/*
   "man 2 stat" describes "struct stat *" but I am not yet clear the best way
   to define this in a non-conflicting way, until then I shall use stat
*/
struct stat {
	dev_t dev;
#ifdef LINUX_I386
	uint16_t __pad1;
#endif
	size_t ino;
	size_t nlink;
	uint32_t mode;
	uint32_t uid;
	uint32_t gid;
#ifdef LINUX_AMD64
	int __pad0;
#endif
	dev_t rdev;
#ifdef LINUX_I386
	uint16_t __pad2;
#endif
	ssize_t size;
	ssize_t blksize;
	ssize_t blocks;
	timespec atim;
	timespec mtim;
	timespec ctim;
#ifdef LINUX_AMD64
	syscall_slong_t __glibc_reserved[3];
#else
	uint32_t __glibc_reserved4;
	uint32_t __glibc_reserved5;
#endif
};

#endif /* _SYS_STAT_H */
