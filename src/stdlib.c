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
