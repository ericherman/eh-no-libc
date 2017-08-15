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
#ifndef _ERRNO_H
#define _ERRNO_H	1

#include <stdint.h>

extern int errno;
extern char *errstrs[];
extern const size_t _eh_unknown_err;

/*
#include <stdio.h>
#include <errno.h>
#include <string.h>
int main(void)
{
	printf("ENOMEM: %d, strerror(ENOMEM):%s\n", ENOMEM, strerror(ENOMEM));
	return 0;
}
*/
#define ENOMEM	12
#define EINVAL	22

#endif /* _ERRNO_H */
