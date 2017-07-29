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
#ifndef _STDIO_H
#define _STDIO_H	1

#include <stdarg.h>
#include <unistd.h>

#define stdin STDIN_FILENO
#define stdout STDOUT_FILENO
#define stderr STDERR_FILENO

#ifndef EOF
#define EOF (-1)
#endif

/* writes the string s and a trailing newline to stdout. */
int puts(char const *str);

/* writes the character c, cast to an unsigned char to stdout */
int putchar(int c);

/*
int fputc(int c, FILE *stream);
int fputs(const char *s, FILE *stream);
int putc(int c, FILE *stream);
*/

int vprintf(const char *format, va_list ap);
int printf(const char *format, ...);

int vsnprintf(char *buf, size_t len, const char *format, va_list ap);
int snprintf(char *buf, size_t len, const char *format, ...);

#endif /* _STDIO_H */
