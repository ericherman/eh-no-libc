/*
eh-printf.c - A version of sprintf for embedded applications
Copyright (C) 2016 Eric Herman

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later
version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License (COPYING) along with this library; if not, see:

        https://www.gnu.org/licenses/old-licenses/lgpl-2.1.txt
*/
#include "eh-printf.h"
#include "eh-printf-private.h"
#include "eh-sys-context.h"

#if HAVE_STDINT_H
#include <stdint.h>
#endif

int eh_snprintf(char *dest, size_t size, const char *format, ...)
{
	va_list ap;
	int rv;
	va_start(ap, format);
	rv = eh_vsnprintf(dest, size, format, ap);
	va_end(ap);
	return rv;
}

int eh_vsnprintf(char *dest, size_t size, const char *format, va_list ap)
{
	struct buf_context ctx;

	/* huh? */
	if (dest == NULL || size < 1) {
		return size;
	}

	dest[0] = '\0';

	ctx.str = dest;
	ctx.len = size;
	ctx.used = 0;

	return eh_vprintf_ctx(eh_buf_output_char, eh_buf_output_str, &ctx,
			      format, ap);
}

int eh_printf(const char *format, ...)
{
	va_list ap;
	int rv;
	va_start(ap, format);
	rv = eh_vprintf(format, ap);
	va_end(ap);
	return rv;

}

int eh_vprintf(const char *format, va_list ap)
{
	int rv;
	void *ctx;

	ctx = start_sys_printf_context();

	rv = eh_vprintf_ctx(eh_sys_output_char, eh_sys_output_str, &ctx, format,
			    ap);

	end_sys_printf_context(ctx);

	return rv;
}

/* internals */
#define Eh_default_float_decimal 6
static int eh_vprintf_ctx(eh_output_char_func output_char,
			  eh_output_str_func output_str, void *ctx,
			  const char *format, va_list ap)
{
	size_t used, fmt_idx, fmt_len;
	char buf[100];
	int special, look_decimal;
	enum eh_upper upper;
	unsigned char zero_padded, alt_form;
	size_t field_size, past_decimal;

	/* supported types */
	char *s;
	char c;
	int d;
	unsigned int u;
	long l;
	unsigned long int lu;
	double f;

	upper = eh_upper;
	zero_padded = 0;
	field_size = 0;
	alt_form = 0;
	used = 0;
	fmt_idx = 0;
	fmt_len = eh_strlen(format);
	special = 0;
	look_decimal = 0;
	past_decimal = Eh_default_float_decimal;

	while (fmt_idx < fmt_len) {

		if (special) {
			switch (format[fmt_idx]) {
			case '%':
				used += output_char(ctx, '%');
				special = 0;
				break;

			case '0':
				if (field_size == 0) {
					zero_padded = 1;
					break;
				} else {
					/* fall-through */
				}
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (look_decimal) {
					past_decimal *= 10;
					past_decimal += format[fmt_idx] - '0';
				} else {
					field_size *= 10;
					field_size += format[fmt_idx] - '0';
				}
				break;

			case 'l':
				++special;	/* long long int ? */
				break;

			case 'x':
			case 'X':
				upper =
				    (format[fmt_idx] ==
				     'X') ? eh_upper : eh_lower;
				if (special > 1) {
					l = va_arg(ap, long unsigned);
				} else {
					d = va_arg(ap, unsigned);
					l = d;
				}
				eh_unsigned_long_to_ascii(buf, 100, eh_hex,
							  upper, alt_form,
							  zero_padded,
							  field_size, l);
				used += output_str(ctx, buf, eh_strlen(buf));
				special = 0;
				break;

			case 'u':
				if (special > 1) {
					lu = va_arg(ap, unsigned long int);
				} else {
					u = va_arg(ap, unsigned int);
					lu = u;
				}
				eh_unsigned_long_to_ascii(buf, 100, eh_decimal,
							  eh_lower, alt_form,
							  zero_padded,
							  field_size, lu);
				used += output_str(ctx, buf, eh_strlen(buf));
				special = 0;
				break;

			case 'i':
			case 'd':
				if (special > 1) {
					l = va_arg(ap, long int);
				} else {
					d = va_arg(ap, int);
					l = d;
				}
				eh_long_to_ascii(buf, 100, eh_decimal, alt_form,
						 zero_padded, field_size, l);
				used += output_str(ctx, buf, eh_strlen(buf));
				special = 0;
				break;

			case 'c':
				c = (char)va_arg(ap, int);
				used += output_char(ctx, c);
				special = 0;
				break;

			case 's':
				s = (char *)va_arg(ap, char *);
				used +=
				    eh_append(output_char, output_str, ctx,
					      field_size, s);
				special = 0;
				break;

			case 'f':
				f = (double)va_arg(ap, double);
				eh_double_to_ascii(buf, 100, eh_decimal,
						   alt_form, zero_padded,
						   field_size, past_decimal, f);
				used += output_str(ctx, buf, eh_strlen(buf));
				special = 0;
				break;

			case '.':
				past_decimal = 0;
				look_decimal = 1;
				break;

			case '#':
				alt_form = 1;
				break;

			default:
				/* unhandled */
				used += output_char(ctx, '%');
				if (alt_form) {
					used += output_char(ctx, '#');
				}
				if (zero_padded) {
					used += output_char(ctx, '0');
				}
				l = field_size;
				eh_long_to_ascii(buf, 100, eh_decimal, 0,
						 0, 0, field_size);
				used += output_str(ctx, buf, eh_strlen(buf));
				used += output_char(ctx, format[fmt_idx]);

				special = 0;
				break;
			}
			++fmt_idx;
			if (!special) {
				zero_padded = 0;
				field_size = 0;
				alt_form = 0;
				look_decimal = 0;
				upper = eh_upper;
				past_decimal = Eh_default_float_decimal;
			}
		} else {
			if (format[fmt_idx] == '%') {
				special = 1;
			} else {
				used += output_char(ctx, format[fmt_idx]);
			}
			++fmt_idx;
		}
	}
	return used;
}

