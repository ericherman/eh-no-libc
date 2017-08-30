/*
test-isinf.c
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
#include "echeck.h"
#include <math.h>

int main(void)
{
	int failures;
	union f_u32_u {
		uint32_t u32;
		float f32;
	} fu;

	failures = check_int(isinf(1.0), 0);
	failures = check_int(isnan(1.0), 0);

	failures = check_int(isinf(2.0 / 0), 1);
	failures = check_int(isnan(2.0 / 0), 0);

	failures = check_int(isinf(-2.0 / 0), -1);
	failures = check_int(isnan(-2.0 / 0), 0);

	fu.u32 = 0x7f800001;	/* NaN */

	failures = check_int(isinf(fu.f32), 0);
	failures = check_int(isnan(fu.f32), 1);

	return check_status(failures);
}
