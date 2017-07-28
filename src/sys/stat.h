#ifndef _SYS_STAT_H
#define _SYS_STAT_H	1

#include "stdint.h"
#include "time.h"

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