#undef Eh_default_float_decimal

static size_t eh_buf_output_char(void *ctx, char c)
{
	struct buf_context *buf;

	buf = (struct buf_context *)ctx;
	if (buf->used < (buf->len - 1)) {
		buf->str[buf->used++] = c;
		buf->str[buf->used] = '\0';
		return 1;
	}
	return 0;
}

static size_t eh_buf_output_str(void *ctx, const char *str, size_t len)
{
	struct buf_context *buf;
	size_t i;

	buf = (struct buf_context *)ctx;
	i = 0;

	/* not enough space for data, bail out! */
	if (len >= ((buf->len - 1) - buf->used)) {
		/* we don't know what to write, fill with "?" */
		for (i = 0; buf->used < (buf->len - 1); ++i) {
			buf->str[buf->used++] = '?';
		}
	} else {
		for (i = 0; i < len; ++i) {
			buf->str[buf->used++] = str[i];
		}
	}

	/* always null terminate */
	buf->str[buf->used] = '\0';
	return i;
}

static size_t eh_append(eh_output_char_func output_char,
			eh_output_str_func output_str, void *ctx,
			size_t field_size, const char *str)
{
	size_t used, i, s_len;

	used = 0;

	if (!str) {
		str = "(null)";
	}

	s_len = eh_strlen(str);
	if (s_len > field_size) {
		field_size = s_len;
	}

	if (s_len < field_size) {
		for (i = 0; i < (field_size - s_len); ++i) {
			used += output_char(ctx, ' ');
		}
	}

	used += output_str(ctx, str, eh_strlen(str));

	return used;
}

/*
Returns the number of bytes in the string, excluding the terminating
null byte ('\0').
*/
static size_t eh_strlen(const char *str)
{
	size_t i;

	if (str == NULL) {
		return 0;
	}

	i = 0;
	while (*(str + i) != '\0') {
		++i;
	}
	return i;
}

static size_t eh_long_to_ascii(char *dest, size_t dest_size, enum eh_base base,
			       unsigned char alt_form,
			       unsigned char zero_padded, size_t field_size,
			       long val)
{
	unsigned char was_negative;

	if (val < 0 && base == eh_decimal) {
		was_negative = 1;
		val = -val;
	} else {
		was_negative = 0;
	}

	return eh_unsigned_long_to_ascii_inner(dest, dest_size, base, eh_upper,
					       alt_form,
					       zero_padded, field_size,
					       was_negative,
					       (unsigned long int)val);
}

