#ifndef _STDLIB_H
#define _STDLIB_H	1

#include <stddef.h>		/* size_t */

void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

#endif /* _STDLIB_H */
