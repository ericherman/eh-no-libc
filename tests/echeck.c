/*
libecheck: "E(asy)Check" boiler-plate to make simple testing easier
Copyright (C) 2016 Eric Herman <eric@freesa.org>

This work is free software: you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This work is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.
*/
#include "echeck.h"
#include <string.h>

int echeck_char_m(FILE *err, const char *func, const char *file, int line,
		  char actual, char expected, const char *msg)
{
	if (expected == actual) {
		return 0;
	}
	if (err == NULL) {
		err = stderr;
	}
	fprintf(err, "FAIL: %s%sExpected '%c' but was '%c' [%s%s%s:%d]\n",
		(msg == NULL) ? "" : msg, (msg == NULL) ? "" : " ", expected,
		actual, (func == NULL) ? "" : func,
		(func == NULL) ? "" : " at ", file, line);
	return 1;
}

int echeck_unsigned_long_m(FILE *err, const char *func, const char *file,
			   int line, unsigned long actual,
			   unsigned long expected, const char *msg)
{
	if (expected == actual) {
		return 0;
	}
	if (err == NULL) {
		err = stderr;
	}
	fprintf(err, "FAIL: %s%sExpected %lu but was %lu [%s%s%s:%d]\n",
		(msg == NULL) ? "" : msg, (msg == NULL) ? "" : " ", expected,
		actual, (func == NULL) ? "" : func,
		(func == NULL) ? "" : " at ", file, line);
	return 1;
}

int echeck_long_m(FILE *err, const char *func, const char *file, int line,
		  long actual, long expected, const char *msg)
{
	if (expected == actual) {
		return 0;
	}
	if (err == NULL) {
		err = stderr;
	}
	fprintf(err, "FAIL: %s%sExpected %ld but was %ld [%s%s%s:%d]\n",
		(msg == NULL) ? "" : msg, (msg == NULL) ? "" : " ", expected,
		actual, (func == NULL) ? "" : func,
		(func == NULL) ? "" : " at ", file, line);
	return 1;
}

int echeck_size_t_m(FILE *err, const char *func, const char *file, int line,
		    size_t actual, size_t expected, const char *msg)
{
	if (expected == actual) {
		return 0;
	}
	if (err == NULL) {
		err = stderr;
	}
	fprintf(err, "FAIL: %s%sExpected %lu but was %lu [%s%s%s:%d]\n",
		(msg == NULL) ? "" : msg, (msg == NULL) ? "" : " ",
		(unsigned long)expected, (unsigned long)actual,
		(func == NULL) ? "" : func, (func == NULL) ? "" : " at ", file,
		line);
	return 1;
}

int echeck_str_m(FILE *err, const char *func, const char *file, int line,
		 const char *actual, const char *expected, const char *msg)
{
	if (actual == expected) {
		return 0;
	}
	if (actual != NULL && expected != NULL && strcmp(expected, actual) == 0) {
		return 0;
	}
	if (err == NULL) {
		err = stderr;
	}
	fprintf(err, "FAIL: %s%sExpected '%s' but was '%s' [%s%s%s:%d]\n",
		(msg == NULL) ? "" : msg, (msg == NULL) ? "" : " ", expected,
		actual, (func == NULL) ? "" : func,
		(func == NULL) ? "" : " at ", file, line);
	return 1;
}

int echeck_byte_array_m(FILE *err, const char *func, const char *file, int line,
			const unsigned char *actual, size_t actual_len,
			const unsigned char *expected, size_t expected_len,
			const char *msg)
{

	size_t i;
	const char *fmt;

	if (err == NULL) {
		err = stderr;
	}
	fmt = "actual/expected length mis-match %d != %d [%s%s%s:%d]\n";

	if (actual_len != expected_len) {
		fprintf(err, fmt, actual_len, expected_len,
			(func == NULL) ? "" : func,
			(func == NULL) ? "" : " at ", file, line);
		goto fail;
	}
	for (i = 0; i < actual_len; i++) {
		if (actual[i] != expected[i]) {
			fprintf(err, "buffers differ at %lu\n",
				(unsigned long)i);
			goto fail;
		}
	}
	return 0;

fail:
	fprintf(err, "FAIL: %s%s[%s%s%s:%d]\n", (msg == NULL) ? "" : msg,
		(msg == NULL) ? "" : " ", (func == NULL) ? "" : func,
		(func == NULL) ? "" : " at ", file, line);
	for (i = 0; i < actual_len; i++) {
		fprintf(err, "actual[%lu]=%02x\n", (unsigned long)i, actual[i]);
	}
	for (i = 0; i < expected_len; i++) {
		fprintf(err, "expected[%lu]=%02x\n", (unsigned long)i,
			expected[i]);
	}
	return 1;
}

int echeck_ptr_m(FILE *err, const char *func, const char *file, int line,
		 const void *actual, const void *expected, const char *msg)
{
	if (expected == actual) {
		return 0;
	}
	if (err == NULL) {
		err = stderr;
	}
	fprintf(err, "FAIL: %s%sExpected '%p' but was '%p' [%s%s%s:%d]\n",
		(msg == NULL) ? "" : msg, (msg == NULL) ? "" : " ", expected,
		actual, (func == NULL) ? "" : func,
		(func == NULL) ? "" : " at ", file, line);
	return 1;
}

char echeck_status_m(FILE *err, const char *func, const char *file, int line,
		     int val, const char *msg)
{
	char c;

	if ((-128 <= val) && (val <= 127)) {
		c = (char)val;
		return val;
	}
	if (val < -128) {
		c = -128;
	} else {
		c = 127;
	}
	if (err == NULL) {
		err = stderr;
	}
	fprintf(err, "%s%s'%d' capped at '%c' [%s%s%s:%d]\n",
		(msg == NULL) ? "" : msg, (msg == NULL) ? "" : " ",
		val, c,
		(func == NULL) ? "" : func,
		(func == NULL) ? "" : " at ", file, line);
	return c;
}
