#include <stdlib.h>
#include <syscall.h>
#include <limits.h>
#include "dumb-alloc-global.h"

int abs(int j)
{
	if (j < 0 && j > INT_MIN) {
		return -j;
	}
	return j;
}

long int labs(long int j)
{
	if (j < 0 && j > LONG_MIN) {
		return -j;
	}
	return j;
}

long long int llabs(long long int j)
{
	if (j < 0 && j > LLONG_MIN) {
		return -j;
	}
	return j;
}

int atoi(const char *nptr)
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

long atol(const char *nptr)
{
	long negate;
	long val;
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
			val = val * 10L;
			val = val + (long)(*nptr - '0');
			++nptr;
		} else {
			end = 1;
		}
	}

	return negate * val;
}

long long atoll(const char *nptr)
{
	long long negate;
	long long val;
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
			val = val * 10LL;
			val = val + (long long)(*nptr - '0');
			++nptr;
		} else {
			end = 1;
		}
	}

	return negate * val;
}

void exit(int status)
{
	syscall1(SYS_exit, (void *)(ssize_t)status);
}

void *malloc(size_t size)
{
	return dumb_malloc(size);
}

void free(void *ptr)
{
	dumb_free(ptr);
}

void *realloc(void *ptr, size_t size)
{
	return dumb_realloc(ptr, size);
}

void *calloc(size_t nmemb, size_t size)
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
