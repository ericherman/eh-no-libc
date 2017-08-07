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
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include <stdio.h>

size_t strlen(char const *str)
{
	char const *p;
	for (p = str; *p; ++p) ;
	return p - str;
}

size_t strnlen(char const *str, size_t max_len)
{
	char const *p;
	size_t i;
	if (!str) {
		return 0;
	}
	for (i = 0, p = str; i < max_len && *p; ++i, ++p) ;
	return p - str;
}

int strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	if (s1 == s2) {
		return 0;
	}
	if (!s1 || !s2) {
		return s1 ? 1 : -1;
	}
	for (i = 0; s1[i] && s2[i] && s1[i] == s2[i]; ++i) ;
	return s1[i] - s2[i];
}

int strncmp(const char *s1, const char *s2, size_t max_len)
{
	size_t i;
	if (s1 == s2) {
		return 0;
	}
	if (!s1 || !s2) {
		return s1 ? 1 : -1;
	}
	for (i = 0; i < max_len && s1[i] && s2[i] && s1[i] == s2[i]; ++i) ;
	return s1[i] - s2[i];
}

char *strcpy(char *dest, const char *src)
{
	size_t i;
	if (!dest) {
		return NULL;
	}
	i = 0;
	if (src) {
		while (*(src + i)) {
			*(dest + i) = *(src + i);
			++i;
		}
	}
	*(dest + i) = '\0';
	return dest;
}

char *strncpy(char *dest, const char *src, size_t n)
{
	size_t i;
	if (!dest) {
		return NULL;
	}
	i = 0;
	if (src) {
		while (i < n && *(src + i)) {
			*(dest + i) = *(src + i);
			++i;
		}
	}
	if (i < n) {
		*(dest + i) = '\0';
	}
	return dest;
}

char *strdup(const char *s)
{
	size_t len;
	char *dup;

	len = s ? strlen(s) : 0;
	dup = malloc(len + 1);
	if (!dup) {
		return NULL;
	}
	dup[len] = '\0';

	strcpy(dup, s);

	return dup;
}

char *strndup(const char *s, size_t n)
{
	size_t len;
	char *dup;

	len = s ? strnlen(s, n) : 0;
	dup = malloc(len + 1);
	if (!dup) {
		return NULL;
	}
	dup[len] = '\0';

	strncpy(dup, s, n);

	return dup;
}

char *strerror(int errnum)
{
	size_t offset;

	offset = (unsigned)errnum;
	if (offset < _eh_unknown_err) {
		return errstrs[offset];
	}
	return errstrs[_eh_unknown_err];
}
