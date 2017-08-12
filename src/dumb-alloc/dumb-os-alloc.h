/*
dumb-os-alloc.h: os-specific call declarations
Copyright (C) 2012, 2017 Eric Herman <eric@freesa.org>

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

#ifndef DUMB_OS_ALLOC_H
#define DUMB_OS_ALLOC_H

#include <stddef.h>

char *dumb_os_mmap(size_t bytes_length);
int dumb_os_munmap(void *addr, size_t bytes_length);

size_t dumb_os_page_size();
size_t dumb_os_mem_limit();

#endif /* DUMB_OS_ALLOC_H */
