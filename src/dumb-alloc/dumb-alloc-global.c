/*
dumb-alloc-global.c: global malloc/free wrappers
Copyright (C) 2012, 2017 Eric Herman <eric@freesa.org>

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

void *dumb_realloc(void *ptr, size_t request_size)
{
	if (!global) {
		_init_global();
	}
	return global->realloc(global, ptr, request_size);
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
