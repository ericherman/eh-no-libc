/*
eh-printf - A version of sprintf for embedded applications
Copyright (C) 2016 Eric Herman

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
#ifndef EH_PRINTF
#define EH_PRINTF

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdarg.h>

/* Returns the number of characters printed (excluding the null byte). */
int eh_printf(const char *format, ...);

/* Returns the number of characters printed (excluding the null byte).
   If the output  was truncated  due  to  this  limit  then the return
   value is the number of characters (excluding the terminating null
   byte) which would have been written  to the final string if enough
   space had been available.  Thus, a return value of size or more means
   that the output  was  truncated. */
int eh_snprintf(char *str, size_t size, const char *format, ...);

int eh_vprintf(const char *format, va_list ap);

int eh_vsnprintf(char *str, size_t size, const char *format, va_list ap);

#ifdef __cplusplus
}
#endif

#endif /* EH_PRINTF */
