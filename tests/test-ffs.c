/*
test-ffs.c
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
#include <limits.h>
#include <strings.h>

int check_ffs(void)
{
	size_t i, j, k, len;
	int *vals, failures, d, b, expect;
	char buf[40];

	failures = 0;

	len = sizeof(int) * 10;
	vals = calloc(sizeof(int), len);
	if (!vals) {
		fprintf(stderr, "Can not allocate %lu bytes?\n",
			sizeof(int) * len);
		return 1;
	}

	i = 0;
	vals[i++] = 0;
	vals[i++] = INT_MIN;
	vals[i++] = INT_MAX;

	for (j = 0; j < 3; ++j) {
		for (k = j; (i < len) && (k < ((8 * sizeof(int)) / 4)); k += 4) {
			vals[i] = (vals[i] | (1U << k));
		}
		++i;
	}

	for (i = 0; i < len; ++i) {
		d = vals[i];
		expect = 0;
		if (d != 0) {
			for (i = 0; !expect && i < (8 * sizeof(int)); ++i) {
				if (d & (1U << i)) {
					expect = i + 1;
				}
			}
		}
		b = ffs(d);
		snprintf(buf, 40, "ffs(%d) == %d", d, b);
		check_int_m(b, expect, buf);
	}

	return failures;
}

int check_ffsl(void)
{
	size_t i, j, k, len;
	long *vals, failures, d, b, expect;
	char buf[40];

	failures = 0;

	len = sizeof(long) * 10;
	vals = calloc(sizeof(long), len);
	if (!vals) {
		fprintf(stderr, "Can not allocate %lu bytes?\n",
			sizeof(long) * len);
		return 1;
	}

	i = 0;
	vals[i++] = 0;
	vals[i++] = LONG_MIN;
	vals[i++] = LONG_MAX;

	for (j = 0; j < 3; ++j) {
		for (k = j; (i < len) && (k < ((8 * sizeof(long)) / 4)); k += 4) {
			vals[i] = (vals[i] | (1U << k));
		}
		++i;
	}

	for (i = 0; i < len; ++i) {
		d = vals[i];
		expect = 0;
		if (d != 0) {
			for (i = 0; !expect && i < (8 * sizeof(int)); ++i) {
				if (d & (1U << i)) {
					expect = i + 1;
				}
			}
		}
		b = ffs(d);
		snprintf(buf, 40, "ffs(%ld) == %ld", d, b);
		check_int_m(b, expect, buf);
	}

	return failures;
}

int check_ffsll(void)
{
	size_t i, j, k, len;
	long long *vals, failures, d, b, expect;
	char buf[40];

	failures = 0;

	len = sizeof(long long) * 10;
	vals = calloc(sizeof(long long), len);
	if (!vals) {
		fprintf(stderr, "Can not allocate %lu bytes?\n",
			sizeof(long long) * len);
		return 1;
	}

	i = 0;
	vals[i++] = 0;
	vals[i++] = LLONG_MIN;
	vals[i++] = LLONG_MAX;

	for (j = 0; j < 3; ++j) {
		for (k = j; (i < len) && (k < ((8 * sizeof(long long)) / 4));
		     k += 4) {
			vals[i] = (vals[i] | (1U << k));
		}
		++i;
	}

	for (i = 0; i < len; ++i) {
		d = vals[i];
		expect = 0;
		if (d != 0) {
			for (i = 0; !expect && i < (8 * sizeof(long long)); ++i) {
				if (d & (1U << i)) {
					expect = i + 1;
				}
			}
		}
		b = ffs(d);
		snprintf(buf, 40, "ffsll(%lld) == %lld", d, b);
		check_int_m(b, expect, buf);
	}

	return failures;
}

/* int main(int argc, char **argv) */
int main(void)
{
	int failures;

	failures = 0;

	failures += check_ffs();
	failures += check_ffsl();
	failures += check_ffsll();

	return check_status(failures);
}
