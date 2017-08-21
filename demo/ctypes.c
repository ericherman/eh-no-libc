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
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv)
{
	int c, limit;

	limit = (argc > 1) ? atoi(argv[1]) : 257;

	for (c = -1; c <= limit; ++c) {
		printf("isalnum(%d) == (%d)\n", c, isalnum(c));
		printf("isalpha(%d) == (%d)\n", c, isalpha(c));
		printf("isascii(%d) == (%d)\n", c, isascii(c));
		printf("isblank(%d) == (%d)\n", c, isblank(c));
		printf("iscntrl(%d) == (%d)\n", c, iscntrl(c));
		printf("isdigit(%d) == (%d)\n", c, isdigit(c));
		printf("islower(%d) == (%d)\n", c, islower(c));
		printf("isspace(%d) == (%d)\n", c, isspace(c));
		printf("isupper(%d) == (%d)\n", c, isupper(c));
		printf("isxdigit(%d) == (%d)\n", c, isxdigit(c));
		printf("isgraph(%d) == (%d)\n", c, isgraph(c));
		printf("isprint(%d) == (%d)\n", c, isprint(c));
		printf("ispunct(%d) == (%d)\n", c, ispunct(c));
		printf("tolower(%d) == (%d)\n", c, tolower(c));
		printf("toupper(%d) == (%d)\n", c, toupper(c));
		printf("\n");
	}

	return 0;
}
