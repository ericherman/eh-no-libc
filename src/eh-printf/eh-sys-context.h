/*
eh-sys-contxt.h - definine system specific functions needed by printf
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
#ifndef EH_SYS_CONTEXT
#define EH_SYS_CONTEXT

#ifdef __cplusplus
extern "C" {
#endif

#if HAVE_CONFIG_H
#include "config.h"
#endif

#if HAVE_STDDEF_H
#include <stddef.h>
#endif

void *start_sys_printf_context(void);

int end_sys_printf_context(void *ctx);

size_t eh_sys_output_char(void *ctx, char c);

size_t eh_sys_output_str(void *ctx, const char *str, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* EH_SYS_CONTEXT */
