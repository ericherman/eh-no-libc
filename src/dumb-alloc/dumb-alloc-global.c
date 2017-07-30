#include <dumb-alloc-private.h>	/* global->data->total_length */
#include <dumb-alloc.h>
#include <dumb-os-alloc.h>

struct dumb_alloc *global = (struct dumb_alloc *)NULL;

void dumb_alloc_set_global(struct dumb_alloc *da)
{
	global = da;
}

struct dumb_alloc *dumb_alloc_get_global()
{
	return global;
}

void _init_global()
{
	char *memory;
	size_t length;
	size_t overhead;

	memory = dumb_os_mmap(dumb_os_page_size());
	length = dumb_os_page_size();
	overhead = sizeof(struct dumb_alloc);
	global = (struct dumb_alloc *)memory;
	dumb_alloc_init(global, memory, length, overhead);
}

void *dumb_malloc(size_t request_size)
{
	if (!global) {
		_init_global();
	}
	return global->malloc(global, request_size);
}

void dumb_free(void *ptr)
{
	if (!global) {
		/*
		   printf("NO GLOBAL CONTEXT! global: %p\n",
		   (void *)global);
		 */
		return;
	}
	global->free(global, ptr);
}

void dumb_reset()
{
	struct dumb_alloc_block *block;

	if (global) {
		block = (struct dumb_alloc_block *)global->data;
		dumb_os_munmap(global, block->total_length);
	}
	global = (struct dumb_alloc *)NULL;
}
