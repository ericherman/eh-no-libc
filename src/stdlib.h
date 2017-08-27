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
void exit(int status);

int abs(int j);
long int labs(long int j);
#if _LONG_SAME_AS_LLONG
#define llabs(j) labs(j)
#else
long long int llabs(long long int j);
#endif

int atoi(const char *nptr);
long atol(const char *nptr);
#if _LONG_SAME_AS_LLONG
#define atoll(nptr) atol(nptr)
#else
long long atoll(const char *nptr);
#endif

long int strtol(const char *nptr, char **endptr, int base);
#if _LONG_SAME_AS_LLONG
#define strtoll(nptr, endptr, base) strtol(nptr, endptr, base)
#else
long long int strtoll(const char *nptr, char **endptr, int base);
#endif

unsigned long int strtoul(const char *nptr, char **endptr, int base);
#if _LONG_SAME_AS_LLONG
#define strtoull(nptr, endptr, base) strtoul(nptr, endptr, base)
#else
unsigned long long int strtoull(const char *nptr, char **endptr, int base);
#endif

void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

#endif /* _STDLIB_H */
