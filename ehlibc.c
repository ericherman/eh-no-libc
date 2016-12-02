#include "ehlibc.h"
#include "syscalls.h"

void *syscall0(uptr number);
void *syscall1(uptr number, void *arg1);
void *syscall2(uptr number, void *arg1, void *arg2);
void *syscall3(uptr number, void *arg1, void *arg2, void *arg3);
void *syscall4(uptr number, void *arg1, void *arg2, void *arg3, void *arg4);
void *syscall5(uptr number, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5);

static iptr write(int fd, void const *data, uptr nbytes)
{
	return (iptr) syscall3(
		sys_write,
		(void*)(iptr)fd, /* avoid warning if sizeof(iptr) != sizeof(int) */
		(void*)data,
		(void*)nbytes
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
