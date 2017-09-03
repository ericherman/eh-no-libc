/*
eh-printf-sys-context-linux.c - linux specific system calls
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

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "eh-printf-sys-context.h"

int EH_PRINTF_SYSOUT_FILENO = STDOUT_FILENO;
int EH_PRINTF_SYSERR_FILENO = STDERR_FILENO;

void start_sys_printf_context(struct eh_printf_context_s *ctx, int fileno)
{
	if (!ctx) {
		return;
	}

	ctx->error = 0;
	ctx->data = NULL;

	if (fileno < 1) {
		ctx->fileno = EH_PRINTF_SYSOUT_FILENO;
	} else {
		ctx->fileno = fileno;
	}
}

int end_sys_printf_context(struct eh_printf_context_s *ctx)
{
	char *msg;
	size_t len;
	int rv;

	if (ctx && ctx->error) {
		msg = strerror(ctx->error);
		len = strlen(msg);
		rv = write(EH_PRINTF_SYSERR_FILENO, msg, len);
		if (rv > 0) {
			rv = write(EH_PRINTF_SYSERR_FILENO, "\n", 1);
		}
		if (rv <= 0) {
			return 1;
		}
	}
	return 0;
}

size_t eh_sys_output_char(struct eh_printf_context_s *ctx, char c)
{
	return eh_sys_output_str(ctx, &c, 1);
}

size_t eh_sys_output_str(struct eh_printf_context_s *ctx, const char *buf,
			 size_t len)
{
	int rv;

	if (!ctx) {
		return 0;
	}

	rv = write(ctx->fileno, buf, len);
	if (rv < 0) {
		if (ctx->error == 0) {
			ctx->error = errno;
		}
		return 0;
	}
	return (size_t)rv;
}
