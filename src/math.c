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
	switch (n) {
	case 0:
		return 1ULL;
	case 1:
		return 1ULL;
	case 2:
		return 2ULL;
	case 3:
		return 2ULL * 3;
	case 4:
		return 2ULL * 3 * 4;
	case 5:
		return 2ULL * 3 * 4 * 5;
	case 6:
		return 2ULL * 3 * 4 * 5 * 6;
	case 7:
		return 2ULL * 3 * 4 * 5 * 6 * 7;
	case 8:
		return 2ULL * 3 * 4 * 5 * 6 * 7 * 8;
	case 9:
		return 2ULL * 3 * 4 * 5 * 6 * 7 * 8 * 9;
	case 10:
		return 2ULL * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10;
	case 11:
		return 2ULL * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11;
	case 12:
		return 2ULL * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12;
	case 13:
		return 2ULL * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13;
	case 14:
		return 2ULL * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 *
		    14;
	case 15:
		return 2ULL * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 *
		    14 * 15;
	case 16:
		return 2ULL * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 *
		    14 * 15 * 16;
	case 17:
		return 2ULL * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 *
		    14 * 15 * 16 * 17;
	case 18:
		return 2ULL * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 *
		    14 * 15 * 16 * 17 * 18;
	case 19:
		return 2ULL * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 *
		    14 * 15 * 16 * 17 * 18 * 19;
	case 20:
		return 2ULL * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 *
		    14 * 15 * 16 * 17 * 18 * 19 * 20;
	default:
		errno = EINVAL;
		return 0;
	}
}
