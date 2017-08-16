#ifndef _STDLIB_H
#define _STDLIB_H	1

#include <stddef.h>		/* size_t */

#define	EXIT_SUCCESS	0
#define	EXIT_FAILURE	1
void exit(int status);

int atoi(const char *nptr);
long atol(const char *nptr);
long long atoll(const char *nptr);

void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

#endif /* _STDLIB_H */
