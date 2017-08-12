/*
test-memmove.c
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
	unsigned char actual[20];
	unsigned char expect[20];
	char *rv;
	int failures;
	size_t i;

	failures = 0;
	for (i = 0; i < 20; ++i) {
		actual[i] = '\0';
		expect[i] = 'a' + i;
	}
	rv = memmove(actual, expect, 20);
	failures += check_byte_array(actual, 20, expect, 20);
	failures += check_ptr(rv, actual);

	for (i = 2; i < 12; ++i) {
		expect[i] = expect[i + 4];
	}
	rv = memmove(actual + 2, actual + 6, 10);
	failures += check_byte_array(actual, 20, expect, 20);
	failures += check_ptr(rv, actual + 2);

	for (i = 0; i < 20; ++i) {
		expect[i] = 'a' + i;
		actual[i] = 'a' + i;
	}
	for (i = 15; i > 5; --i) {
		expect[i] = expect[i - 4];
	}
	rv = memmove(actual + 6, actual + 2, 10);
	failures += check_byte_array(actual, 20, expect, 20);
	failures += check_ptr(rv, actual + 6);

	return check_status(failures);
}