static size_t eh_unsigned_long_to_ascii(char *dest, size_t dest_size,
					enum eh_base base, enum eh_upper upper,
					unsigned char alt_form,
					unsigned char zero_padded,
					size_t field_size, unsigned long val)
{
	unsigned char was_negative = 0;

	return eh_unsigned_long_to_ascii_inner(dest, dest_size, base, upper,
					       alt_form,
					       zero_padded, field_size,
					       was_negative,
					       (unsigned long int)val);
}

#define EH_LONG_BASE2_ASCII_BUF_SIZE \
	((EH_CHAR_BIT * sizeof(unsigned long int)) + 1 + 2 + 1)

static size_t eh_unsigned_long_to_ascii_inner(char *dest, size_t dest_size,
					      enum eh_base base,
					      enum eh_upper upper,
					      unsigned char alt_form,
					      unsigned char zero_padded,
					      size_t field_size,
					      unsigned char was_negative,
					      unsigned long v)
{
	size_t i, j, extra;
	unsigned long int d, b;
	char a;
	char reversed_buf[EH_LONG_BASE2_ASCII_BUF_SIZE];

	/* huh? */
	if (dest == NULL || dest_size < 2) {
		if (dest && dest_size) {
			dest[0] = '\0';
		}
		return 0;
	}
	/* bogus input, I guess we fix it? */
	if (field_size >= dest_size) {
		field_size = (dest_size - 1);
	}

	a = upper ? 'A' : 'a';
	b = ((unsigned long int)base);

	i = 0;
	while (v > 0) {
		d = v % b;
		v = v / b;
		if (d < 10) {
			reversed_buf[i++] = '0' + d;
		} else {
			reversed_buf[i++] = a + (d - 10);
		}
	}

	/* If the field size was not specified (zero), or the value is
	   wider than the specified field width, then the field is
	   expanded to contain the value. */
	if (field_size < i) {
		field_size = i;
	}

	j = 0;
	/* not enough space for data, bail out! */
	if (field_size >= dest_size) {
		/* we don't know what to write, fill with "?" */
		while (j < (dest_size - 1)) {
			dest[j++] = '?';
		}
		dest[j] = '\0';
		return j;
	}

	/* fill padding to right justify */
	if (zero_padded && base == eh_decimal && was_negative) {
		dest[j++] = '-';
	}
	if (zero_padded && base == eh_hex && alt_form) {
		dest[j++] = '0';
		dest[j++] = (upper == eh_upper) ? 'X' : 'x';
	}
	extra = (alt_form && base == eh_hex) ? 0 : 0;
	while (j < (field_size - (i + extra))) {
		dest[j++] = (zero_padded) ? '0' : ' ';
	}
	if (!zero_padded && base == eh_decimal && was_negative) {
		if (j > 0) {
			dest[j - 1] = '-';
		} else {
			dest[j++] = '-';
		}
	}
	if (!zero_padded && base == eh_hex && alt_form) {
		dest[j++] = '0';
		dest[j++] = (upper == eh_upper) ? 'X' : 'x';
	}

	/* walk the reversed_buf backwards */
	while (i) {
		dest[j++] = reversed_buf[--i];
	}

	/* NULL terminate */
	dest[j] = '\0';

	/* return characters written, excluding null character */
	return j;
}

#undef EH_LONG_BASE2_ASCII_BUF_SIZE

static double to_power(unsigned base, unsigned exp)
{
	double v;

	v = 1;
	while (exp--) {
		v *= base;
	}

	return v;
}

static int ceil_log(unsigned base, double d)
{
	int log;

	d = (d < 0.0) ? -d : d;

	if (d < 1.0 && d >= 0.5) {
		return 0;
	}

	if (d > 0.5) {
		for (log = 1; to_power(base, log) < d; ++log) ;
		return log;
	}

	for (log = 0; d < 0.5; --log) {
		d *= base;
	}

	return log;
}

/* TODO: how to #if sizeof(double) == sizeof(uint_64) anyway? */
#if 1
#define eh_double_to_fields eh_double64_endian_little_radix_2_to_fields
#endif

