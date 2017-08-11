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

char *strcat(char *dest, const char *src)
{
	char *d;

	for (d = dest; *d; ++d) ;

	while (*src) {
		*d++ = *src++;
	}
	*d = '\0';

	return dest;
}

char *strncat(char *dest, const char *src, size_t n)
{
	char *d;

	for (d = dest; *d; ++d) ;

	for (; n && *src; --n) {
		*d++ = *src++;
	}
	*d = '\0';

	return dest;
}

char *strchr(const char *s, int c)
{
	for (; *s && *s != c; ++s) ;
	if (*s == '\0' && c != 0) {
		return NULL;
	}
	return (char *)s;
}

char *strrchr(const char *s, int c)
{
	char *r;
	for (r = NULL; *s; ++s) {
		if (*s == c) {
			r = (char *)s;
		}
	}
	return r;
}

char *strchrnul(const char *s, int c)
{
	for (; *s && *s != c; ++s) ;
	return (char *)s;
}

size_t strlen(char const *str)
{
	char const *p;
	if (!str) {
		return 0;
	}
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

char *strpbrk(const char *s, const char *accept)
{
	size_t i, j, len;

	if (!s) {
		return NULL;
	}
	if (!accept) {
		return NULL;
	}

	len = strlen(accept);
	if (!len) {
		return NULL;
	}

	for (i = 0; s[i]; ++i) {
		for (j = 0; j < len; ++j) {
			if (s[i] == accept[j]) {
				return (char *)(s + i);
			}
		}
	}
	return NULL;
}

size_t strspn(const char *s, const char *accept)
{
	size_t i, j, found, len;

	if (!s) {
		return 0;
	}
	if (!accept) {
		return strlen(accept);
	}

	len = strlen(accept);
	if (!len) {
		return 0;
	}

	for (i = 0; s[i]; ++i) {
		found = 0;
		for (j = 0; !found && j < len; ++j) {
			if (s[i] == accept[j]) {
				found = 1;
			}
		}
		if (!found) {
			return i;
		}
	}
	return i;
}

size_t strcspn(const char *s, const char *reject)
{
	size_t i, j, found, len;

	if (!s) {
		return 0;
	}
	if (!reject) {
		return strlen(s);
	}

	len = strlen(reject);
	if (!len) {
		return strlen(s);
	}

	for (i = 0; s[i]; ++i) {
		found = 0;
		for (j = 0; !found && j < len; ++j) {
			if (s[i] == reject[j]) {
				return i;
			}
		}
	}
	return i;
}

char *strstr(const char *haystack, const char *needle)
{
	size_t i, j, found, len;

	if (!haystack) {
		return NULL;
	}

	len = 0;
	if (!needle || !(len = strlen(needle))) {
		return (char *)haystack;
	}

	for (i = 0; haystack[i]; ++i) {
		found = 1;
		for (j = 0; found && j < len; ++j) {
			if (haystack[i] != needle[j]) {
				found = 0;
			}
		}
		if (found) {
			return (char *)(haystack + i);
		}
	}
	return NULL;
}

char *_eh_strtok;

char *strtok(char *s, const char *delim)
{
	return strtok_r(s, delim, &_eh_strtok);
}

char *strtok_r(char *s, const char *delim, char **saveptr)
{
	char *tok;

	if (!saveptr) {
		return NULL;
	}

	if (!delim || !(*delim)) {
		return s;
	}

	if (!s) {
		s = *saveptr;
	}
	if (!s) {
		return NULL;
	}

	s += strspn(s, delim);
	if (!(*s)) {
		*saveptr = s;
		return NULL;
	}

	tok = s;
	s = strpbrk(tok, delim);
	if (!s) {
		*saveptr = NULL;
	} else {
		*s = '\0';
		*saveptr = s + 1;
	}
	return tok;
}

/* strcoll and strxfrm are not supported */
size_t strxfrm(char *dest, const char *src, size_t n)
{
	return strlen(strncpy(dest, src, n));
}

/* strcoll and strxfrm are not supported */
int strcoll(const char *s1, const char *s2)
{
	return strcmp(s1, s2);
}
