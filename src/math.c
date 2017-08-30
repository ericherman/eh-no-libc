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
#include "eh-printf/eh-printf-parse-float.h"

int isinf(double x)
{
	uint8_t sign;
	int16_t exponent;
	uint64_t fraction;

	eh_double_to_fields(x, &sign, &exponent, &fraction);

	if (exponent == 0x400 && !fraction) {
		return (sign) ? -1 : 1;
	}

	return 0;
}
