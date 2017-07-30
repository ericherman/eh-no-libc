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

typedef unsigned long long uint64_t;
typedef signed long long int64_t;

typedef unsigned int uint32_t;
typedef signed int int32_t;

typedef unsigned short uint16_t;
typedef signed short int16_t;

typedef unsigned char uint8_t;
typedef signed char int8_t;

typedef uint32_t size_t;
typedef int32_t ssize_t;

typedef ssize_t ptrdiff_t;
typedef ssize_t wchar_t;
typedef uint32_t off_t;
typedef uint64_t off64_t;

typedef struct {
	long long __max_align_ll
	    __attribute__ ((__aligned__(__alignof__(long long))));
	long double __max_align_ld
	    __attribute__ ((__aligned__(__alignof__(long double))));
} max_align_t;

#endif /* TYPES_H */
