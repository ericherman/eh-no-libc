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
#ifndef _STDLIB_H
#define _STDLIB_H	1

#include <stddef.h>		/* size_t */

#define	EXIT_SUCCESS	0
#define	EXIT_FAILURE	1
#define exit(status) ehnlc_exit(status)
void ehnlc_exit(int status);

#define abs(j) ehnlc_abs(j)
int ehnlc_abs(int j);

#define labs(j) ehnlc_labs(j)
long int ehnlc_labs(long int j);
#if _LONG_SAME_AS_LLONG
#define llabs(j) ehnlc_labs(j)
#else
#define llabs(j) ehnlc_llabs(j)
long long int ehnlc_llabs(long long int j);
#endif

#define atoi(nptr) ehnlc_atoi(nptr)
int ehnlc_atoi(const char *nptr);

#define atol(nptr) ehnlc_atol(nptr)
long ehnlc_atol(const char *nptr);

#if _LONG_SAME_AS_LLONG
#define atoll(nptr) ehnlc_atol(nptr)
#else
#define atoll(nptr) ehnlc_atoll(nptr)
long long ehnlc_atoll(const char *nptr);
#endif

#define strtol(nptr, endptr, base) ehnlc_strtol(nptr, endptr, base)
long int ehnlc_strtol(const char *nptr, char **endptr, int base);
#if _LONG_SAME_AS_LLONG
#define strtoll(nptr, endptr, base) ehnlc_strtol(nptr, endptr, base)
#else
#define strtoll(nptr, endptr, base) ehnlc_strtoll(nptr, endptr, base)
long long int ehnlc_strtoll(const char *nptr, char **endptr, int base);
#endif

#define strtoul(nptr, endptr, base) ehnlc_strtoul(nptr, endptr, base)
unsigned long int ehnlc_strtoul(const char *nptr, char **endptr, int base);
#if _LONG_SAME_AS_LLONG
#define strtoull(nptr, endptr, base) ehnlc_strtoul(nptr, endptr, base)
#else
#define strtoull(nptr, endptr, base) ehnlc_strtoull(nptr, endptr, base)
unsigned long long int ehnlc_strtoull(const char *nptr, char **endptr,
				      int base);
#endif

#define malloc(size) dumb_malloc(size)
void *dumb_malloc(size_t size);

#define calloc(nmemb, size) ehnlc_calloc(nmemb, size)
void *ehnlc_calloc(size_t nmemb, size_t size);

#define free(ptr) dumb_free(ptr)
void dumb_free(void *ptr);

#define realloc(ptr, size) realloc(ptr, size)
void *dumb_realloc(void *ptr, size_t size);

#endif /* _STDLIB_H */
