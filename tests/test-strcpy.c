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

void fill_str(char *str, size_t len, char c)
{
	size_t i, last;

	last = len -1;
	for(i = 0; i<last;++i) {
		str[i] = c;
	}
	str[last] = '\0';
}

/* int main(int argc, char **argv) */
int main(void)
{
	const char *expect;
	char actual[80];
	char *rv;
	int failures;

	failures = 0;
	fill_str(actual, 80, 'X');
	expect = "foo bar";
	rv = strcpy(actual, expect);
	failures += check_str(actual, expect);
	failures += check_ptr(rv, actual);

	fill_str(actual, 80, '\0');
	expect = "foo";
	strncpy(actual, "foo bar", 3);
	failures += check_str(actual, expect);
	failures += check_ptr(rv, actual);

	return check_status(failures);
}
