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
#ifndef	_FCNTL_H
#define	_FCNTL_H	1

#include <stdint.h>
#include <linux/fcntl.h>

#ifndef O_TMPFILE
#ifndef __O_TMPFILE
#define __O_TMPFILE 020000000
#endif
#define O_TMPFILE (__O_TMPFILE | O_DIRECTORY)
#endif
#ifndef O_TMPFILE_MASK
#define O_TMPFILE_MASK (__O_TMPFILE | O_DIRECTORY | O_CREAT)
#endif

/*
int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
*/
extern int open(const char *pathname, int flags, ...);

#endif /* fcntl.h  */
