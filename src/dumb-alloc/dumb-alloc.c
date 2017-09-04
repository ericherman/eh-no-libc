/*
dumb-alloc.c: OO memory allocator
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
#include <dumb-alloc-private.h>
#include <dumb-os-alloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

static void *_da_alloc(struct dumb_alloc *da, size_t request);
static void *_da_realloc(struct dumb_alloc *da, void *ptr, size_t request);
static void _da_free(struct dumb_alloc *da, void *ptr);
static void _dump_chunk(struct dumb_alloc_chunk *chunk);
static void _dump_block(struct dumb_alloc_block *block);
static void _dump(struct dumb_alloc *da);
static void _chunk_join_next(struct dumb_alloc_chunk *chunk);

static void _init_chunk(struct dumb_alloc_chunk *chunk, size_t available_length)
{
	chunk->start = ((char *)chunk) + sizeof(struct dumb_alloc_chunk);
	chunk->available_length =
	    available_length - sizeof(struct dumb_alloc_chunk);
	chunk->in_use = 0;
	chunk->prev = (struct dumb_alloc_chunk *)NULL;
	chunk->next = (struct dumb_alloc_chunk *)NULL;
}

static struct dumb_alloc_block *_init_block(char *memory, size_t region_size,
					    size_t initial_overhead)
{
	struct dumb_alloc_block *block;
	size_t block_available_length;

	block = (struct dumb_alloc_block *)(memory + initial_overhead);
	block->region_start = memory;
	block->total_length = region_size;
	block->next_block = (struct dumb_alloc_block *)NULL;

	block->first_chunk =
	    (struct dumb_alloc_chunk *)(((char *)block) +
					sizeof(struct dumb_alloc_block));

	block_available_length =
	    block->total_length - (initial_overhead +
				   sizeof(struct dumb_alloc_block));
	_init_chunk(block->first_chunk, block_available_length);
	return block;
}

void dumb_alloc_init(struct dumb_alloc *da, char *memory, size_t length,
		     size_t overhead)
{
	da->malloc = _da_alloc;
	da->realloc = _da_realloc;
	da->free = _da_free;
	da->dump = _dump;
	da->data = _init_block(memory, length, overhead);
}

static struct dumb_alloc_block *_first_block(struct dumb_alloc *da)
{
	struct dumb_alloc_block *block;

	block = (struct dumb_alloc_block *)da->data;

	return block;
}

static void _split_chunk(struct dumb_alloc_chunk *from, size_t request)
{
	size_t remaining_available_length;

	from->in_use = 1;

	if ((request + sizeof(struct dumb_alloc_chunk)) >=
	    from->available_length) {
		return;
	}

	remaining_available_length = from->available_length - request;
	if (remaining_available_length <= sizeof(struct dumb_alloc_chunk)) {
		return;
	}

	from->available_length = request;
	from->next =
	    (struct dumb_alloc_chunk *)(from->start + from->available_length);

	_init_chunk(from->next, remaining_available_length);
	from->next->prev = from;
}

static void *_da_alloc(struct dumb_alloc *da, size_t request)
{
	char *memory;
	struct dumb_alloc_block *last_block;
	struct dumb_alloc_block *block;
	struct dumb_alloc_chunk *chunk;
	size_t min_needed;
	size_t needed;
	size_t requested;
	size_t total_mem;
	size_t overhead_consumed;

	if (!da) {
		return NULL;
	}
	block = _first_block(da);
	while (block != NULL) {
		for (chunk = block->first_chunk; chunk != NULL;
		     chunk = chunk->next) {
			if (chunk->in_use == 0) {
				if (chunk->available_length >= request) {
					_split_chunk(chunk, request);
					return chunk->start;
				}
			}
		}
		block = block->next_block;
	}

	last_block = _first_block(da);
	total_mem = last_block->total_length;
	while (last_block->next_block != NULL) {
		last_block = last_block->next_block;
		total_mem += last_block->total_length;
	}

	min_needed =
	    request + sizeof(struct dumb_alloc_block) +
	    sizeof(struct dumb_alloc_chunk);
	if (dumb_os_mem_limit()
	    && (min_needed + total_mem > dumb_os_mem_limit())) {
		errno = ENOMEM;
		return NULL;
	}
	needed = min_needed + (2 * last_block->total_length);

	requested = dumb_os_page_size() * (1 + (needed / dumb_os_page_size()));
	if (dumb_os_mem_limit()
	    && (requested + total_mem > dumb_os_mem_limit())) {
		memory = NULL;
	} else {
		memory = dumb_os_mmap(requested);
	}
	if (!memory) {
		requested = min_needed;
		requested =
		    dumb_os_page_size() * (1 +
					   (min_needed / dumb_os_page_size()));
		if (requested + total_mem > dumb_os_mem_limit()) {
			errno = ENOMEM;
			return NULL;
		}
		memory = dumb_os_mmap(requested);
		if (!memory) {
			errno = ENOMEM;
			return NULL;
		}
	}
	overhead_consumed = 0;
	block = _init_block(memory, requested, overhead_consumed);
	last_block->next_block = block;
	chunk = block->first_chunk;
	_split_chunk(chunk, request);
	return chunk->start;
}

/* The  realloc()  function  changes  the  size  of  the memory
 * block pointed to by ptr to size bytes.  The contents will be
 * unchanged in the range from the start of the region up to the
 * minimum of the old and new sizes.  If the new size is larger
 * than the old size, the added memory will not be initialized.
 * If ptr is NULL, then the call is equivalent to malloc(size),
 * for all values of size; if size is equal to zero, and ptr is
 * not NULL, then the call is equivalent to  free(ptr).   Unless
 * ptr is NULL, it must have been returned by an earlier call to
 * malloc(), calloc() or realloc().  If the area pointed to was
 * moved, a free(ptr) is done.  */
