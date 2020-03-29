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
#include <stdlib.h>
#include <syscall.h>
#include <limits.h>
#include <errno.h>
#include <assert.h>
#include "dumb-alloc-global.h"

int ehnlc_abs(int j)
{
	if (j < 0 && j > INT_MIN) {
		return -j;
	}
	return j;
}

long int ehnlc_labs(long int j)
{
	if (j < 0 && j > LONG_MIN) {
		return -j;
	}
	return j;
}

#if (_LONG_SAME_AS_LLONG == 0)
long long int ehnlc_llabs(long long int j)
{
	if (j < 0 && j > LLONG_MIN) {
		return -j;
	}
	return j;
}
#endif

int ehnlc_atoi(const char *nptr)
{
	int negate;
	int val;
	int end;
	if (!nptr) {
		return 0;
	}
	if (*nptr == '-') {
		nptr++;
		negate = -1;
	} else {
		negate = 1;
	}
	end = 0;
	val = 0;
	while (*nptr && !end) {
		if (*nptr >= '0' && *nptr <= '9') {
			val = val * 10;
			val = val + (*nptr - '0');
			++nptr;
		} else {
			end = 1;
		}
	}

	return negate * val;
}

long ehnlc_atol(const char *nptr)
{
	return strtol(nptr, NULL, 10);
}

#if (_LONG_SAME_AS_LLONG == 0)
long long ehnlc_atoll(const char *nptr)
{
	return strtoll(nptr, NULL, 10);
}
#endif

long int ehnlc_strtol(const char *nptr, char **endptr, int base)
{
	long val;
	int negate, end;
	char ascii_end1, ascii_end2, ascii_end3;

	if (!nptr) {
		if (endptr) {
			*endptr = NULL;
		}
		return 0;
	}

	if (base < 2 || base > 36) {
		errno = EINVAL;
		if (endptr) {
			*endptr = NULL;
		}
		return 0;
	}
	if (base <= 10) {
		ascii_end1 = '0' + (base - 1);
		ascii_end2 = 0;
		ascii_end3 = 0;
	} else {
		ascii_end1 = '9';
		ascii_end2 = 'A' + (base - 11);
		ascii_end3 = 'a' + (base - 11);
	}

	if (*nptr == '-') {
		nptr++;
		negate = -1;
	} else {
		negate = 0;
	}
	end = 0;
	val = 0;
	while (*nptr && !end) {
		if (*nptr >= '0' && *nptr <= ascii_end1) {
			val = val * (long)base;
			val = val + (long)(*nptr - '0');
			++nptr;
		} else if (*nptr >= 'A' && *nptr <= ascii_end2) {
			val = val * (long)base;
			val = val + 10L + (long)(*nptr - 'A');
			++nptr;
		} else if (*nptr >= 'a' && *nptr <= ascii_end3) {
			val = val * (long)base;
			val = val + 10L + (long)(*nptr - 'a');
			++nptr;
		} else {
			end = 1;
		}
	}

	if (endptr) {
		*endptr = (char *)nptr;
	}
	return negate ? -val : val;
}

#if (_LONG_SAME_AS_LLONG == 0)
long long int ehnlc_strtoll(const char *nptr, char **endptr, int base)
{
	long long int val;
	int negate, end;
	char ascii_end1, ascii_end2, ascii_end3;

	if (!nptr) {
		if (endptr) {
			*endptr = NULL;
		}
		return 0;
	}

	if (base < 2 || base > 36) {
		errno = EINVAL;
		if (endptr) {
			*endptr = NULL;
		}
		return 0;
	}
	if (base <= 10) {
		ascii_end1 = '0' + (base - 1);
		ascii_end2 = 0;
		ascii_end3 = 0;
	} else {
		ascii_end1 = '9';
		ascii_end2 = 'A' + (base - 11);
		ascii_end3 = 'a' + (base - 11);
	}

	if (*nptr == '-') {
		nptr++;
		negate = -1;
	} else {
		negate = 0;
	}
	end = 0;
	val = 0;
	while (*nptr && !end) {
		if (*nptr >= '0' && *nptr <= ascii_end1) {
			val = val * (long long int)base;
			val = val + (long long int)(*nptr - '0');
			++nptr;
		} else if (*nptr >= 'A' && *nptr <= ascii_end2) {
			val = val * (long long int)base;
			val = val + 10LL + (long long int)(*nptr - 'A');
			++nptr;
		} else if (*nptr >= 'a' && *nptr <= ascii_end3) {
			val = val * (long long int)base;
			val = val + 10LL + (long long int)(*nptr - 'a');
			++nptr;
		} else {
			end = 1;
		}
	}

	if (endptr) {
		*endptr = (char *)nptr;
	}
	return negate ? -val : val;
}
#endif

