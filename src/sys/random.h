/*
eh-no-libc - exploring coding without the standard library
Copyright (C) 2020 Eric Herman

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
#ifndef RANDOM_H
#define RANDOM_H 1

#include <stdint.h>

#define GRND_NONBLOCK	0x01
#define GRND_RANDOM	0x02

#define getrandom(buf, buflen, flags) \
  ehnlc_getrandom(buf, buflen, flags)
ssize_t getrandom(void *buf, size_t buflen, unsigned int flags);

#endif /* RANDOM_H */
