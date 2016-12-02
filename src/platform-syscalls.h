#ifndef PLATFORM_SYSCALLS_H
#define PLATFORM_SYSCALLS_H

#include "platform-types.h"

#if ((defined LINUX_I386) || (defined LINUX_AMD64))

#if defined LINUX_AMD64
#include "linux-amd64/syscalls.h"
#elif defined LINUX_I386
#include "linux-i386/syscalls.h"
#endif

void *syscall0(size_t number);
void *syscall1(size_t number, void *arg1);
void *syscall2(size_t number, void *arg1, void *arg2);
void *syscall3(size_t number, void *arg1, void *arg2, void *arg3);
void *syscall4(size_t number, void *arg1, void *arg2, void *arg3, void *arg4);
void *syscall5(size_t number, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5);

/* yes, I know it is poor form to define function impls in header files */
static ssize_t write(int fd, void const *data, size_t nbytes)
{
	return (ssize_t) syscall3(
		sys_write,
		(void*)(ssize_t)fd, /* avoid WARN if sizeof(ssize_t) != sizeof(int) */
		(void*)data,
		(void*)nbytes
		);
}
#endif

#endif /* PLATFORM_SYSCALLS_H */
