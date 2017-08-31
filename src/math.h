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
#ifndef _MATH_H
#define _MATH_H	1

enum {
	FP_NAN,			/* Not a Number */
	FP_INFINITE,		/* Infinity (either positive or negative) */
	FP_ZERO,		/* Zero */
	FP_SUBNORMAL,		/* too small for normalized representation */
	FP_NORMAL		/* none of the above, must be normal */
};

int _fpclassifyd(double d);
int _isinfd(double d);

#define fpclassify(x)	_fpclassifyd((double)(x))

#define isinf(x)	_isinfd((double)(x))

#define isnan(x)	(fpclassify(x) == FP_NAN)

#define isnormal(x)	(fpclassify(x) == FP_NORMAL)

#define isfinite(x)	(fpclassify(x) != FP_NAN && \
			 fpclassify(x) != FP_INFINITE)

#endif /* _MATH_H */
