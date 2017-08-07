/*
test-strchr.c
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
#include "echeck.h"
#include <stdio.h>
#include <string.h>

/* int main(int argc, char **argv) */
int main(void)
{
	char *rv, *source;
	int failures;

	failures = 0;

	source = "foo bar baz whiz bang";
	rv = strchr(source, 'b');
	failures += check_ptr(rv, source + 4);
	rv = strrchr(source, 'b');
	failures += check_ptr(rv, source + strlen(source) - 4);
	rv = strchr(source, 'B');
	failures += check_ptr(rv, NULL);
	rv = strchrnul(source, 'B');
	failures += check_ptr(rv, source + strlen(source));

	return check_status(failures);
}
