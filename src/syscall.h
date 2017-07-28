#ifndef _SYSCALL_H
#define _SYSCALL_H	1

#include "stdint.h"

#if ((defined LINUX_I386) || (defined LINUX_AMD64))

#if USE_HOST_SYS_SYSCALL_H
#include <sys/syscall.h>
#else
#if defined LINUX_AMD64
#include "linux-amd64/syscalls.h"
#elif defined LINUX_I386
#include "linux-i386/syscalls.h"
#endif
#endif

void *syscall0(size_t number);
void *syscall1(size_t number, void *arg1);
void *syscall2(size_t number, void *arg1, void *arg2);
void *syscall3(size_t number, void *arg1, void *arg2, void *arg3);
void *syscall4(size_t number, void *arg1, void *arg2, void *arg3, void *arg4);
void *syscall5(size_t number, void *arg1, void *arg2, void *arg3, void *arg4,
	       void *arg5);

#endif /* if ((defined LINUX_I386) || (defined LINUX_AMD64)) */

#endif /* _SYSCALL_H */
