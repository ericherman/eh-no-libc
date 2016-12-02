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

#endif /* EHLIBC_H */
