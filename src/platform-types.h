#ifndef LINUX_TYPES_H
#define LINUX_TYPES_H

#if defined LINUX_AMD64
#include "linux-amd64/types.h"
#elif defined LINUX_I386
#include "linux-i386/types.h"
#endif

#endif /* LINIX_TYPES_H */
