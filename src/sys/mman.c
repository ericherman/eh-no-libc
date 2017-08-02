#include <sys/mman.h>
#include <syscall.h>
#include <errno.h>

#ifndef DEBUG
#define _Sys_mman_c_debug 0
#else
#define _Sys_mman_c_debug 1
#include <string.h>		/* strlen, strerror */
#include "eh-printf/eh-printf.h"	/* eh_snprintf */
#endif

void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset)
{
	void *rv;
	long s_rv;

#if _Sys_mman_c_debug
	char buf[70];
#endif

	errno = 0;
	rv = syscall6(SYS_mmap, addr, (void *)len, (void *)(ssize_t)prot,
		      (void *)(ssize_t)flags, (void *)(ssize_t)fd,
		      (void *)(ssize_t)offset);

	s_rv = (long)((ssize_t)rv);

	if (s_rv < 0) {
		errno = -s_rv;
#if _Sys_mman_c_debug
		eh_snprintf(buf, 70, "mmap returned %ld, errno: %d (%s)?", s_rv,
			    errno, strerror(errno));
		_eh_crash(buf, strlen(buf));
#endif
	}

	return s_rv < 0 ? NULL : rv;
}

/* returns zero on succuess */
int munmap(void *addr, size_t len)
{
	void *rv;

	rv = syscall2(SYS_munmap, addr, (void *)len);

	return rv == NULL ? 0 : -1;
}

#undef _Sys_mman_c_debug
