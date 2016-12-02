#ifndef PLATFORM_SYSCALLS_H
#define PLATFORM_SYSCALLS_H

#include "platform-types.h"

#if ((defined LINUX_I386) || (defined LINUX_AMD64))

#if defined LINUX_AMD64
#include "linux-amd64/syscalls.h"
#elif defined LINUX_I386
#include "linux-i386/syscalls.h"
#endif

void *syscall0(uptr number);
void *syscall1(uptr number, void *arg1);
void *syscall2(uptr number, void *arg1, void *arg2);
void *syscall3(uptr number, void *arg1, void *arg2, void *arg3);
void *syscall4(uptr number, void *arg1, void *arg2, void *arg3, void *arg4);
void *syscall5(uptr number, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5);

/* yes, I know it is poor form to define function impls in header files */
static iptr write(int fd, void const *data, uptr nbytes)
{
	return (iptr) syscall3(
		sys_write,
		(void*)(iptr)fd, /* avoid WARN if sizeof(iptr) != sizeof(int) */
		(void*)data,
		(void*)nbytes
		);
}
#endif

#endif /* PLATFORM_SYSCALLS_H */
