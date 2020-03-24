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

/* http://pubs.opengroup.org/onlinepubs/007908775/xsh/stdio.h.html */
/* http://pubs.opengroup.org/onlinepubs/9699919799/basedefs/stdio.h.html */

#include <stdarg.h>
#include <stddef.h>
#include <unistd.h>
#include <errno.h>

#include <libio.h>
struct _IO_FILE;
typedef struct _IO_FILE FILE;
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;

#define BUFSIZ	8192
#define FILENAME_MAX	4096
#define FOPEN_MAX	16
#define _IOFBF	0
#define _IOLBF	1
#define _IONBF	2
#define L_ctermid	9
#define L_cuserid	20
#define L_tmpnam	20
#define SEEK_CUR	1
#define SEEK_END	2
#define SEEK_SET	0
#define TMP_MAX	238328

#ifndef EOF
#define EOF (-1)
#endif

#define P_tmpdir "/tmp"

extern char *optarg;
extern int opterr;
extern int optind;		/* LEGACY */
extern int optopt;

#define dprintf(fildes, format, ...) ehnlc_dprintf(fildes, format, ##__VA_ARGS__)
int ehnlc_dprintf(int fildes, const char *format, ...);

#define fclose(stream) ehnlc_fclose(stream)
int ehnlc_fclose(FILE *stream);

#define fdopen(f, s) ehnlc_fdopen(f, s)
FILE *ehnlc_fdopen(int f, const char *s);

#define fgetc(stream) ehnlc_fgetc(stream)
int ehnlc_fgetc(FILE *stream);

#define fileno(stream) ehnlc_fileno(stream)
int ehnlc_fileno(FILE *stream);

#define fopen(path, mode) ehnlc_fopen(path, mode)
FILE *ehnlc_fopen(const char *path, const char *mode);

#define fprintf(stream, format, ...) ehnlc_fprintf(stream, format, ##__VA_ARGS__)
int ehnlc_fprintf(FILE *stream, const char *format, ...);

#define fputc(c, stream) ehnlc_fputc(c, stream)
int ehnlc_fputc(int c, FILE *stream);

#define fputs(str, stream) ehnlc_fputs(str, stream)
int ehnlc_fputs(const char *str, FILE *stream);

#define fread(ptr, size, nmemb, stream) ehnlc_fread(ptr, size, nmemb, stream)
size_t ehnlc_fread(void *ptr, size_t size, size_t nmemb, FILE *stream);

#define fwrite(ptr, size, nmemb, stream) ehnlc_fwrite(ptr, size, nmemb, stream)
size_t ehnlc_fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

#define getc(in) ehnlc_fgetc(in)

#define popen(a, b) ehnlc_popen(a, b)
FILE *ehnlc_popen(const char *a, const char *b);

#define printf(format, ...) ehnlc_printf(format, ##__VA_ARGS__)
int ehnlc_printf(const char *format, ...);

#define putc(c, stream) ehnlc_putc(c, stream)
int ehnlc_putc(int c, FILE *stream);

/* writes the character c, cast to an unsigned char to stdout */
#define putchar(c) ehnlc_putchar(c)
int ehnlc_putchar(int c);

/* writes the string s and a trailing newline to stdout. */
#define puts(str) ehnlc_puts(str)
int ehnlc_puts(char const *str);

#define snprintf(buf, len, format, ...) \
	ehnlc_snprintf(buf, len, format, ##__VA_ARGS__)
int ehnlc_snprintf(char *buf, size_t len, const char *format, ...);

#define sprintf(buf, format, ...) ehnlc_sprintf(buf, format, ##__VA_ARGS__)
int ehnlc_sprintf(char *buf, const char *format, ...);

#define vfprintf(stream, format, ap) ehnlc_vfprintf(stream, format, ap)
int ehnlc_vfprintf(FILE *stream, const char *format, va_list ap);

#define vprintf(format, ap) ehnlc_vprintf(format, ap)
int ehnlc_vprintf(const char *format, va_list ap);

#define vdprintf(fildes, format, ap) ehnlc_vdprintf(fildes, format, ap)
int ehnlc_vdprintf(int fildes, const char *format, va_list ap);

#define vsnprintf(buf, len, format, ap) ehnlc_vsnprintf(buf, len, format, ap)
int ehnlc_vsnprintf(char *buf, size_t len, const char *format, va_list ap);

#define vsprintf(buf, format, ap) ehnlc_vsprintf(buf, format, ap)
int ehnlc_vsprintf(char *buf, const char *format, va_list ap);

#endif /* _STDIO_H */
