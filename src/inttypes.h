/*
eh-no-libc - exploring coding without the standard library
Copyright (C) 2017 Eric Herman

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
#ifndef _INTTYPES_H
#define _INTTYPES_H	1

#include <stdint.h>
#include <stdlib.h>

#if defined LINUX_AMD64
#include "linux-amd64/inttypes.h"
#elif defined LINUX_I386
#include "linux-i386/inttypes.h"
#endif

/* intmax_t imaxabs(intmax_t j); */

/* imaxdiv_t imaxdiv(intmax_t numerator, intmax_t denominator); */

/* intmax_t strtoimax(const char *nptr, char **endptr, int base); */
/* uintmax_t strtoumax(const char *nptr, char **endptr, int base); */

/* intmax_t wcstoimax(const wchar_t *nptr, wchar_t **endptr, int base); */
/* uintmax_t wcstoumax(const wchar_t *nptr, wchar_t **endptr, int base); */

#if _LONG_SAME_AS_LLONG

#define imaxabs(j) labs(j)

#define strtoimax(nptr, endptr, base) strtol(nptr, endptr, base)
#define strtoumax(nptr, endptr, base) strtoul(nptr, endptr, base)

#else /* _LONG_SAME_AS_LLONG */

#define imaxabs(j) llabs(j)

#define strtoimax(nptr, endptr, base) strtoll(nptr, endptr, base)
#define strtoumax(nptr, endptr, base) strtoull(nptr, endptr, base)

#endif /* _LONG_SAME_AS_LLONG */

#endif /* _INTTYPES_H */
