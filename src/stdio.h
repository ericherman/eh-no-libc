#ifndef _STDIO_H
#define _STDIO_H	1

#define stdin 0
#define stdout 1
#define stderr 2

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

#endif /* _STDIO_H */
