/*
test-file-io-roundtrip.c
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

#ifndef PATH_MAX
#define PATH_MAX	4096
#endif

#ifndef O_TMPFILE
#ifndef __O_TMPFILE
#define __O_TMPFILE 020000000
#endif
#define O_TMPFILE (__O_TMPFILE | O_DIRECTORY)
#endif
#ifndef O_TMPFILE_MASK
#define O_TMPFILE_MASK (__O_TMPFILE | O_DIRECTORY | O_CREAT)
#endif

int main(void)
{
	char actual[80];
	const char *expect;
	int failures;
	int fd, fd2, save_errno;
	char fd_path[PATH_MAX];
	size_t num_read;

	failures = 0;

	fd = open("/tmp", O_TMPFILE | O_RDWR, S_IRUSR | S_IWUSR);
	dprintf(fd, "f%co\n%s\n", 'o', "bar");
	expect = "foo\nbar\n";

	snprintf(fd_path, PATH_MAX, "/proc/self/fd/%d", fd);
	fd2 = open(fd_path, O_RDONLY);
	if (fd2 < 0) {
		save_errno = errno;
		fprintf(stderr, "could not open '%s' errno: %d\n", fd_path,
			save_errno);
		return 1;
	}

	num_read = read(fd2, actual, 79);
	actual[num_read] = '\0';

	close(fd2);
	close(fd);

	failures += check_str(actual, expect);

	return failures ? 1 : 0;
}
