/*
eh-no-libc - exploring coding without the standard library
Copyright (C) 2017 Eric Herman

This work is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later
version.

This work is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License (COPYING) along with this library; if not, see:

        https://www.gnu.org/licenses/old-licenses/lgpl-2.1.txt
*/
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "eh-printf/eh-printf.h"

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

int vprintf(const char *format, va_list ap)
{
	return eh_vprintf(format, ap);
}

int printf(const char *format, ...)
{
	va_list ap;
	int rv;
	va_start(ap, format);
	rv = eh_vprintf(format, ap);
	va_end(ap);
	return rv;

}

int vsnprintf(char *buf, size_t len, const char *format, va_list ap)
{
	return eh_vsnprintf(buf, len, format, ap);
}

int snprintf(char *buf, size_t len, const char *format, ...)
{
	va_list ap;
	int rv;
	va_start(ap, format);
	rv = vsnprintf(buf, len, format, ap);
	va_end(ap);
	return rv;

}
