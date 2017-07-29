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
#ifndef _LINUX_AMD64_LIMITS_H
#define _LINUX_AMD64_LIMITS_H	1

#define CHAR_BIT	8

#define CHAR_MIN	(-128)
#define CHAR_MAX	127
#define UCHAR_MAX	255

#define SHRT_MIN	(-32768)
#define SHRT_MAX	32767
#define USHRT_MAX	65535

#define INT_MIN		(-2147483648)
#define INT_MAX		2147483647
#define UINT_MAX	4294967295U

#define LONG_MIN	(-9223372036854775808LL)
#define LONG_MAX	9223372036854775807LL
#define ULONG_MAX	18446744073709551615ULL

#define LLONG_MIN	(-9223372036854775808LL)
#define LLONG_MAX	9223372036854775807LL
#define ULLONG_MAX	18446744073709551615ULL

#endif /* _LINUX_AMD_LIMITS_H */