static void *_da_realloc(struct dumb_alloc *da, void *ptr, size_t request)
{
	struct dumb_alloc_block *block;
	struct dumb_alloc_chunk *chunk;
	size_t old_size;

	if (!da) {
		return NULL;
	}

	if (!ptr) {
		return _da_alloc(da, request);
	}
	if (request == 0) {
		_da_free(da, ptr);
		return NULL;
	}

	old_size = 0;
	block = _first_block(da);
	while (block != NULL) {
		for (chunk = block->first_chunk; old_size == 0 && chunk != NULL;
		     chunk = chunk->next) {
			if (ptr == chunk->start) {
				old_size = chunk->available_length;
			}
		}
		block = (old_size == 0) ? block->next_block : NULL;
	}

	if (old_size == 0) {
		return NULL;
	}

	if (old_size == request) {
		return chunk->start;
	}

	if (old_size > request) {
		_split_chunk(chunk, request);
		return chunk->start;
	}

	if (chunk->next && chunk->next->in_use == 0) {
		_chunk_join_next(chunk);
		if (chunk->available_length < request) {
			_split_chunk(chunk, request);
			return chunk->start;
		}
		if (chunk->available_length == request) {
			return chunk->start;
		}
	}

	ptr = _da_alloc(da, request);
	memcpy(ptr, chunk->start, old_size);
	_da_free(da, chunk->start);
	return ptr;
}

static void _chunk_join_next(struct dumb_alloc_chunk *chunk)
{
	struct dumb_alloc_chunk *next;
	size_t additional_available_length;

	next = chunk->next;
	if (!next) {
		return;
	}
	if (next->in_use) {
		return;
	}
	chunk->next = next->next;
	additional_available_length =
	    sizeof(struct dumb_alloc_chunk) + next->available_length;
	chunk->available_length += additional_available_length;
}

char _chunks_in_use(struct dumb_alloc_block *block)
{
	struct dumb_alloc_chunk *chunk;

	if (!block) {
		return 0;
	}
	for (chunk = block->first_chunk; chunk != NULL; chunk = chunk->next) {
		if (chunk->in_use) {
			return 1;
		}
	}
	return 0;
}

