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
#ifndef _STRINGS_H
#define _STRINGS_H	1

/* http://pubs.opengroup.org/onlinepubs/007908775/xsh/strings.h.html */

#include <stdint.h>

/* int bcmp(const void *s1, const void *s2, size_t n); */
#define bcmp(s1, s2, n) memcmp((s1), (s2), (n))

/* void bcopy(const void *src, void *dest, size_t n); */
#define bcopy(s1, s2, n) memmove((s2), (s1), (n))

/* void bzero(void *s, size_t n); */
#define bzero(s, n) memset((s), 0, (n))

#define ffs(i) ehnlc_ffs(i)
int ehnlc_ffs(int i);

#define ffsl(l) ehnlc_ffsl(l)
int ehnlc_ffsl(long int l);

#if (_LONG_SAME_AS_LLONG)
#define ffsll(ll) ehnlc_ffsl(ll)
#else
#define ffsll(ll) ehnlc_ffsll(ll)
int ehnlc_ffsll(long long int ll);
#endif

/* char *index(const char *s, int c); */
#define index(s, c) strchr((s), (c));

/* char *rindex(const char *s, int c); */
#define rindex(s, c) strrchr((s), (c));

#define strcasecmp(s1, s2) ehnlc_strcasecmp(s1, s2)
int ehnlc_strcasecmp(const char *s1, const char *s2);

#define strncasecmp(s1, s2, n) ehnlc_strncasecmp(s1, s2, n)
int ehnlc_strncasecmp(const char *s1, const char *s2, size_t n);

#endif /* _STRINGS_H */
