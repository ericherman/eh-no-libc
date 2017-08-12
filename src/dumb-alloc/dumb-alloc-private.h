/*
dumb-alloc-private.h: dumb-alloc struct declarations
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
#ifndef DUMB_ALLOC_PRIVATE_H
#define DUMB_ALLOC_PRIVATE_H

#include <dumb-alloc.h>

struct dumb_alloc_chunk {
	char *start;
	size_t available_length;
	unsigned char in_use;
	struct dumb_alloc_chunk *prev;
	struct dumb_alloc_chunk *next;
};

struct dumb_alloc_block {
	char *region_start;
	size_t total_length;
	struct dumb_alloc_chunk *first_chunk;
	struct dumb_alloc_block *next_block;
};

#endif /* DUMB_ALLOC_PRIVATE_H */
