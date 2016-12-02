#include "ehlibc.h"
#include "syscalls.h"

iptr write(int fd, void const *data, uptr nbytes)
{
	return (iptr) syscall5(
		sys_write,
		(void*)(iptr)fd, /* avoid warning if sizeof(iptr) != sizeof(int) */
		(void*)data,
		(void*)nbytes,
		0, /* ignored */
		0 /* ignored */
		);
}

uptr strlen(char const *str)
{
	char const *p;
	for (p = str; *p; ++p);
	return p - str;
}


int puts(char const *str)
{
	return write(stdout, str, strlen(str));
}
