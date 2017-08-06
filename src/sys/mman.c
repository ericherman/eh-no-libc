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

#if ((!defined(USE_LEGACY_MMAP)) && defined(LINUX_I386))
#define USE_LEGACY_MMAP 1
#endif

#ifndef USE_LEGACY_MMAP
#define USE_LEGACY_MMAP 0
#endif

static void *legacy_mmap(void *addr, size_t len, int prot, int flags, int fd,
			 off_t offset)
{
	void *params[7];

	params[0] = addr;
	params[1] = (void *)((long)len);
	params[2] = (void *)((long)prot);
	params[3] = (void *)((long)flags);
	params[4] = (void *)((long)fd);
	params[5] = (void *)((long)offset);
	params[6] = 0;

	return syscall1(SYS_mmap, (void *)params);
}

void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset)
{
	void *rv;
	long s_rv;
#if _Sys_mman_c_debug
	char buf[70];
#endif

	if (USE_LEGACY_MMAP) {
		rv = legacy_mmap(addr, len, prot, flags, fd, offset);
	} else {
		rv = syscall6(SYS_mmap, addr, (void *)len,
			      (void *)(ssize_t)prot, (void *)(ssize_t)flags,
			      (void *)(ssize_t)fd, (void *)(ssize_t)offset);
	}
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
