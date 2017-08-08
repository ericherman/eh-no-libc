/*
test-strspn.c
Copyright (C) 2016 Eric Herman

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
#include <stdio.h>
#include <string.h>

/* int main(int argc, char **argv) */
int main(void)
{
	int expect, rv, failures;
	const char *str = "321 Ave. G\nSnohomish, WA 98290\nUSA";
	const char *accept = "0123456789";
	const char *reject = "abcdefghijklmnopqrstuvwxyz";
	const char *none = "XYZ";

	failures = 0;

	expect = 0;
	rv = strspn(NULL, accept);
	failures += check_int(rv, expect);

	expect = 0;
	rv = strspn(str, NULL);
	failures += check_int(rv, expect);

	expect = 0;
	rv = strspn(str, none);
	failures += check_int(rv, expect);

	expect = strlen(str);
	rv = strspn(str, str);
	failures += check_int(rv, expect);

	expect = 0;
	rv = strcspn(NULL, reject);
	failures += check_int(rv, expect);

	expect = strlen(str);
	rv = strcspn(str, NULL);
	failures += check_int(rv, expect);

	expect = 0;
	rv = strcspn(str, str);
	failures += check_int(rv, expect);

	expect = 5;
	rv = strcspn(str, reject);
	failures += check_int(rv, expect);

	expect = strlen(str);
	rv = strcspn(str, none);
	failures += check_int(rv, expect);

	return check_status(failures);
}
