/*
eh-no-libc - exploring coding without the standard library
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
#include <strings.h>
#include <ctype.h>

int ffs(int d)
{
	size_t i;

	if (d == 0) {
		return 0;
	}

	for (i = 0; i < 8 * sizeof(int); ++i) {
		if (d & (1U << i)) {
			return i + 1;
		}
	}
	return -1;
}

int ffsl(long int ld)
{
	size_t i;

	if (ld == 0) {
		return 0;
	}

	for (i = 0; i < 8 * sizeof(long int); ++i) {
		if (ld & (1U << i)) {
			return i + 1;
		}
	}
	return -1;
}

int ffsll(long long int lld)
{
	size_t i;

	if (lld == 0) {
		return 0;
	}

	for (i = 0; i < 8 * sizeof(long long int); ++i) {
		if (lld & (1U << i)) {
			return i + 1;
		}
	}
	return -1;
}

int strcasecmp(const char *s1, const char *s2)
{
	size_t i;
	char l, r;
	int d;

	if (s1 == s2) {
		return 0;
	}
	if (!s1 || !s2) {
		return s1 ? 1 : -1;
	}
	for (i = 0; 1; ++i) {
		l = toupper(s1[i]);
		r = toupper(s2[i]);
		d = l - r;
		if (d) {
			return d;
		} else if (l == '\0') {
			return 0;
		}
	}
	return 0;
}

int strncasecmp(const char *s1, const char *s2, size_t n)
{
	size_t i;
	char l, r;
	int d;

	if (s1 == s2 || n == 0) {
		return 0;
	}
	if (!s1 || !s2) {
		return s1 ? 1 : -1;
	}
	for (i = 0; i < n; ++i) {
		l = toupper(s1[i]);
		r = toupper(s2[i]);
		d = l - r;
		if (d) {
			return d;
		} else if (l == '\0') {
			return 0;
		}
	}
	return 0;
}
