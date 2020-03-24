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

#include <math.h>
#include <errno.h>
#include "efloat/efloat.h"

int ehnlc_isinfd(double x)
{
	struct efloat_double_fields fields;
	enum efloat_class classfied;

	classfied = efloat_double_to_fields(x, &fields);

	if (classfied == ef_inf) {
		return (fields.sign) ? -1 : 1;
	}

	return 0;
}

int ehnlc_fpclassifyd(double x)
{
	return (sizeof(double) == sizeof(efloat32))
	    ? efloat32_classify(x)
	    : efloat64_classify(x);
}

double ehnlc_fabs(double x)
{
	return x >= 0.0 ? x : -x;
}

/*
   Max uint64_t: 18,446,744,073,709,551,615
   While,  21! = 51,090,942,171,709,440,000
   Thus we limit to 20
*/
uint64_t ehnlc_factorial(uint64_t n)
{
	uint64_t limit, result;

	limit = 20;
	if (n > limit) {
		errno = EINVAL;
		return 0;
	}

	result = n;

	if (n < 2) {
		return 1;
	}

	do {
		result *= --n;
	} while (n > 1);

	return result;
}
