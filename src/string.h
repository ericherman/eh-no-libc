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
#ifndef _STRING_H
#define _STRING_H	1

#include <stdint.h>

char *strcat(char *dest, const char *src);

char *strncat(char *dest, const char *src, size_t n);

/* The strchr() function returns a pointer to the first occurrence of
 * the character c in the string s, or NULL if the character is not
 * found. */
char *strchr(const char *s, int c);

/* The strrchr() function returns a pointer to the last occurrence of
 * the character c in the string s, or NULL if the character is not
 * found. */
char *strrchr(const char *s, int c);

/* The  strchrnul() function is like strchr() except that if c is not
 * found in s, then it returns a pointer to the null byte at the end of
 * s, rather than NULL. */
char *strchrnul(const char *s, int c);

int strcmp(const char *s1, const char *s2);

int strncmp(const char *s1, const char *s2, size_t n);

char *strcpy(char *dest, const char *src);

char *strncpy(char *dest, const char *src, size_t n);

char *strdup(const char *s);

char *strndup(const char *s, size_t n);

size_t strlen(char const *str);

size_t strnlen(const char *s, size_t maxlen);

char *strerror(int errnum);

#endif /* _STRING_H */
