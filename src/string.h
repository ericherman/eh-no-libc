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

/* http://pubs.opengroup.org/onlinepubs/007908775/xsh/string.h.html */

#include <stdint.h>

#define memccpy(dest, src, c, n) ehnlc_memccpy(dest, src, c, n)
void *ehnlc_memccpy(void *dest, const void *src, int c, size_t n);

#define memchr(s, c, n) ehnlc_memchr(s, c, n)
void *ehnlc_memchr(const void *s, int c, size_t n);

#define memrchr(s, c, n) ehnlc_memrchr(s, c, n)
void *ehnlc_memrchr(const void *s, int c, size_t n);

#define rawmemchr(s, c) ehnlc_rawmemchr(s, c)
void *ehnlc_rawmemchr(const void *s, int c);

#define memcmp(s1, s2, n) ehnlc_memcmp(s1, s2, n)
int ehnlc_memcmp(const void *s1, const void *s2, size_t n);

#define memcpy(dest, src, n) ehnlc_memcpy(dest, src, n)
void *ehnlc_memcpy(void *dest, const void *src, size_t n);

#define memmove(dest, src, n) ehnlc_memmove(dest, src, n)
void *ehnlc_memmove(void *dest, const void *src, size_t n);

#define memset(s, c, n) ehnlc_memset(s, c, n)
void *ehnlc_memset(void *s, int c, size_t n);

#define strcat(dest, src) ehnlc_strcat(dest, src)
char *ehnlc_strcat(char *dest, const char *src);

#define strncat(dest, src, n) ehnlc_strncat(dest, src, n)
char *ehnlc_strncat(char *dest, const char *src, size_t n);

/* The strchr() function returns a pointer to the first occurrence of
 * the character c in the string s, or NULL if the character is not
 * found. */
#define strchr(s, c) ehnlc_strchr(s, c)
char *ehnlc_strchr(const char *s, int c);

/* The strrchr() function returns a pointer to the last occurrence of
 * the character c in the string s, or NULL if the character is not
 * found. */
#define strrchr(s, c) ehnlc_strrchr(s, c)
char *ehnlc_strrchr(const char *s, int c);

/* The  strchrnul() function is like strchr() except that if c is not
 * found in s, then it returns a pointer to the null byte at the end of
 * s, rather than NULL. */
#define strchrnul(s, c) ehnlc_strchrnul(s, c)
char *ehnlc_strchrnul(const char *s, int c);

#define strcmp(s1, s2) ehnlc_strcmp(s1, s2)
int ehnlc_strcmp(const char *s1, const char *s2);

#define strncmp(s1, s2, n) ehnlc_strncmp(s1, s2, n)
int ehnlc_strncmp(const char *s1, const char *s2, size_t n);

#define strcpy(dest, src) ehnlc_strcpy(dest, src)
char *ehnlc_strcpy(char *dest, const char *src);

#define strncpy(dest, src, n) ehnlc_strncpy(dest, src, n)
char *ehnlc_strncpy(char *dest, const char *src, size_t n);

#define strdup(s) ehnlc_strdup(s)
char *ehnlc_strdup(const char *s);

#define strndup(s, n) ehnlc_strndup(s, n)
char *ehnlc_strndup(const char *s, size_t n);

#define strlen(str) ehnlc_strlen(str)
size_t ehnlc_strlen(char const *str);

#define strnlen(s, maxlen) ehnlc_strnlen(s, maxlen)
size_t ehnlc_strnlen(const char *s, size_t maxlen);

#define strerror(errnum) ehnlc_strerror(errnum)
char *ehnlc_strerror(int errnum);

#define strpbrk(s, accept) ehnlc_strpbrk(s, accept)
char *ehnlc_strpbrk(const char *s, const char *accept);

#define strspn(s, accept) ehnlc_strspn(s, accept)
size_t ehnlc_strspn(const char *s, const char *accept);

#define strcspn(s, reject) ehnlc_strcspn(s, reject)
size_t ehnlc_strcspn(const char *s, const char *reject);

#define strstr(haystack, needle) ehnlc_strstr(haystack, needle)
char *ehnlc_strstr(const char *haystack, const char *needle);

#define strtok(str, delim) ehnlc_strtok(str, delim)
char *ehnlc_strtok(char *str, const char *delim);

#define strtok_r(str, delim, saveptr) ehnlc_strtok_r(str, delim, saveptr)
char *ehnlc_strtok_r(char *str, const char *delim, char **saveptr);

/* strcoll and strxfrm are not supported */
#define strxfrm(dest, src, n) ehnlc_strxfrm(dest, src, n)
size_t ehnlc_strxfrm(char *dest, const char *src, size_t n);

/* strcoll and strxfrm are not supported */
#define strcoll(s1, s2) ehnlc_strcoll(s1, s2)
int ehnlc_strcoll(const char *s1, const char *s2);

#endif /* _STRING_H */
