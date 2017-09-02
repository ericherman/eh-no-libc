/*
eh-printf-parse-float.h - headers for float field extraction
Copyright (C) 2017 Eric Herman

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

#ifndef EH_PRINTF_PARSE_FLOAT_H
#define EH_PRINTF_PARSE_FLOAT_H

#ifdef __cplusplus
extern "C" {
#endif

#if HAVE_CONFIG_H
#include "config.h"
#endif

#if HAVE_STDINT_H
#include <stdint.h>
#endif

#if HAVE_FLOAT_H
#include <float.h>
#endif

/* intended to match defines in math.h */
#define EH_FP_NAN 0
#define EH_FP_INFINITE 1
#define EH_FP_ZERO 2
#define EH_FP_SUBNORMAL 3
#define EH_FP_NORMAL 4

/*
float32	Sign	Exponent	Fraction
float32	1 [31]	8 [30-23]	23 [22-00]
float32 SEEEEEEE EFFFFFFF FFFFFFFF FFFFFFFF

float64	Sign	Exponent	Fraction
float64 1 [63]	11 [62-52]	52 [51-00]
float64 SEEEEEEE EEEEFFFF FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF FFFFFFFF
*/

#define Eh_float32_exp_max 127
#define Eh_float32_exp_inf_nan 128
#define Eh_float64_exp_max 1023L
#define Eh_float64_exp_inf_nan 1024L

#if (!defined eh_double_to_fields) \
 && (DBL_MAX_EXP == 1024) \
 && (DBL_MANT_DIG == 53) \
 && (FLT_RADIX == 2)
#define Eh_double_exp_max	Eh_float64_exp_max
#define Eh_double_exp_inf_nan	Eh_float64_exp_inf_nan
#define eh_double_to_fields	eh_float64_radix_2_to_fields
#define eh_double_classify_f	eh_float64_classify_f
#define eh_double_classify	eh_float64_classify
#endif

#if (!defined eh_double_to_fields) \
 && (DBL_MAX_EXP == 128) \
 && (DBL_MANT_DIG == 24) \
 && (FLT_RADIX == 2)
#define Eh_double_exp_max	Eh_float32_exp_max
#define Eh_double_exp_inf_nan	Eh_float32_exp_inf_nan
#define eh_double_to_fields	eh_float32_radix_2_to_fields
#define eh_double_classify_f	eh_float32_classify_f
#define eh_double_classify	eh_float32_classify
#endif

#if (!defined eh_double_to_fields)	/* wild guess */
#define Eh_double_exp_max	Eh_float64_exp_max
#define Eh_double_exp_inf_nan	Eh_float64_exp_inf_nan
#define eh_double_to_fields	eh_float64_radix_2_to_fields
#define eh_double_classify_f	eh_float64_classify_f
#define eh_double_classify	eh_float64_classify
#endif

#if (!defined EH_HAVE_FLOAT32) \
 && (FLT_MAX_EXP == 128) \
 && (FLT_MANT_DIG == 24)
#define EH_HAVE_FLOAT32 1
typedef float Eh_float32;
#endif

#if (!defined EH_HAVE_FLOAT32) \
 && (DBL_MAX_EXP == 128) \
 && (DBL_MANT_DIG == 24)
#define EH_HAVE_FLOAT32 1
typedef double Eh_float32;
#endif

#if (!defined EH_HAVE_FLOAT32) \
 && (LDBL_MAX_EXP == 128) \
 && (LDBL_MANT_DIG == 24)
#define EH_HAVE_FLOAT32 1
typedef long double Eh_float32;
#endif

#if (!defined EH_HAVE_FLOAT32)	/* wild guess */
typedef float Eh_float32;
#endif

#if (!defined EH_HAVE_FLOAT64) \
 && (DBL_MAX_EXP == 1024) \
 && (DBL_MANT_DIG == 53)
#define EH_HAVE_FLOAT64 1
typedef double Eh_float64;
#endif

#if (!defined EH_HAVE_FLOAT64) \
 && (FLT_MAX_EXP == 1024) \
 && (FLT_MANT_DIG == 53)
#define EH_HAVE_FLOAT64 1
typedef float Eh_float64;
#endif

#if (!defined EH_HAVE_FLOAT64) \
 && (LDBL_MAX_EXP == 1024) \
 && (LDBL_MANT_DIG == 53)
#define EH_HAVE_FLOAT64 1
typedef long double Eh_float64;
#endif

#if (!defined EH_HAVE_FLOAT64)	/* wild guess */
typedef double Eh_float64;
#endif

#if (!defined EH_PRINTF_SKIP_FLOAT64)
int eh_float64_radix_2_to_fields(Eh_float64 d, uint8_t *sign,
				 int16_t *exponent, uint64_t *fraction);
int eh_float64_classify_f(int16_t exponent, uint64_t fraction);
int eh_float64_classify(Eh_float64 d);
#endif

#if (!defined EH_PRINTF_SKIP_FLOAT32)
int eh_float32_radix_2_to_fields(Eh_float32 d, uint8_t *sign,
				 int16_t *exponent, uint64_t *fraction);
int eh_float32_classify_f(int16_t exponent, uint32_t fraction);
int eh_float32_classify(Eh_float32 f);
#endif

#ifdef __cplusplus
}
#endif

#endif /* EH_PRINTF_PARSE_FLOAT_H */
