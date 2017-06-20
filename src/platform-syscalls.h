#ifndef PLATFORM_SYSCALLS_H
#define PLATFORM_SYSCALLS_H

#include "platform-types.h"

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

ssize_t write(int fd, void const *data, size_t nbytes);

int stat(const char *pathname, stat_info_s *buf);

#endif /* if ((defined LINUX_I386) || (defined LINUX_AMD64)) */

#endif /* PLATFORM_SYSCALLS_H */
