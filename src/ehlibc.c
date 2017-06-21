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
	int written;
	size_t len;

	len = strlen(str);
	written = write(stdout, str, len);
	if (written == EOF) {
		return EOF;
	}
	if (putchar('\n') == EOF) {
		return EOF;
	}
	return written + 1;
}

int putchar(int c)
{
	return write(stdout, (unsigned char *)&c, 1);
}
