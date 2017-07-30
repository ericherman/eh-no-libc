#ifndef DUMB_OS_ALLOC_H
#define DUMB_OS_ALLOC_H

#include <stddef.h>

char *dumb_os_mmap(size_t bytes_length);
int dumb_os_munmap(void *addr, size_t bytes_length);

size_t dumb_os_page_size();
size_t dumb_os_mem_limit();

#endif /* DUMB_OS_ALLOC_H */