unsigned long int ehnlc_strtoul(const char *nptr, char **endptr, int base)
{
	unsigned long int val;
	int end;
	char ascii_end1, ascii_end2, ascii_end3;

	if (!nptr) {
		if (endptr) {
			*endptr = NULL;
		}
		return 0;
	}

	if (base < 2 || base > 36) {
		errno = EINVAL;
		if (endptr) {
			*endptr = NULL;
		}
		return 0;
	}
	if (base <= 10) {
		ascii_end1 = '0' + (base - 1);
		ascii_end2 = 0;
		ascii_end3 = 0;
	} else {
		ascii_end1 = '9';
		ascii_end2 = 'A' + (base - 11);
		ascii_end3 = 'a' + (base - 11);
	}

	end = 0;
	val = 0;
	while (*nptr && !end) {
		if (*nptr >= '0' && *nptr <= ascii_end1) {
			val = val * (unsigned long int)base;
			val = val + (unsigned long int)(*nptr - '0');
			++nptr;
		} else if (*nptr >= 'A' && *nptr <= ascii_end2) {
			val = val * (unsigned long int)base;
			val = val + 10UL + (unsigned long int)(*nptr - 'A');
			++nptr;
		} else if (*nptr >= 'a' && *nptr <= ascii_end3) {
			val = val * (unsigned long)base;
			val = val + 10UL + (unsigned long int)(*nptr - 'a');
			++nptr;
		} else {
			end = 1;
		}
	}

	if (endptr) {
		*endptr = (char *)nptr;
	}
	return val;
}

#if (_LONG_SAME_AS_LLONG == 0)
unsigned long long int ehnlc_strtoull(const char *nptr, char **endptr, int base)
{
	unsigned long long int val;
	int end;
	char ascii_end1, ascii_end2, ascii_end3;

	if (!nptr) {
		if (endptr) {
			*endptr = NULL;
		}
		return 0;
	}

	if (base < 2 || base > 36) {
		errno = EINVAL;
		if (endptr) {
			*endptr = NULL;
		}
		return 0;
	}
	if (base <= 10) {
		ascii_end1 = '0' + (base - 1);
		ascii_end2 = 0;
		ascii_end3 = 0;
	} else {
		ascii_end1 = '9';
		ascii_end2 = 'A' + (base - 11);
		ascii_end3 = 'a' + (base - 11);
	}

	end = 0;
	val = 0;
	while (*nptr && !end) {
		if (*nptr >= '0' && *nptr <= ascii_end1) {
			val = val * (unsigned long long int)base;
			val = val + (unsigned long long int)(*nptr - '0');
			++nptr;
		} else if (*nptr >= 'A' && *nptr <= ascii_end2) {
			val = val * (unsigned long long int)base;
			val =
			    val + 10ULL + (unsigned long long int)(*nptr - 'A');
			++nptr;
		} else if (*nptr >= 'a' && *nptr <= ascii_end3) {
			val = val * (unsigned long long int)base;
			val =
			    val + 10ULL + (unsigned long long int)(*nptr - 'a');
			++nptr;
		} else {
			end = 1;
		}
	}

	if (endptr) {
		*endptr = (char *)nptr;
	}
	return val;
}
#endif

void ehnlc_exit(int status)
{
	ehnlc_syscall1(SYS_exit, (void *)(ssize_t)status);
}

void *ehnlc_calloc(size_t nmemb, size_t size)
{
	size_t i, len;
	unsigned char *chars;

	len = nmemb * size;
	chars = malloc(len);
	if (chars) {
		for (i = 0; i < len; ++i) {
			chars[i] = '\0';
		}
	}
	return chars;
}

static void ehnlc_memswap(void *p1, void *p2, size_t len)
{
	unsigned char *c1, *c2, tmp;

	for (c1 = p1, c2 = p2; len; ++c1, ++c2, --len) {
		tmp = *c1;
		*c1 = *c2;
		*c2 = tmp;
	}
}

typedef int (*ehnlc_compar_func)(const void *left, const void *right);

static size_t ehnlc_qsort_lomuto_partition(unsigned char *base, size_t lb,
					   size_t ub, size_t size,
					   ehnlc_compar_func compar)
{
	unsigned char *pivot, *x, *y;
	size_t i, j;
	int cmp;

	assert(ub > 0);

	pivot = base + (ub * size);

	for (i = lb, j = lb; j < ub; ++j) {
		x = base + (j * size);
		cmp = compar(x, pivot);
		if (cmp < 0) {
			if (i != j) {
				y = base + (i * size);
				ehnlc_memswap(x, y, size);
			}
			++i;
		}
	}
	if (i != ub) {
		y = base + (i * size);
		ehnlc_memswap(y, pivot, size);
	}
	return i;
}

static void ehnlc_qsort_lomuto(unsigned char *base, size_t lb, size_t ub,
			       size_t size, ehnlc_compar_func compar)
{
	size_t pos;
	if (lb >= ub) {
		return;
	}
	pos = ehnlc_qsort_lomuto_partition(base, lb, ub, size, compar);
	if (pos > 0) {
		ehnlc_qsort_lomuto(base, lb, pos - 1, size, compar);
	}
	if (pos < ub) {
		ehnlc_qsort_lomuto(base, pos + 1, ub, size, compar);
	}
}

void ehnlc_qsort(void *base, size_t nmemb, size_t size,
		 ehnlc_compar_func compar)
{
	if (nmemb < 1) {
		return;
	}
	ehnlc_qsort_lomuto(base, 0, nmemb - 1, size, compar);
}
