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
#ifndef TYPES_H
#define TYPES_H

#define NULL ((void *)0)
#define _LONG_SAME_AS_LLONG 1

typedef unsigned long int uint64_t;
typedef unsigned long int uint_least64_t;
typedef unsigned long int uint_fast64_t;

typedef signed long int int64_t;
typedef signed long int int_least64_t;
typedef signed long int int_fast64_t;

typedef unsigned int uint32_t;
typedef unsigned int uint_least32_t;
typedef unsigned long int uint_fast32_t;

typedef signed int int32_t;
typedef signed int int_least32_t;
typedef signed long int int_fast32_t;

typedef unsigned short uint16_t;
typedef unsigned short int uint_least16_t;
typedef unsigned long int uint_fast16_t;

typedef signed short int16_t;
typedef signed short int int_least16_t;
typedef signed long int int_fast16_t;

typedef unsigned char uint8_t;
typedef unsigned char uint_least8_t;
typedef unsigned char uint_fast8_t;

typedef signed char int8_t;
typedef signed char int_least8_t;
typedef signed char int_fast8_t;

typedef int64_t intmax_t;
typedef uint64_t uintmax_t;

typedef uint64_t size_t;
typedef int64_t ssize_t;
typedef ssize_t intptr_t;
typedef size_t uintptr_t;
typedef ssize_t ptrdiff_t;

typedef uint32_t wchar_t;
typedef uint32_t wint_t;
typedef uint32_t wctype_t;

typedef uint32_t off_t;
typedef uint64_t off64_t;
typedef uint32_t mode_t;

typedef struct {
	uint64_t quot;
	uint64_t rem;
} imaxdiv_t;

#if 0
typedef struct {
	long long __max_align_ll
	    __attribute__((__aligned__(__alignof__(long long))));
	long double __max_align_ld
	    __attribute__((__aligned__(__alignof__(long double))));
} max_align_t;
#endif

#endif /* TYPES_H */
