#ifndef _STDINT_H
#define _STDINT_H	1

#if defined LINUX_AMD64
#include "linux-amd64/types.h"
#elif defined LINUX_I386
#include "linux-i386/types.h"
#endif

#endif
