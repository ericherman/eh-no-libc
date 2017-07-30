/*
eh-parse-float.c - extract fields from a floating point variable
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
#include "eh-parse-float.h"

#if (!defined EH_SKIP_FLOAT64)
#if (EH_LONG_IS_AT_LEAST_64_BIT)
#define eh_sign_mask 0x8000000000000000UL
#define eh_rexp_mask 0x7FF0000000000000UL
#define eh_frac_mask 0x000FFFFFFFFFFFFFUL
#else /* we need LONG LONG */
#define eh_sign_mask 0x8000000000000000ULL
#define eh_rexp_mask 0x7FF0000000000000ULL
#define eh_frac_mask 0x000FFFFFFFFFFFFFULL
#endif
void eh_float64_radix_2_to_fields(Eh_float64 d, uint8_t *sign,
				  int16_t *exponent, uint64_t *fraction)
{
	union eh_float64_u {
		Eh_float64 d;
		uint64_t ul;
	} pun_f;
	int16_t raw_exp;
	uint64_t d_u64;

	pun_f.d = d;
	d_u64 = pun_f.ul;

	*sign = (d_u64 & eh_sign_mask) ? 1U : 0U;
	raw_exp = ((d_u64 & eh_rexp_mask) >> 52UL);
	*exponent = raw_exp - 1023L;
	*fraction = d_u64 & eh_frac_mask;
}

#undef eh_sign_mask
#undef eh_rexp_mask
#undef eh_frac_mask
#endif

#if (!defined EH_SKIP_FLOAT32)
void eh_float32_radix_2_to_fields(Eh_float32 d, uint8_t *sign,
				  int16_t *exponent, uint64_t *fraction)
{
	union eh_float32_u {
		Eh_float32 d;
		uint32_t ul;
	} pun_f;
	uint32_t sign_mask, rexp_mask, frac_mask;
	uint16_t raw_exp;
	uint32_t d_u32;

	sign_mask = 0x80000000UL;
	rexp_mask = 0x7F800000UL;
	frac_mask = 0x007FFFFFUL;

	pun_f.d = d;
	d_u32 = pun_f.ul;

	*sign = (d_u32 & sign_mask) ? 1U : 0U;
	raw_exp = ((d_u32 & rexp_mask) >> 23U);
	*exponent = raw_exp - 127;
	*fraction = d_u32 & frac_mask;
}
#endif
