#include <dumb-os-alloc.h>
#include <dumb-printf-defines.h>
#include <sys/mman.h>
#include <stdio.h>
#include <unistd.h>

#ifndef MAP_ANONYMOUS
#ifdef MAP_ANON
#define MAP_ANONYMOUS MAP_ANON
#else
/* from: /usr/include/asm-generic/mman-common.h */
#define MAP_ANONYMOUS 0x20	/* don't use a file */
#endif
#endif

char *dumb_os_mmap(size_t length)
{
	void *memory, *addr;
	int prot, flags, fd, offset;

	addr = NULL;
	prot = PROT_READ | PROT_WRITE;
	flags = MAP_PRIVATE | MAP_ANONYMOUS;
	fd = -1;
	offset = 0;

	/*
	   fprintf(stderr, "requesting " FMT_SIZE_T " bytes.\n", length);
	 */
#ifdef DEBUG
	fprintf(stderr, "addr: NULL\n");
	fprintf(stderr, "len: %lu\n", (unsigned long)length);
	fprintf(stderr, "prot: %x\n", prot);
	fprintf(stderr, "flags: %x\n", flags);
	fprintf(stderr, "fd: %d\n", fd);
	fprintf(stderr, "offset: %d\n", offset);
#endif

	memory = mmap(addr, length, prot, flags, fd, offset);

	if (!memory) {
		fprintf(stderr, "Could not allocate " FMT_SIZE_T " bytes\n",
			(CAST_SIZE_T) length);
	}

	return (char *)memory;
}

int dumb_os_munmap(void *addr, size_t bytes_length)
{
	return munmap(addr, bytes_length);
}

size_t dumb_os_page_size()
{
	return (size_t)sysconf(_SC_PAGESIZE);
}

size_t dumb_os_mem_limit()
{
	return 1073741824;
}
