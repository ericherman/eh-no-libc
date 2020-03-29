/*
test-qsort.c
Copyright (C) 2019, 2020 Eric Herman

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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "echeck.h"

int _test_qsort_str_comparer(const void *a, const void *b)
{
	const char **ia = (const char **)a;
	const char **ib = (const char **)b;
	return strcmp(*ia, *ib);
}

int test_qsort_strings(const char **in_str, const char **expect, size_t len)
{
	int sorted;
	size_t i;

	qsort(in_str, len, sizeof(const char *), _test_qsort_str_comparer);

	sorted = 1;
	for (i = 0; i < len && sorted; ++i) {
		if (strcmp(expect[i], in_str[i])) {
			sorted = 0;
		}
	}
	if (!sorted) {
		for (i = 0; i < len; ++i) {
			fprintf(stderr, "expect[%u]: '%s', in_str[%u]: '%s'\n",
				(unsigned)i, expect[i], (unsigned)i, in_str[i]);
		}
	}

	return sorted ? 0 : 1;
}

int test_qsort_strings_reversed(void)
{
	const char *expect[] = { "AA", "BB", "CC", "DD", "EE" };
	const char *in_str[] = { "EE", "DD", "CC", "BB", "AA" };
	return test_qsort_strings(in_str, expect, 5);
}

int test_qsort_strings_shuffled(void)
{
	const char *expect[] = { "AA", "BB", "CC", "DD", "EE" };
	const char *in_str[] = { "BB", "EE", "AA", "DD", "CC" };
	return test_qsort_strings(in_str, expect, 5);
}

int test_qsort_strings_presorted(void)
{
	const char *expect[] = { "AA", "BB", "CC", "DD", "EE" };
	const char *in_str[] = { "AA", "BB", "CC", "DD", "EE" };
	return test_qsort_strings(in_str, expect, 5);
}

int main(void)
{
	int failures;

	failures = 0;

	failures += test_qsort_strings_presorted();
	failures += test_qsort_strings_shuffled();
	failures += test_qsort_strings_reversed();

	return check_status(failures);
}
