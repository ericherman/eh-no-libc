/*
test-strtol.c
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
#include <stdlib.h>
#include <inttypes.h>

int test_strtol(int test_null)
{
	int failures;
	long l;
	char *str, *end_ptr;
	ssize_t diff;

	failures = 0;

	end_ptr = "wrong";
	str = "-123 foo";
	l = strtol(str, &end_ptr, 10);
	failures += check_long(l, -123L);
	diff = end_ptr - str;
	failures += check_long((long)diff, 4L);

	str = "7FFFFFFF foo";
	l = strtol(str, &end_ptr, 16);
	failures += check_long(l, 0x7FFFFFFFL);

	str = "4badc0de foo";
	l = strtol(str, NULL, 16);
	failures += check_long(l, 0x4badc0deL);

	if (test_null) {
		end_ptr = "wrong";
		str = NULL;
		l = strtol(str, &end_ptr, 10);
		failures += check_long(l, 0);
	}

	return failures;
}

int test_strtoll(int test_null)
{
	int failures;
	long long ll;
	char *str, *end_ptr;
	ssize_t diff;

	failures = 0;

	end_ptr = "wrong";
	str = "-123 foo";
	ll = strtoll(str, &end_ptr, 10);
	failures += check_long(ll, -123L);
	diff = end_ptr - str;
	failures += check_long((long long)diff, 4);

	str = "7FFFFFFF foo";
	ll = strtoll(str, NULL, 16);
	failures += check_long(ll, 0x7FFFFFFFLL);

	str = "4badc0de foo";
	ll = strtoll(str, NULL, 16);
	failures += check_long(ll, 0x4badc0deLL);

	if (test_null) {
		end_ptr = "wrong";
		str = NULL;
		ll = strtoll(str, &end_ptr, 10);
		failures += check_long(ll, 0);
	}

	return failures;
}

int test_strtoul(int test_null)
{
	int failures;
	unsigned long lu;
	char *str, *end_ptr;
	ssize_t diff;

	failures = 0;

	end_ptr = "wrong";
	str = "123 foo";
	lu = strtoul(str, &end_ptr, 10);
	failures += check_unsigned_long(lu, 123UL);
	diff = end_ptr - str;
	failures += check_long((long)diff, 3L);

	str = "7FFFFFFF foo";
	lu = strtoul(str, NULL, 16);
	failures += check_unsigned_long(lu, 0x7FFFFFFFUL);

	str = "4badc0de foo";
	lu = strtoul(str, NULL, 16);
	failures += check_unsigned_long(lu, 0x4badc0deUL);

	if (test_null) {
		end_ptr = "wrong";
		str = NULL;
		lu = strtoul(str, &end_ptr, 10);
		failures += check_long(lu, 0UL);
	}

	return failures;
}

int test_strtoull(int test_null)
{
	int failures;
	unsigned long lu;
	char *str, *end_ptr;
	ssize_t diff;

	failures = 0;

	end_ptr = "wrong";
	str = "123 foo";
	lu = strtoull(str, &end_ptr, 10);
	failures += check_unsigned_long(lu, 123ULL);
	diff = end_ptr - str;
	failures += check_long((long)diff, 3L);

	str = "7FFFFFFF foo";
	lu = strtoull(str, NULL, 16);
	failures += check_unsigned_long(lu, 0x7FFFFFFFULL);

	str = "4badc0de foo";
	lu = strtoull(str, NULL, 16);
	failures += check_unsigned_long(lu, 0x4badc0deULL);

	if (test_null) {
		end_ptr = "wrong";
		str = NULL;
		lu = strtoull(str, &end_ptr, 10);
		failures += check_unsigned_long(lu, 0UL);
	}

	return failures;
}

int test_strtoimax(int test_null)
{
	int failures;
	intmax_t imax;
	char *str, *end_ptr;
	ssize_t diff;

	failures = 0;

	end_ptr = "wrong";
	str = "123 foo";
	imax = strtoimax(str, &end_ptr, 10);
	failures += check_long(imax, 123LL);
	diff = end_ptr - str;
	failures += check_long((long)diff, 3L);

	str = "7FFFFFFF foo";
	imax = strtoimax(str, NULL, 16);
	failures += check_long(imax, 0x7FFFFFFFLL);

	str = "4badc0de foo";
	imax = strtoimax(str, NULL, 16);
	failures += check_long(imax, 0x4badc0deLL);

	if (test_null) {
		end_ptr = "wrong";
		str = NULL;
		imax = strtoimax(str, &end_ptr, 10);
		failures += check_long(imax, 0UL);
	}

	return failures;
}

int test_strtoumax(int test_null)
{
	int failures;
	uintmax_t umax;
	char *str, *end_ptr;
	ssize_t diff;

	failures = 0;

	end_ptr = "wrong";
	str = "123 foo";
	umax = strtoumax(str, &end_ptr, 10);
	failures += check_unsigned_long(umax, 123ULL);
	diff = end_ptr - str;
	failures += check_long((long)diff, 3L);

	str = "7FFFFFFF foo";
	umax = strtoumax(str, NULL, 16);
	failures += check_unsigned_long(umax, 0x7FFFFFFFULL);

	str = "4badc0de foo";
	umax = strtoumax(str, NULL, 16);
	failures += check_unsigned_long(umax, 0x4badc0deULL);

	if (test_null) {
		end_ptr = "wrong";
		str = NULL;
		umax = strtoumax(str, &end_ptr, 10);
		failures += check_unsigned_long(umax, 0UL);
	}

	return failures;
}

int main(int argc, char **argv)
{
	int test_null;
	int failures;

	test_null = (argc > 1) ? atoi(argv[1]) : 1;

	failures = 0;

	failures += test_strtol(test_null);
	failures += test_strtoll(test_null);
	failures += test_strtoul(test_null);
	failures += test_strtoull(test_null);
	failures += test_strtoimax(test_null);
	failures += test_strtoumax(test_null);

	return check_status(failures);
}
