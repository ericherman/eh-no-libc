#ifndef EHLIBC_H
#define EHLIBC_H

#include "platform-types.h"

#define stdin 0
#define stdout 1
#define stderr 2

#ifndef EOF
#define EOF (-1)
#endif

size_t strlen(char const *str);

int puts(char const* str);

#if ((defined LINUX_AMD64) || (defined LINUX_I386))
ssize_t write(int fd, void const *data, size_t nbytes);
int stat(const char *pathname, stat_info *buf);
#endif

#endif /* EHLIBC_H */
