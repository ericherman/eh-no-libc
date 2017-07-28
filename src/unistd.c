#include "unistd.h"
#include "sys/stat.h"
#include "syscall.h"

#if ((defined LINUX_I386) || (defined LINUX_AMD64))
ssize_t write(int fd, void const *data, size_t nbytes)
{
	void *vpfd;

	/* avoid WARN if sizeof(ssize_t) != sizeof(int) */
	vpfd = (void *)(ssize_t)fd;

	return (ssize_t)syscall3(SYS_write, vpfd, (void *)data, (void *)nbytes);
}

int stat(const char *pathname, struct stat *buf)
{
	return (int)(ssize_t)syscall2(SYS_stat, (void *)pathname, (void *)buf);
}
#endif
