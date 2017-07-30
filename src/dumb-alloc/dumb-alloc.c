#include <dumb-alloc-private.h>
#include <dumb-os-alloc.h>
#include <dumb-printf-defines.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static void *_da_alloc(struct dumb_alloc *da, size_t request);
static void _da_free(struct dumb_alloc *da, void *ptr);
static void _dump_chunk(struct dumb_alloc_chunk *chunk);
static void _dump_block(struct dumb_alloc_block *block);
static void _dump(struct dumb_alloc *da);

static void _init_chunk(struct dumb_alloc_chunk *chunk, size_t available_length)
{
	chunk->start = ((char *)chunk) + sizeof(struct dumb_alloc_chunk);
	chunk->available_length =
	    available_length - sizeof(struct dumb_alloc_chunk);
	chunk->in_use = 0;
	chunk->prev = (struct dumb_alloc_chunk *)NULL;
	chunk->next = (struct dumb_alloc_chunk *)NULL;
}

static void _init_block(char *memory, size_t region_size,
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
}

void dumb_alloc_init(struct dumb_alloc *da, char *memory, size_t length,
		     size_t overhead)
{
	da->malloc = _da_alloc;
	da->free = _da_free;
	da->dump = _dump;
	da->data = (memory + overhead);
	_init_block(memory, length, overhead);
}

static void _split_chunk(struct dumb_alloc_chunk *from, size_t request)
{
	size_t remaining_available_length;
	if ((request + sizeof(struct dumb_alloc_chunk)) >
	    from->available_length) {
		return;
	}

	remaining_available_length = from->available_length - request;

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

	if (!da) {
		return NULL;
	}
	block = (struct dumb_alloc_block *)da->data;
	while (block != NULL) {
		for (chunk = block->first_chunk; chunk != NULL;
		     chunk = chunk->next) {
			if (chunk->in_use == 0) {
				if (chunk->available_length >= request) {
					_split_chunk(chunk, request);
					chunk->in_use = 1;
					return chunk->start;
				}
			}
		}
		block = block->next_block;
	}

	last_block = (struct dumb_alloc_block *)da->data;
	total_mem = last_block->total_length;
	while (last_block->next_block != NULL) {
		last_block = last_block->next_block;
		total_mem += last_block->total_length;
	}

	min_needed =
	    request + sizeof(struct dumb_alloc_block) +
	    sizeof(struct dumb_alloc_chunk);
	if (min_needed + total_mem > dumb_os_mem_limit()) {
		errno = ENOMEM;
		return NULL;
	}
	needed = min_needed + (2 * last_block->total_length);

	requested = dumb_os_page_size() * (1 + (needed / dumb_os_page_size()));
	if (requested + total_mem > dumb_os_mem_limit()) {
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
	block = (struct dumb_alloc_block *)memory;
	_init_block(memory, requested, 0);
	last_block->next_block = block;
	chunk = block->first_chunk;
	_split_chunk(chunk, request);
	chunk->in_use = 1;
	return chunk->start;
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

	block = (struct dumb_alloc_block *)da->data;
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
	block = (struct dumb_alloc_block *)da->data;
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
	printf("chunk %p ( " FMT_SIZE_T " )\n", (void *)chunk,
	       (CAST_SIZE_T) ((void *)chunk));
	if (!chunk) {
		return;
	}
	printf("\tstart: %p ( " FMT_SIZE_T " )\n", (void *)chunk->start,
	       (CAST_SIZE_T) ((void *)chunk->start));
	printf("\tavailable_length: " FMT_SIZE_T "\n",
	       (CAST_SIZE_T) chunk->available_length);
	printf("\tin_use: %d\n", chunk->in_use);
	printf("\tprev: %p ( " FMT_SIZE_T " )\n", (void *)chunk->prev,
	       (CAST_SIZE_T) ((void *)chunk->prev));
	printf("\tnext: %p ( " FMT_SIZE_T " )\n", (void *)chunk->next,
	       (CAST_SIZE_T) ((void *)chunk->next));
	if (chunk->next) {
		_dump_chunk(chunk->next);
	}
}

static void _dump_block(struct dumb_alloc_block *block)
{
	printf("block %p ( " FMT_SIZE_T " )\n", (void *)block,
	       (CAST_SIZE_T) ((void *)block));
	if (!block) {
		return;
	}
	printf("\tregion_start: %p ( " FMT_SIZE_T " )\n",
	       (void *)block->region_start,
	       (CAST_SIZE_T) ((void *)block->region_start));
	printf("\ttotal_length: " FMT_SIZE_T "\n",
	       (CAST_SIZE_T) block->total_length);
	printf("\tfirst_chunk: %p ( " FMT_SIZE_T " )\n",
	       (void *)block->first_chunk,
	       (CAST_SIZE_T) ((void *)block->first_chunk));
	if (block->first_chunk) {
		_dump_chunk(block->first_chunk);
	}
	printf("\tnext_block: %p ( " FMT_SIZE_T " )\n",
	       (void *)block->next_block,
	       (CAST_SIZE_T) ((void *)block->next_block));
	if (block->next_block) {
		_dump_block(block->next_block);
	}
}

static void _dump(struct dumb_alloc *da)
{
	printf("sizeof(struct dumb_alloc): " FMT_SIZEOF "\n",
	       sizeof(struct dumb_alloc));
	printf("sizeof(struct dumb_alloc_block): " FMT_SIZEOF "\n",
	       sizeof(struct dumb_alloc_block));
	printf("sizeof(struct dumb_alloc_chunk): " FMT_SIZEOF "\n",
	       sizeof(struct dumb_alloc_chunk));

	printf("context %p ( " FMT_SIZE_T " )\n", (void *)da,
	       (CAST_SIZE_T) ((void *)da));
	if (!da) {
		return;
	}
	printf("\tblock: %p ( " FMT_SIZE_T " )\n", da->data,
	       (CAST_SIZE_T) da->data);
	if (da->data) {
		_dump_block((struct dumb_alloc_block *)da->data);
	}
}
