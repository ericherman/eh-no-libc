/*
efloat.c: Embedable Float manipulation library
Copyright (C) 2017 Eric Herman

https://github.com/ericherman/libefloat

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later
version.
*/

#include <efloat.h>

#ifndef eprintf2
#if HAVE_STDIO_H
#include <stdio.h>
#define eprintf2(fmt, a, b) fprintf(stderr, fmt, a, b)
#else
#define eprintf2(fmt, a, b)	/* NOOP */
#endif
#endif

#ifndef HAVE_MEMCPY
#define HAVE_MEMCPY 0
#endif
#ifndef HAVE_STRING_H
#define HAVE_STRING_H 0
#endif
#if (HAVE_MEMCPY && HAVE_STRING_H)
#include <string.h>		/* memcpy */
#endif
/*
   If no memcpy(), then we can use type-punning via a union.
   The C standard reads ambuguously to me as to whether this is strictly
   conforming, but I know of no compilers which do not support it.

   The calls to memcpy() here are probably going to be removed by gcc:
   gcc output: https://godbolt.org/g/hiX8oL
*/

#if HAVE_ERRNO_H
#include <errno.h>
#define seterrnoinval() do { errno = EINVAL; } while (0)
#endif

#ifndef seterrnoinval
#define seterrnoinval()		/* NOOP */
#endif

#if ((defined efloat32_exists) && (efloat32_exists))
#if HAVE_MEMCPY
efloat32 uint32_to_efloat32(uint32_t u)
{
	efloat32 f;
	memcpy(&f, &u, sizeof(efloat32));
	return f;
}

uint32_t efloat32_to_uint32(efloat32 f)
{
	uint32_t u;
	memcpy(&u, &f, sizeof(uint32_t));
	return u;
}

#ifndef SKIP_EFLOAT_SIGNED_INTS
efloat32 int32_to_efloat32(int32_t i)
{
	efloat32 f;
	memcpy(&f, &i, sizeof(efloat32));
	return f;
}

int32_t efloat32_to_int32(efloat32 f)
{
	int32_t i;
	memcpy(&i, &f, sizeof(int32_t));
	return i;
}
#endif /* SKIP_EFLOAT_SIGNED_INTS */
#else /* HAVE_MEMCPY */

efloat32 uint32_to_efloat32(uint32_t u)
{
	union efloat32_u {
		efloat32 f;
		uint32_t u;
	} pun;
	pun.u = u;
	return pun.f;
}

uint32_t efloat32_to_uint32(efloat32 f)
{
	union efloat32_u {
		efloat32 f;
		uint32_t u;
	} pun;
	pun.f = f;
	return pun.u;
}

#ifndef SKIP_EFLOAT_SIGNED_INTS
efloat32 int32_to_efloat32(int32_t i)
{
	union efloat32_u {
		efloat32 f;
		int32_t i;
	} pun;
	pun.i = i;
	return pun.f;
}

int32_t efloat32_to_int32(efloat32 f)
{
	union efloat32_u {
		efloat32 f;
		int32_t i;
	} pun;
	pun.f = f;
	return pun.i;
}
#endif /* SKIP_EFLOAT_SIGNED_INTS */
#endif /* HAVE_MEMCPY */

enum efloat_class efloat32_classify(efloat32 f)
{
	struct efloat32_fields fields;

	fields.sign = 0;
	fields.exponent = 0;
	fields.significand = 0;
	return efloat32_radix_2_to_fields(f, &fields);
}

enum efloat_class efloat32_radix_2_to_fields(efloat32 f,
					     struct efloat32_fields *fields)
{
	uint32_t u32, raw_exp;

	u32 = efloat32_to_uint32(f);

	fields->sign = (u32 & efloat32_r2_sign_mask) ? 1U : 0U;

	raw_exp = (u32 & efloat32_r2_rexp_mask);
	raw_exp = (raw_exp >> efloat32_r2_exp_shift);
	fields->exponent = (raw_exp - efloat32_r2_exp_max);

