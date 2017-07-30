#ifndef DUMB_ALLOC_GLOBAL_H
#define DUMB_ALLOC_GLOBAL_H

#include <dumb-alloc.h>

/* global malloc/free compat fuctions */
void *dumb_malloc(size_t request_size);
void dumb_free(void *ptr);

/* resets the global context and clears all memory */
void dumb_reset();

void dumb_alloc_set_global(struct dumb_alloc *da);
struct dumb_alloc *dumb_alloc_get_global();

#endif /* DUMB_ALLOC_GLOBAL_H */
