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
#ifndef	_ASSERT_H
#define	_ASSERT_H	1

#ifdef	NDEBUG

/*
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-value"
#define assert(expression) ((void *)(0))
#pragma GCC diagnostic pop
*/
#define assert(expression)	/* nothing */

#else

void _assert_fail(const char *func, const char *file, int line,
		  const char *expression_str);

#define assert(expression) \
	( (expression) \
		? ((void *)(0)) \
		: _assert_fail(__func__, __FILE__, __LINE__, #expression) \
	)

#endif /* NDEBUG */

#endif /* _ASSERT_H  */