	fields->significand = u32 & efloat32_r2_signif_mask;

	if (fields->exponent == efloat32_r2_exp_inf_nan) {
		if (fields->significand) {
			/* +/- nan */
			return ef_nan;
		} else {
			/* +/- inf */
			return ef_inf;
		}
	}

	if ((fields->significand == 0)
	    && (fields->exponent == efloat32_r2_exp_min)) {
		/* zero or -zero */
		return ef_zero;
	}

	if (fields->exponent == efloat32_r2_exp_min) {
		/* subnormal */
		return ef_subnorm;
	}

	return ef_normal;
}

efloat32 efloat32_radix_2_from_fields(struct efloat32_fields fields,
				      enum efloat_class *efloat32class)
{
	efloat32 f;
	uint32_t u32, raw_exp;
	struct efloat32_fields f2;
	int err;

	err = 0;
	f2.sign = fields.sign ? 1 : 0;

	if (fields.exponent > efloat32_r2_exp_inf_nan
	    || fields.exponent < efloat32_r2_exp_min) {
		seterrnoinval();
		err = 1;
		fields.exponent = efloat32_r2_exp_inf_nan;
	}
	raw_exp = (fields.exponent + efloat32_r2_exp_max);

	if (fields.significand !=
	    (fields.significand & efloat32_r2_signif_mask)) {
		seterrnoinval();
		err = 1;
		fields.significand =
		    (fields.significand & efloat32_r2_signif_mask);
	}

	u32 = (fields.sign ? efloat32_r2_sign_mask : 0)
	    | (raw_exp << efloat32_r2_exp_shift)
	    | fields.significand;

	f = uint32_to_efloat32(u32);
	if (efloat32class) {
		*efloat32class = efloat32_radix_2_to_fields(f, &f2);
	} else {
		efloat32_radix_2_to_fields(f, &f2);
	}
	if (!err) {
		if ((!fields.sign) != (!f2.sign)) {
			seterrnoinval();
			eprintf2("sign %u != %u\n",
				 (unsigned)fields.sign, (unsigned)f2.sign);
		}
		if (fields.exponent != f2.exponent) {
			seterrnoinval();
			eprintf2("exponent %d != %d\n",
				 (int)fields.exponent, (int)f2.exponent);
		}
		if (fields.significand != f2.significand) {
			seterrnoinval();
			eprintf2("significand %lu != %lu\n",
				 (unsigned long)fields.significand,
				 (unsigned long)fields.significand);
		}
	}
	return f;
}
#endif

#if ((defined efloat64_exists) && (efloat64_exists))
#if HAVE_MEMCPY
efloat64 uint64_to_efloat64(uint64_t u)
{
	efloat64 f;
	memcpy(&f, &u, sizeof(efloat64));
	return f;
}

uint64_t efloat64_to_uint64(efloat64 f)
{
	uint64_t u;
	memcpy(&u, &f, sizeof(uint64_t));
	return u;
}

#ifndef SKIP_EFLOAT_SIGNED_INTS
efloat64 int64_to_efloat64(int64_t i)
{
	efloat64 f;
	memcpy(&f, &i, sizeof(efloat64));
	return f;
}

int64_t efloat64_to_int64(efloat64 f)
{
	int64_t i;
	memcpy(&i, &f, sizeof(int64_t));
	return i;
}
#endif /* SKIP_EFLOAT_SIGNED_INTS */
#else /* HAVE MEMCPY */
efloat64 uint64_to_efloat64(uint64_t u)
{
	union efloat64_u {
		efloat64 f;
		uint64_t u;
	} pun;
	pun.u = u;
	return pun.f;
}

uint64_t efloat64_to_uint64(efloat64 f)
{
	union efloat64_u {
		efloat64 f;
		uint64_t u;
	} pun;
	pun.f = f;
	return pun.u;
}

