/*
test-memccpy.c
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

void fill_array(void *dest, size_t len, unsigned char c, unsigned char term)
{
	size_t i;
	unsigned char *chars;

	chars = (unsigned char *)dest;
	for (i = 0; i < (len - 1); ++i) {
		chars[i] = c;
	}
	chars[len - 1] = term;
}

/* int main(int argc, char **argv) */
int main(void)
{
	char expect[40];
	char actual[40];
	char *rv;
	size_t i;
	int failures;

	failures = 0;

	fill_array(actual, 40, 'X', '\0');
	fill_array(expect, 40, 'O', '\0');
	strcpy(expect, "foo bar");
	rv = memccpy(actual, expect, '\0', 40);
	failures += check_str(actual, expect);
	failures += check_ptr(rv, actual + strlen(expect) + 1);

	fill_array(actual, 40, 'X', '\0');
	fill_array(expect, 40, 'O', '\0');
	rv = memccpy(actual, expect, '\0', 20);
	for (i = 20; i < (40 - 1); ++i) {
		expect[i] = 'X';
	}
	failures += check_str(actual, expect);
	failures += check_ptr(rv, NULL);

	return check_status(failures);
}
