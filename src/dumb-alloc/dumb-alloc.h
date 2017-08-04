#ifndef DUMB_ALLOC_H
#define DUMB_ALLOC_H

#include <stddef.h>

struct dumb_alloc {
	/* public methods */
	void *(*malloc) (struct dumb_alloc *da, size_t request);
	void (*free) (struct dumb_alloc *da, void *ptr);
	void (*dump) (struct dumb_alloc *da);

	/* private data */
	void *data;
};

/* constructor */
void dumb_alloc_init(struct dumb_alloc *da, char *memory, size_t length,
		     size_t overhead);

#endif /* DUMB_ALLOC_H */
