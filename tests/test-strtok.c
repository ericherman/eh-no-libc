/*
test-strtok.c
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
	int failures;
	char str[80];
	char *delim = ";\n\r|";
	char *rv, *expect;

	strcpy(str, "321 Ave. G\nSnohomish, WA 98290\nUSA");

	failures = 0;

	expect = "321 Ave. G";
	failures += (expect == NULL) ? 1 : 0;
	rv = strtok(str, delim);
	failures += (rv == NULL) ? 1 : 0;
	failures += check_str(rv, expect);
/*

	expect = "Snohomish, WA 98290";
	rv = strtok(NULL, delim);
	failures += check_str(rv, expect);

	expect = "USA";
	rv = strtok(NULL, delim);
	failures += check_str(rv, expect);

	expect = NULL;
	rv = strtok(NULL, delim);
	failures += check_str(rv, expect);
*/
	return check_status(failures);
}
