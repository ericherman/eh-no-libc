/*
dumb-alloc-global.h: global malloc/free wrapper headers
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

#ifndef DUMB_ALLOC_GLOBAL_H
#define DUMB_ALLOC_GLOBAL_H

#include <dumb-alloc.h>

/* global malloc/free compat fuctions */
void *dumb_malloc(size_t request_size);
void *dumb_realloc(void *ptr, size_t request_size);
void dumb_free(void *ptr);

/* resets the global context and clears all memory */
void dumb_reset(void);

void dumb_alloc_set_global(struct dumb_alloc *da);
struct dumb_alloc *dumb_alloc_get_global(void);

#endif /* DUMB_ALLOC_GLOBAL_H */
