/*
eh-parse-float.h - headers for float field extraction
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

#ifndef EH_PARSE_FLOAT_H
#define EH_PARSE_FLOAT_H

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

#if (!defined eh_double_to_fields) \
 && (DBL_MAX_EXP == 1024) \
 && (DBL_MANT_DIG == 53) \
 && (FLT_RADIX == 2)
#define eh_double_to_fields eh_float64_radix_2_to_fields
#endif

#if (!defined eh_double_to_fields) \
 && (DBL_MAX_EXP == 128) \
 && (DBL_MANT_DIG == 24) \
 && (FLT_RADIX == 2)
#define eh_double_to_fields eh_float32_radix_2_to_fields
#endif

#if (!defined eh_double_to_fields)	/* wild guess */
#define eh_double_to_fields eh_float64_radix_2_to_fields
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

#if (!defined EH_SKIP_FLOAT64)
void eh_float64_radix_2_to_fields(Eh_float64 d, uint8_t *sign,
				  int16_t *exponent, uint64_t *fraction);
#endif

#if (!defined EH_SKIP_FLOAT32)
void eh_float32_radix_2_to_fields(Eh_float32 d, uint8_t *sign,
				  int16_t *exponent, uint64_t *fraction);
#endif

#ifdef __cplusplus
}
#endif

#endif /* EH_PARSE_FLOAT_H */
