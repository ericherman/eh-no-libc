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

int isascii(int c)
{
	return (c >= 0 && c <= 127) ? 1 : 0;
}

int isblank(int c)
{
	return (c == ' ' || c == '\t') ? 1 : 0;
}

int islower(int c)
{
	return (c >= 'a' && c <= 'z') ? 1 : 0;
}

int isupper(int c)
{
	return (c >= 'A' && c <= 'Z') ? 1 : 0;
}

int isspace(int c)
{
	switch (c) {
	case '\t':
	case '\n':
	case '\v':
	case '\f':
	case '\r':
	case ' ':
		return 1;
	default:
		return 0;
	}
}

int toupper(int c)
{
	if (c >= 'a' && c <= 'z') {
		return 'A' + (c - 'a');
	}
	return c;
}

int tolower(int c)
{
	if (c >= 'A' && c <= 'Z') {
		return 'a' + (c - 'A');
	}
	return c;
}
