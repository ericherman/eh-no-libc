#include <stdlib.h>
#include "dumb-alloc-global.h"

void *malloc(size_t size)
{
	return dumb_malloc(size);
}

void free(void *ptr)
{
	dumb_free(ptr);
}

void *calloc(size_t nmemb, size_t size)
{
	size_t i, len;
	unsigned char *chars;

	len = nmemb * size;
	chars = malloc(len);
	if (chars) {
		for (i = 0; i < len; ++i) {
			chars[i] = '\0';
		}
	}
	return chars;
}
