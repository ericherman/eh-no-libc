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

void clearerr(FILE *);
char *ctermid(char *);
char *cuserid(char *);		/* LEGACY */
int dprintf(int fildes, const char *format, ...);
int fclose(FILE *stream);
FILE *fdopen(int, const char *);
int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
int fgetc(FILE *stream);
int fgetpos(FILE *, fpos_t *);
char *fgets(char *, int, FILE *);
int fileno(FILE *stream);
void flockfile(FILE *);
FILE *fopen(const char *path, const char *mode);
int fprintf(FILE *stream, const char *format, ...);
int fputc(int c, FILE *stream);
int fputs(const char *str, FILE *stream);
size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
FILE *freopen(const char *, const char *, FILE *);
int fscanf(FILE *, const char *, ...);
int fseek(FILE *, long int, int);
int fseeko(FILE *, off_t, int);
int fsetpos(FILE *, const fpos_t *);
long int ftell(FILE *);
off_t ftello(FILE *);
int ftrylockfile(FILE *);
void funlockfile(FILE *);
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
int getc(FILE *);
int getchar(void);
int getc_unlocked(FILE *);
int getchar_unlocked(void);
int getopt(int, char *const[], const char);	/* (LEGACY) */
char *gets(char *);
int getw(FILE *);
int pclose(FILE *);
void perror(const char *);
FILE *popen(const char *, const char *);
int printf(const char *format, ...);
int putc(int c, FILE *stream);
/* writes the character c, cast to an unsigned char to stdout */
int putchar(int c);
int putc_unlocked(int, FILE *);
int putchar_unlocked(int);
/* writes the string s and a trailing newline to stdout. */
int puts(char const *str);
int putw(int, FILE *);
int remove(const char *);
int rename(const char *, const char *);
void rewind(FILE *);
int scanf(const char *, ...);
void setbuf(FILE *, char *);
int setvbuf(FILE *, char *, int, size_t);
int snprintf(char *buf, size_t len, const char *format, ...);
int sprintf(char *, const char *, ...);
int sscanf(const char *, const char *, ...);
char *tempnam(const char *, const char *);
FILE *tmpfile(void);
char *tmpnam(char *);
int ungetc(int, FILE *);
int vfprintf(FILE *stream, const char *format, va_list ap);
int vprintf(const char *format, va_list ap);
int vdprintf(int fildes, const char *format, va_list ap);
int vsnprintf(char *buf, size_t len, const char *format, va_list ap);
int vsprintf(char *, const char *, va_list);

#endif /* _STDIO_H */
