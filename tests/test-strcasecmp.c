/*
test-strcasecmp.c
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
#include <strings.h>

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
	char s2[20];
	char s1[20];
	int rv1, rv2, rv3;
	int failures;

	failures = 0;

	fill_array(s1, 20, 'X', '\0');
	fill_array(s2, 20, 'X', '\0');
	rv1 = strncasecmp(s1, s2, 20);
	failures += check_int(rv1, 0);
	rv2 = strcasecmp(s1, s2);
	failures += check_int(rv1, rv2);
	rv3 = strncmp(s1, s2, 20);
	failures += check_int(rv1, rv3);

	fill_array(s1, 20, 'X', '\0');
	fill_array(s2, 20, 'x', '\0');
	rv1 = strncasecmp(s1, s2, 20);
	failures += check_int(rv1, 0);
	rv2 = strcasecmp(s1, s2);
	failures += check_int(rv1, rv2);
	rv3 = strncmp(s1, s2, 20);
	failures += check_int(rv3 == 0 ? 0 : 1, 1);

	fill_array(s2 + 10, 20 - 10, 'O', '\0');
	rv1 = strncasecmp(s1, s2, 20);
	failures += check_int(rv1 == 0 ? 0 : 1, 1);
	rv2 = strcasecmp(s1, s2);
	failures += check_int(rv1, rv2);

	rv1 = strncasecmp(s1, s2, 20 - 10);
	failures += check_int(rv1, 0);
	rv2 = strncmp(s1, s2, 20 - 10);
	failures += check_int(rv2 == 0 ? 0 : 1, 1);

	return check_status(failures);
}
