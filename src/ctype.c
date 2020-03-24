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
#include <ctype.h>

int ehnlc_isalpha(int c)
{
	return (islower(c) || isupper(c)) ? 1024 : 0;
}

int ehnlc_isalnum(int c)
{
	return (isalpha(c) || isdigit(c)) ? 8 : 0;
}

int ehnlc_isascii(int c)
{
	return (c >= 0 && c <= 127) ? 1 : 0;
}

int ehnlc_isblank(int c)
{
	return (c == ' ' || c == '\t') ? 1 : 0;
}

int ehnlc_islower(int c)
{
	return (c >= 'a' && c <= 'z') ? 512 : 0;
}

int ehnlc_isupper(int c)
{
	return (c >= 'A' && c <= 'Z') ? 256 : 0;
}

int ehnlc_isdigit(int c)
{
	return (c >= '0' && c <= '9') ? 2048 : 0;
}

int ehnlc_isxdigit(int c)
{
	return (isdigit(c) || (c >= 'A' && c <= 'F')
		|| (c >= 'a' && c <= 'f')) ? 4096 : 0;
}

int ehnlc_isspace(int c)
{
	switch (c) {
	case '\t':
	case '\n':
	case '\v':
	case '\f':
	case '\r':
	case ' ':
		return 8192;
	default:
		return 0;
	}
}

int ehnlc_iscntrl(int c)
{
	return ((c >= 0 && c <= 31) || (c == 127)) ? 2 : 0;
}

int ehnlc_isgraph(int c)
{
	return (c < 0 || isspace(c) || iscntrl(c) || c >= 128) ? 0 : 32768;
}

int ehnlc_isprint(int c)
{
	return ((c == ' ') || isgraph(c)) ? 16384 : 0;
}

int ehnlc_ispunct(int c)
{
	return ((c >= 33 && c <= 47) || (c >= 58 && c <= 64)
		|| (c >= 91 && c <= 96) || (c >= 123 && c <= 126)) ? 4 : 0;
}

int ehnlc_toupper(int c)
{
	if (c >= 'a' && c <= 'z') {
		return 'A' + (c - 'a');
	}
	return c;
}

int ehnlc_tolower(int c)
{
	if (c >= 'A' && c <= 'Z') {
		return 'a' + (c - 'A');
	}
	return c;
}