static void _release_unused_block(struct dumb_alloc *da)
{
	struct dumb_alloc_block *block;
	struct dumb_alloc_block *block_prev;

	block = _first_block(da);
	while (block != NULL) {
		block_prev = block;
		block = block->next_block;
		if (block && !_chunks_in_use(block)) {
			block_prev->next_block = block->next_block;
			dumb_os_munmap(block, block->total_length);
			block = block_prev->next_block;
		}
	}
}

static void _da_free(struct dumb_alloc *da, void *ptr)
{
	struct dumb_alloc_block *block;
	struct dumb_alloc_chunk *chunk;
	size_t i;

	if (!da || !ptr) {
		return;
	}
	block = _first_block(da);
	while (block != NULL) {
		for (chunk = block->first_chunk; chunk != NULL;
		     chunk = chunk->next) {
			if (chunk->start == ptr) {
				chunk->in_use = 0;

				_chunk_join_next(chunk);
				while (chunk->prev && chunk->prev->in_use == 0) {
					chunk = chunk->prev;
					if (chunk->in_use == 0) {
						_chunk_join_next(chunk);
					}
				}
				for (i = 0; i < chunk->available_length; ++i) {
					chunk->start[i] = 0;
				}
				_release_unused_block(da);
				return;
			}
		}
		block = block->next_block;
	}
	/*
	   printf("chunk for %p not found!\n", ptr);
	   da->dump(da);
	 */
	return;
}

static void _dump_chunk(struct dumb_alloc_chunk *chunk)
{
	printf("chunk %p ( %lu )\n", (void *)chunk,
	       (unsigned long)((void *)chunk));
	if (!chunk) {
		return;
	}
	printf("\tstart: %p ( %lu )\n", (void *)chunk->start,
	       (unsigned long)((void *)chunk->start));
	printf("\tavailable_length: %lu\n",
	       (unsigned long)chunk->available_length);
	printf("\tin_use: %d\n", chunk->in_use);
	printf("\tprev: %p ( %lu )\n", (void *)chunk->prev,
	       (unsigned long)((void *)chunk->prev));
	printf("\tnext: %p ( %lu )\n", (void *)chunk->next,
	       (unsigned long)((void *)chunk->next));
	if (chunk->next) {
		_dump_chunk(chunk->next);
	}
}

static void _dump_block(struct dumb_alloc_block *block)
{
	printf("block %p ( %lu )\n", (void *)block,
	       (unsigned long)((void *)block));
	if (!block) {
		return;
	}
	printf("\tregion_start: %p ( %lu )\n",
	       (void *)block->region_start,
	       (unsigned long)((void *)block->region_start));
	printf("\ttotal_length: %lu\n", (unsigned long)block->total_length);
	printf("\tfirst_chunk: %p ( %lu )\n",
	       (void *)block->first_chunk,
	       (unsigned long)((void *)block->first_chunk));
	if (block->first_chunk) {
		_dump_chunk(block->first_chunk);
	}
	printf("\tnext_block: %p ( %lu )\n",
	       (void *)block->next_block,
	       (unsigned long)((void *)block->next_block));
	if (block->next_block) {
		_dump_block(block->next_block);
	}
}

static void _dump(struct dumb_alloc *da)
{
	printf("sizeof(struct dumb_alloc): %lu\n",
	       (unsigned long)sizeof(struct dumb_alloc));
	printf("sizeof(struct dumb_alloc_block): %lu\n",
	       (unsigned long)sizeof(struct dumb_alloc_block));
	printf("sizeof(struct dumb_alloc_chunk): %lu\n",
	       (unsigned long)sizeof(struct dumb_alloc_chunk));

	printf("context %p ( %lu )\n", (void *)da, (unsigned long)((void *)da));
	if (!da) {
		return;
	}
	printf("\tblock: %p ( %lu )\n", da->data, (unsigned long)da->data);
	if (da->data) {
		_dump_block((struct dumb_alloc_block *)da->data);
	}
}
