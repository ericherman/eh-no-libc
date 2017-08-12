/*
dumb-alloc.h: dumb-alloc public structs and functions declarations
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
#ifndef DUMB_ALLOC_H
#define DUMB_ALLOC_H

#include <stddef.h>

struct dumb_alloc {
	/* public methods */
	void *(*malloc) (struct dumb_alloc *da, size_t request);
	void *(*realloc) (struct dumb_alloc *da, void *ptr, size_t request);
	void (*free) (struct dumb_alloc *da, void *ptr);
	void (*dump) (struct dumb_alloc *da);

	/* private data */
	void *data;
};

/* constructor */
void dumb_alloc_init(struct dumb_alloc *da, char *memory, size_t length,
		     size_t overhead);

#endif /* DUMB_ALLOC_H */