/* is "unsigned long" 64 bit? */
#if (ULONG_MAX > 4294967295UL)	/* unsigned long is probably 64 bit */
#define eh_sign_mask 0x8000000000000000UL
#define eh_rexp_mask 0x07FFUL
#define eh_mant_mask 0x000FFFFFFFFFFFFFUL
#else /* we need LONG LONG */
#define eh_sign_mask 0x8000000000000000ULL
#define eh_rexp_mask 0x07FFULL
#define eh_mant_mask 0x000FFFFFFFFFFFFFULL
#endif
static void eh_double64_endian_little_radix_2_to_fields(double d,
							uint8_t *sign,
							int16_t *exponent,
							uint64_t *fraction)
{
	union eh_float64_u {
		double d;
		uint64_t ul;
	} pun_f;
	int16_t raw_exp;
	uint64_t d_ui64;

	pun_f.d = d;
	d_ui64 = pun_f.ul;

	*sign = (d_ui64 & eh_sign_mask) ? 1U : 0U;
	raw_exp = (uint16_t)(d_ui64 >> 52U & eh_rexp_mask);
	*exponent = ((int16_t)raw_exp) - 1023L;
	*fraction = d_ui64 & eh_mant_mask;
}

#undef eh_sign_mask
#undef eh_rexp_mask
#undef eh_mant_mask

static size_t eh_double_to_ascii(char *buf, size_t len, enum eh_base base,
				 unsigned char alt_form,
				 unsigned char zero_padded, size_t field_size,
				 size_t past_decimal, double f)
{
	size_t u, w, digits, extra;
	int i;
	uint8_t c, sign;
	int16_t exponent, exp_base;
	uint64_t fraction;
	double x, y;

	if (!buf) {
		return 0;
	}

	/* NULL-padding just makes debug easier */
	for (u = 0; u < len; ++u) {
		buf[u] = '\0';
	}

	eh_double_to_fields(f, &sign, &exponent, &fraction);

	w = 0;
	if (sign) {
		f = (-f);
	}

	if (exponent == 0x400) {
		if (sign) {
			if (w < len) {
				buf[w++] = '-';
			}
		}
		if (fraction) {
			if (w < len) {
				buf[w++] = 'n';
			}
			if (w < len) {
				buf[w++] = 'a';
			}
			if (w < len) {
				buf[w++] = 'n';
			}
		} else {
			if (w < len) {
				buf[w++] = 'i';
			}
			if (w < len) {
				buf[w++] = 'n';
			}
			if (w < len) {
				buf[w++] = 'f';
			}
		}
		return w;
	}

	/* crude rounding */
	f = f + (0.5 / to_power(base, past_decimal));

	exp_base = (int16_t)ceil_log(base, f);
	extra = alt_form ? 0 : 0;
	if (exp_base > 0) {
		digits = (sign + exp_base + 1 + past_decimal) + extra;
	} else {
		digits = (sign + 1 + 1 + past_decimal) + extra;
	}
	if ((field_size > 0) && (digits < field_size)) {
		if (zero_padded && sign) {
			if (w < len) {
				buf[w++] = '-';
			}
		}
		for (u = 0; u < (field_size - digits); ++u) {
			if (w < len) {
				buf[w++] = zero_padded ? '0' : ' ';
			}
		}
		if ((!zero_padded) && sign) {
			if (w < len) {
				buf[w++] = '-';
			}
		}
	} else if (sign) {
		if (w < len) {
			buf[w++] = '-';
		}
	}

	if (exp_base > 0) {
		for (i = 0; i < exp_base; ++i) {
			x = to_power(base, ((int)exp_base) - (1 + i));
			y = (f / x);
			c = (uint8_t)y;
			c = c % base;	/* should be a NO-OP */
			if (w < len) {
				buf[w++] = '0' + c;
			}
			f = f - (c * x);
		}
	} else {
		if (w < len) {
			buf[w++] = '0';
		}
	}
	if (past_decimal) {
		if (w < len) {
			buf[w++] = '.';
		}
		for (u = 0; u < past_decimal; ++u) {
			f *= base;
			c = (uint8_t)f;
			c = c % base;	/* should be a NO-OP */
			if (w < len) {
				buf[w++] = '0' + c;
			}
			f = (f - c);
		}
	}

	if (w < len) {
		buf[w] = '\0';
	}

	return w;
}
