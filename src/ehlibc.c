#include "ehlibc.h"
#include "platform-syscalls.h"

size_t strlen(char const *str)
{
	char const *p;
	for (p = str; *p; ++p) ;
	return p - str;
}

int puts(char const *str)
{
	return write(stdout, str, strlen(str));
}
