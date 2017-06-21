#ifndef EHLIBC_H
#define EHLIBC_H

#include "platform-types.h"

#define stdin 0
#define stdout 1
#define stderr 2

#ifndef EOF
#define EOF (-1)
#endif

size_t strlen(char const *str);

/* writes the string s and a trailing newline to stdout. */
int puts(char const *str);

/* writes the character c, cast to an unsigned char to stdout */
int putchar(int c);

/*
int fputc(int c, FILE *stream);
int fputs(const char *s, FILE *stream);
int putc(int c, FILE *stream);
*/

#if ((defined LINUX_AMD64) || (defined LINUX_I386))
ssize_t write(int fd, void const *data, size_t nbytes);
int stat(const char *pathname, stat_info_s *buf);
#endif

#endif /* EHLIBC_H */
