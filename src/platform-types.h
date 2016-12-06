#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

#if defined LINUX_AMD64
#include "linux-amd64/types.h"
#elif defined LINUX_I386
#include "linux-i386/types.h"
#endif

typedef uint64_t dev_t;
typedef ssize_t syscall_slong_t;
typedef ssize_t time_t;

/*
  http://pubs.opengroup.org/onlinepubs/007908775/xsh/time.h.html

  The <time.h> header declares the structure timespec
*/
typedef struct {
	time_t sec;
	syscall_slong_t nsec;
} timespec;

/*
   "man 2 stat" describes "struct stat *" but I am not yet clear the best way
   to define this in a non-conflicting way, until then I shall use stat_info_s
*/
typedef struct {
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
} stat_info_s;

#endif /* LINIX_TYPES_H */
