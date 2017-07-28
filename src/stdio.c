#include "stdio.h"
#include "unistd.h"
#include "string.h"

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
