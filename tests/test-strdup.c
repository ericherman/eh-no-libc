/*
test-strcpy.c
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

#ifndef TEST_STRDUPA
#define TEST_STRDUPA 0
#endif

/* int main(int argc, char **argv) */
int main(void)
{
	char *actual;
#if TEST_STRDUPA
	char *actual2;
#endif
	const char *expect;
	int failures;

	failures = 0;

	expect = "foo bar";
	actual = strdup(expect);
	failures += check_str(actual, expect);
	if (actual) {
		free(actual);
	}

	expect = "foo bar";
	actual = strndup(expect, 3);
	expect = "foo";
	failures += check_str(actual, expect);
	if (actual) {
		free(actual);
	}

#if TEST_STRDUPA
	expect = "foo bar";
	actual = strdupa(expect);
	if (!actual) {
		++failures;
	} else {
		failures += check_str(actual, expect);
	}

	expect = "foo bar";
	actual2 = strndupa(expect, 3);
	expect = "foo";
	if (!actual) {
		++failures;
	} else {
		failures += check_str(actual2, expect);
	}
#endif

	return check_status(failures);
}
