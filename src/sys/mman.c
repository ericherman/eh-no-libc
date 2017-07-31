#include <sys/mman.h>
#include <syscall.h>

#ifdef DEBUG
#define Crash_on_MAP_FAILED 1
#else
#define Crash_on_MAP_FAILED 0
#endif

#ifndef MAP_FAILED
#define MAP_FAILED ((void*)((ssize_t)-1UL))
#define _Sys_mman_c_need_undef_MAP_FAILED
#endif
void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset)
{
	void *rv;

	rv = syscall6(SYS_mmap, addr, (void *)len, (void *)(ssize_t)prot,
		      (void *)(ssize_t)flags, (void *)(ssize_t)fd,
		      (void *)(ssize_t)offset);

	if (rv == MAP_FAILED && Crash_on_MAP_FAILED) {
		_eh_crash("mmap failed", 11);
	}

	return rv;
}

#ifdef _Sys_mman_c_need_undef_MAP_FAILED
#undef MAP_FAILED
#undef _Sys_mman_c_need_undef_MAP_FAILED
#endif

/* returns zero on succuess */
int munmap(void *addr, size_t len)
{
	void *rv;

	rv = syscall2(SYS_munmap, addr, (void *)len);

	return rv == NULL ? 0 : -1;
}
