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
#ifndef _SYS_TIME_H
#define _SYS_TIME_H	1

#include <stdint.h>

typedef ssize_t syscall_slong_t;
typedef ssize_t time_t;

/*
  http://pubs.opengroup.org/onlinepubs/007908775/xsh/time.h.html
*/
typedef struct {
	time_t sec;
	syscall_slong_t nsec;
} timespec;

#endif /* _SYS_TIME_H */
