#include <sys/mman.h>
#include <syscall.h>

void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset)
{
	return (void *)syscall6(SYS_mmap, addr, (void *)len, (void *)prot,
				(void *)flags, (void *)fd, (void *)offset);
}

int munmap(void *addr, size_t len)
{
	return (int)syscall2(SYS_munmap, addr, (void *)len);
}
