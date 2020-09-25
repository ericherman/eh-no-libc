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
#include <libio.h>
#include <unistd.h>
#include <string.h>
#include "eh-printf/eh-printf.h"
#include <fcntl.h>
#include <stdlib.h>

FILE _eh_stdin;
FILE _eh_stdout;
FILE _eh_stderr;

int _eh_stdin_init = 0;
int _eh_stdout_init = 0;
int _eh_stderr_init = 0;

FILE *stdin = &_eh_stdin;
FILE *stdout = &_eh_stdout;
FILE *stderr = &_eh_stderr;

static void _ehnlc_ensure_initialized(FILE *stream);

int ehnlc_fgetc(FILE *stream)
{
	size_t bytes, size, nmemb;
	char c;

	_ehnlc_ensure_initialized(stream);
	size = sizeof(char);
	nmemb = 1;

	bytes = fread(&c, size, nmemb, stream);
	return (bytes == 1) ? (int)c : EOF;
}

int ehnlc_puts(char const *str)
{
	int written;
	size_t len;

	len = strlen(str);
	written = write(STDOUT_FILENO, str, len);
	if (written == EOF) {
		return EOF;
	}
	if (putchar('\n') == EOF) {
		return EOF;
	}
	return written + 1;
}

int ehnlc_putchar(int c)
{
	return write(STDOUT_FILENO, (unsigned char *)&c, 1);
}

int ehnlc_putc(int c, FILE *stream)
{
	return fputc(c, stream);
}

int ehnlc_fputc(int c, FILE *stream)
{
	ssize_t rv;

	if (!stream) {
		return EOF;
	}
	rv = write(fileno(stream), (unsigned char *)&c, 1);
	return (rv == 1) ? (int)c : EOF;
}

int ehnlc_fputs(const char *s, FILE *stream)
{
	if (!stream) {
		return EOF;
	}
	return write(fileno(stream), s, strlen(s));
}

int ehnlc_vprintf(const char *format, va_list ap)
{
	return eh_vprintf(format, ap);
}

int ehnlc_printf(const char *format, ...)
{
	va_list ap;
	int rv;
	va_start(ap, format);
	rv = eh_vprintf(format, ap);
	va_end(ap);
	return rv;
}

int ehnlc_vsnprintf(char *buf, size_t len, const char *format, va_list ap)
{
	return eh_vsnprintf(buf, len, format, ap);
}

int ehnlc_snprintf(char *buf, size_t len, const char *format, ...)
{
	va_list ap;
	int rv;
	va_start(ap, format);
	rv = vsnprintf(buf, len, format, ap);
	va_end(ap);
	return rv;
}

static void _ehnlc_ensure_initialized(FILE *stream)
{
	if ((stream == stdout) && (_eh_stdout_init == 0)) {
		stdout->_fileno = STDOUT_FILENO;
		_eh_stdout_init = 1;
	} else if ((stream == stderr) && (_eh_stderr_init == 0)) {
		stderr->_fileno = STDERR_FILENO;
		_eh_stderr_init = 1;
	} else if ((stream == stdin) && (_eh_stdin_init == 0)) {
		stdin->_fileno = STDIN_FILENO;
		_eh_stdin_init = 1;
	}
}

int ehnlc_vfprintf(FILE *stream, const char *format, va_list ap)
{
	return eh_vfprintf(stream, format, ap);
}

int ehnlc_fprintf(FILE *stream, const char *format, ...)
{
	va_list ap;
	int rv;
	va_start(ap, format);
	rv = eh_vfprintf(stream, format, ap);
	va_end(ap);
	return rv;
}

int ehnlc_vdprintf(int fd, const char *format, va_list ap)
{
	return eh_vdprintf(fd, format, ap);
}

int ehnlc_dprintf(int fd, const char *format, ...)
{
	va_list ap;
	int rv;
	va_start(ap, format);
	rv = eh_vdprintf(fd, format, ap);
	va_end(ap);
	return rv;
}

int ehnlc_fclose(FILE *stream)
{
	return close(fileno(stream));
}

int ehnlc_fileno(FILE *stream)
{
	if (!stream) {
		return -1;
	}

	_ehnlc_ensure_initialized(stream);

	return stream->_fileno;
}

size_t ehnlc_fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	int fd;
	ssize_t bytes;

	fd = fileno(stream);
	bytes = read(fd, ptr, (size * nmemb));
	if (bytes < 0) {
		return 0;
	}
	return bytes / size;
}

size_t ehnlc_fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	size_t i;
	const char *cptr;
	int fd;

	cptr = (const char *)ptr;	/* pointer math */
	fd = fileno(stream);

	for (i = 0; i < nmemb; ++i) {
		write(fd, cptr, size);
		cptr += size;
	}

	return i;
}

FILE *ehnlc_fopen(const char *path, const char *mode)
{
	int fd;
	int r, w, a, p, flags;
	mode_t _mode;
	FILE *f;

	if (!path) {
		errno = EINVAL;
		return NULL;
	}

	r = w = a = p = flags = _mode = 0;

	if (mode) {
		while (*mode) {
			switch (*mode) {
			case 'r':
				r = 1;
				break;
			case 'w':
				w = 1;
				break;
			case 'a':
				a = 1;
				break;
			case '+':
				p = 1;
				break;
			case 'b':	/* ignore */ ;
			default:;
			};
			++mode;
		}
	}
	if (w && p) {
		flags = flags | O_RDWR | O_CREAT | O_TRUNC;
		_mode = S_IRUSR | S_IWUSR | S_IRGRP;
	} else if (w) {
		flags = flags | O_WRONLY | O_CREAT | O_APPEND;
		_mode = S_IRUSR | S_IWUSR | S_IRGRP;
	} else if (r && p) {
		flags = flags | O_RDWR;
		_mode = S_IRUSR | S_IWUSR | S_IRGRP;
	} else if (r) {
		flags = flags | O_RDONLY;
		_mode = S_IRUSR | S_IRGRP;
	}

	fd = open(path, flags, mode);
	f = malloc(sizeof(FILE));
	if (!f) {
		return NULL;
	}
	f->_fileno = fd;
	f->_flags = flags;
	f->_mode = _mode;

	return f;
}
