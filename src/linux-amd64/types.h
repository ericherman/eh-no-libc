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

typedef unsigned long uint64_t;
typedef signed long int64_t;

typedef unsigned int uint32_t;
typedef signed int int32_t;

typedef unsigned short uint16_t;
typedef signed short int16_t;

typedef unsigned char uint8_t;
typedef signed char int8_t;

typedef uint64_t size_t;
typedef int64_t ssize_t;

#endif /* TYPES_H */
