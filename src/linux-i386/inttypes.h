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
#ifndef INTTYPES_H
#define INTTYPES_H

#define PRId8		"d"
#define PRId16		"d"
#define PRId32		"d"
#define PRId64		"lld"

#define PRIdLEAST8	"d"
#define PRIdLEAST16	"d"
#define PRIdLEAST32	"d"
#define PRIdLEAST64	"lld"

#define PRIdFAST8	"d"
#define PRIdFAST16	"d"
#define PRIdFAST32	"d"
#define PRIdFAST64	"lld"

#define PRIi8		"i"
#define PRIi16		"i"
#define PRIi32		"i"
#define PRIi64		"lli"

#define PRIiLEAST8	"i"
#define PRIiLEAST16	"i"
#define PRIiLEAST32	"i"
#define PRIiLEAST64	"lli"

#define PRIiFAST8	"i"
#define PRIiFAST16	"i"
#define PRIiFAST32	"i"
#define PRIiFAST64	"lli"

#define PRIo8		"o"
#define PRIo16		"o"
#define PRIo32		"o"
#define PRIo64		"llo"

#define PRIoLEAST8	"o"
#define PRIoLEAST16	"o"
#define PRIoLEAST32	"o"
#define PRIoLEAST64	"llo"

#define PRIoFAST8	"o"
#define PRIoFAST16	"o"
#define PRIoFAST32	"o"
#define PRIoFAST64	"llo"

#define PRIu8		"u"
#define PRIu16		"u"
#define PRIu32		"u"
#define PRIu64		"llu"

#define PRIuLEAST8	"u"
#define PRIuLEAST16	"u"
#define PRIuLEAST32	"u"
#define PRIuLEAST64	"llu"

#define PRIuFAST8	"u"
#define PRIuFAST16	"u"
#define PRIuFAST32	"u"
#define PRIuFAST64	"llu"

#define PRIx8		"x"
#define PRIx16		"x"
#define PRIx32		"x"
#define PRIx64		"llx"

#define PRIxLEAST8	"x"
#define PRIxLEAST16	"x"
#define PRIxLEAST32	"x"
#define PRIxLEAST64	"llx"

#define PRIxFAST8	"x"
#define PRIxFAST16	"x"
#define PRIxFAST32	"x"
#define PRIxFAST64	"llx"

#define PRIX8		"X"
#define PRIX16		"X"
#define PRIX32		"X"
#define PRIX64		"llX"

#define PRIXLEAST8	"X"
#define PRIXLEAST16	"X"
#define PRIXLEAST32	"X"
#define PRIXLEAST64	"llX"

#define PRIXFAST8	"X"
#define PRIXFAST16	"X"
#define PRIXFAST32	"X"
#define PRIXFAST64	"llX"

#define PRIdMAX	"lld"
#define PRIiMAX	"lli"
#define PRIoMAX	"llo"
#define PRIuMAX	"llu"
#define PRIxMAX	"llx"
#define PRIXMAX	"llX"

#define PRIdPTR	"d"
#define PRIiPTR	"i"
#define PRIoPTR	"o"
#define PRIuPTR	"u"
#define PRIxPTR	"x"
#define PRIXPTR	"X"

#define SCNd8		"hhd"
#define SCNd16		"hd"
#define SCNd32		"d"
#define SCNd64		"lld"

#define SCNdLEAST8	"hhd"
#define SCNdLEAST16	"hd"
#define SCNdLEAST32	"d"
#define SCNdLEAST64	"lld"

#define SCNdFAST8	"hhd"
#define SCNdFAST16	"d"
#define SCNdFAST32	"d"
#define SCNdFAST64	"lld"

#define SCNi8		"hhi"
#define SCNi16		"hi"
#define SCNi32		"i"
#define SCNi64		"lli"

#define SCNiLEAST8	"hhi"
#define SCNiLEAST16	"hi"
#define SCNiLEAST32	"i"
#define SCNiLEAST64	"lli"

#define SCNiFAST8	"hhi"
#define SCNiFAST16	"i"
#define SCNiFAST32	"i"
#define SCNiFAST64	"lli"

#define SCNu8		"hhu"
#define SCNu16		"hu"
#define SCNu32		"u"
#define SCNu64		"llu"

#define SCNuLEAST8	"hhu"
#define SCNuLEAST16	"hu"
#define SCNuLEAST32	"u"
#define SCNuLEAST64	"llu"

#define SCNuFAST8	"hhu"
#define SCNuFAST16	"u"
#define SCNuFAST32	"u"
#define SCNuFAST64	"llu"

#define SCNo8		"hho"
#define SCNo16		"ho"
#define SCNo32		"o"
#define SCNo64		"llo"

#define SCNoLEAST8	"hho"
#define SCNoLEAST16	"ho"
#define SCNoLEAST32	"o"
#define SCNoLEAST64	"llo"

#define SCNoFAST8	"hho"
#define SCNoFAST16	"o"
#define SCNoFAST32	"o"
#define SCNoFAST64	"llo"

#define SCNx8		"hhx"
#define SCNx16		"hx"
#define SCNx32		"x"
#define SCNx64		"llx"

#define SCNxLEAST8	"hhx"
#define SCNxLEAST16	"hx"
#define SCNxLEAST32	"x"
#define SCNxLEAST64	"llx"

#define SCNxFAST8	"hhx"
#define SCNxFAST16	"x"
#define SCNxFAST32	"x"
#define SCNxFAST64	"llx"

#define SCNdMAX	"lld"
#define SCNiMAX	"lli"
#define SCNoMAX	"llo"
#define SCNuMAX	"llu"
#define SCNxMAX	"llx"

#define SCNdPTR	"d"
#define SCNiPTR	"i"
#define SCNoPTR	"o"
#define SCNuPTR	"u"
#define SCNxPTR	"x"

#endif /* INTTYPES_H */
