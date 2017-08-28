/*
test-fgetc.c
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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

#ifndef O_TMPFILE
#ifndef __O_TMPFILE
#define __O_TMPFILE 020000000
#endif
#define O_TMPFILE (__O_TMPFILE | O_DIRECTORY)
#endif

int main(void)
{
	int failures;
	FILE *f;
	int fd, save_errno;
	char fd_path[PATH_MAX];

	failures = 0;

	fd = open("/tmp", O_TMPFILE | O_RDWR, S_IRUSR | S_IWUSR);
	dprintf(fd, "foo\nbar\n");

	snprintf(fd_path, PATH_MAX, "/proc/self/fd/%d", fd);
	f = fopen(fd_path, "r+");
	if (!f) {
		save_errno = errno;
		fprintf(stderr, "could not open '%s' errno: %d\n", fd_path,
			save_errno);
		return 1;
	}

	failures += check_int(fgetc(f), (int)'f');
	failures += check_int(fgetc(f), (int)'o');
	failures += check_int(fgetc(f), (int)'o');
	failures += check_int(fgetc(f), (int)'\n');
	failures += check_int(fgetc(f), (int)'b');
	failures += check_int(fgetc(f), (int)'a');
	failures += check_int(fgetc(f), (int)'r');
	failures += check_int(fgetc(f), (int)'\n');
	failures += check_int(fgetc(f), EOF);

	fclose(f);
	close(fd);

	return failures ? 1 : 0;
}
