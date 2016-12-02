#include "syscalls.h"

#ifdef __WORDSIZE
#if ( __WORDSIZE == 64 )
/* size_t */
#define uptr unsigned long
/* ssize_t */
#define iptr long
#elif ( __WORDSIZE == 32 )
/* size_t */
#define uptr unsigned int
/* ssize_t */
#define iptr int
#endif
#endif

void *syscall5(uptr number, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5);

static iptr write(int fd, void const* data, uptr nbytes)
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

uptr eh_strlen(char const* str)
{
	char const* p;
	for (p = str; *p; ++p);
	return p - str;
}

/* int main(int argc, char **argv) */
int main(void)
{
	const char *str;

	str = "hello, world\n";
	write(1, str, eh_strlen(str));

	return 0;
}