#ifndef SKIP_EFLOAT_SIGNED_INTS
efloat64 int64_to_efloat64(int64_t i)
{
	union efloat64_u {
		efloat64 f;
		int64_t i;
	} pun;
	pun.i = i;
	return pun.f;
}

int64_t efloat64_to_int64(efloat64 f)
{
	union efloat64_u {
		efloat64 f;
		int64_t i;
	} pun;
	pun.f = f;
	return pun.i;
}
#endif /* SKIP_EFLOAT_SIGNED_INTS */
#endif /* HAVE_MEMCPY */

enum efloat_class efloat64_classify(efloat64 f)
{
	struct efloat64_fields fields;

	fields.sign = 0;
	fields.exponent = 0;
	fields.significand = 0;
	return efloat64_radix_2_to_fields(f, &fields);
}

enum efloat_class efloat64_radix_2_to_fields(efloat64 f,
					     struct efloat64_fields *fields)
{
	uint64_t u64, raw_exp;

	u64 = efloat64_to_uint64(f);

	fields->sign = (u64 & efloat64_r2_sign_mask) ? 1U : 0U;

	raw_exp = (u64 & efloat64_r2_rexp_mask);
	raw_exp = (raw_exp >> efloat64_r2_exp_shift);
	fields->exponent = (raw_exp - efloat64_r2_exp_max);

	fields->significand = u64 & efloat64_r2_signif_mask;

	if (fields->exponent == efloat64_r2_exp_inf_nan) {
		if (fields->significand) {
			/* +/- nan */
			return ef_nan;
		} else {
			/* +/- inf */
			return ef_inf;
		}
	}

	if ((fields->significand == 0)
	    && (fields->exponent == efloat64_r2_exp_min)) {
		/* zero or -zero */
		return ef_zero;
	}

	if (fields->exponent == efloat64_r2_exp_min) {
		/* subnormal */
		return ef_subnorm;
	}

	return ef_normal;
}

efloat64 efloat64_radix_2_from_fields(struct efloat64_fields fields,
				      enum efloat_class *efloat64class)
{
	efloat64 f;
	uint64_t u64, raw_exp;
	struct efloat64_fields f2;
	int err;

	err = 0;
	f2.sign = fields.sign ? 1 : 0;

	if (fields.exponent > efloat64_r2_exp_inf_nan
	    || fields.exponent < efloat64_r2_exp_min) {
		seterrnoinval();
		err = 1;
		fields.exponent = efloat64_r2_exp_inf_nan;
	}
	raw_exp = (fields.exponent + efloat64_r2_exp_max);

	if (fields.significand !=
	    (fields.significand & efloat64_r2_signif_mask)) {
		seterrnoinval();
		err = 1;
		fields.significand =
		    (fields.significand & efloat64_r2_signif_mask);
	}

	u64 = (fields.sign ? efloat64_r2_sign_mask : 0)
	    | (raw_exp << efloat64_r2_exp_shift)
	    | fields.significand;

	f = uint64_to_efloat64(u64);
	if (efloat64class) {
		*efloat64class = efloat64_radix_2_to_fields(f, &f2);
	} else {
		efloat64_radix_2_to_fields(f, &f2);
	}
	if (!err) {
		if ((!fields.sign) != (!f2.sign)) {
			seterrnoinval();
			eprintf2("sign %u != %u\n",
				 (unsigned)fields.sign, (unsigned)f2.sign);
		}
		if (fields.exponent != f2.exponent) {
			seterrnoinval();
			eprintf2("exponent %d != %d\n",
				 (int)fields.exponent, (int)f2.exponent);
		}
		if (fields.significand != f2.significand) {
			seterrnoinval();
			eprintf2("significand %lu != %lu\n",
				 (unsigned long)fields.significand,
				 (unsigned long)f2.significand);
		}
	}
	return f;
}
#endif
