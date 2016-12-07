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
void *syscall5(size_t number, void *arg1, void *arg2, void *arg3, void *arg4,
	       void *arg5);

/* yes, I know it is poor form to define function impls in header files */
ssize_t write(int fd, void const *data, size_t nbytes)
{
	void *vpfd;

	/* avoid WARN if sizeof(ssize_t) != sizeof(int) */
	vpfd = (void *)(ssize_t)fd;

	return (ssize_t)syscall3(SYS_write, vpfd, (void *)data, (void *)nbytes);
}

int stat(const char *pathname, stat_info_s *buf)
{
	return (int)(ssize_t)syscall2(SYS_stat, (void *)pathname, (void *)buf);
}
#endif

#endif /* PLATFORM_SYSCALLS_H */
