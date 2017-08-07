/*
test-strcat.c
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
	char actual[80], *rv;
	const char *expect;
	int failures;

	failures = 0;

	actual[0] = '\0';
	expect = "foo bar";
	rv = strcat(actual, "foo");
	failures += check_ptr(rv, actual);
	rv = strcat(actual, " bar");
	failures += check_ptr(rv, actual);
	failures += check_str(actual, expect);

	rv = strncat(actual, " whiz bang pow", 10);
	failures += check_ptr(rv, actual);
	expect = "foo bar whiz bang";
	failures += check_str(actual, expect);

	return check_status(failures);
}
