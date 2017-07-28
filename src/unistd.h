#ifndef _UNISTD_H
#define _UNISTD_H	1

#include "sys/stat.h"

#if ((defined LINUX_AMD64) || (defined LINUX_I386))
ssize_t write(int fd, void const *data, size_t nbytes);
int stat(const char *pathname, struct stat *buf);
#endif

#endif /* _UNISTD_H */
