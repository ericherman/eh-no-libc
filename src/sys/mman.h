#ifndef _SYS_MMAN_H
#define _SYS_MMAN_H	1

#include <stdint.h>

#define PROT_NONE	0x00
#define PROT_READ	0x01
#define PROT_WRITE	0x02
#define PROT_EXEC	0x04

#define MAP_FILE	0x00
#define MAP_SHARED      0x01
#define MAP_PRIVATE     0x02
#define MAP_FIXED	0x10
#define MAP_ANONYMOUS	0x20
#define MAP_ANON	MAP_ANONYMOUS

#define MAP_GROWSDOWN	0x00100
#define MAP_DENYWRITE	0x00800
#define MAP_EXECUTABLE	0x01000
#define MAP_LOCKED	0x02000
#define MAP_NORESERVE	0x04000
#define MAP_POPULATE	0x08000
#define MAP_NONBLOCK	0x10000
#define MAP_STACK	0x20000
#define MAP_HUGETLB	0x40000

#define PROT_GROWSDOWN	0x01000000
#define PROT_GROWSUP	0x02000000

void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
int munmap(void *addr, size_t len);

#endif /* _SYS_MMAN_H */
