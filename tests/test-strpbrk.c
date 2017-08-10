/*
test-strpbrk.c
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
#include <stdio.h>
#include <string.h>

/* int main(int argc, char **argv) */
int main(void)
{
	int failures;
	char *str = "321 Ave. G\nSnohomish, WA 98290\nUSA";
	char *accept = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *none = "XYZ";
	char *rv, *expect;

	failures = 0;

	expect = str + 4;
	rv = strpbrk(str, accept);
	failures += check_ptr(rv, expect);

	expect = str;
	rv = strpbrk(str, str);
	failures += check_ptr(rv, expect);

	expect = NULL;
	rv = strpbrk(str, none);
	failures += check_ptr(rv, expect);

	expect = NULL;
	rv = strpbrk(NULL, accept);
	failures += check_ptr(rv, NULL);

	expect = NULL;
	rv = strpbrk(str, NULL);
	failures += check_ptr(NULL, expect);

	return check_status(failures);
}
