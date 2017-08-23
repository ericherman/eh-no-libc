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
#define PRId64		"ld"

#define PRIdLEAST8	"d"
#define PRIdLEAST16	"d"
#define PRIdLEAST32	"d"
#define PRIdLEAST64	"ld"

#define PRIdFAST8	"d"
#define PRIdFAST16	"ld"
#define PRIdFAST32	"ld"
#define PRIdFAST64	"ld"

#define PRIi8		"i"
#define PRIi16		"i"
#define PRIi32		"i"
#define PRIi64		"li"

#define PRIiLEAST8	"i"
#define PRIiLEAST16	"i"
#define PRIiLEAST32	"i"
#define PRIiLEAST64	"li"

#define PRIiFAST8	"i"
#define PRIiFAST16	"li"
#define PRIiFAST32	"li"
#define PRIiFAST64	"li"

#define PRIo8		"o"
#define PRIo16		"o"
#define PRIo32		"o"
#define PRIo64		"lo"

#define PRIoLEAST8	"o"
#define PRIoLEAST16	"o"
#define PRIoLEAST32	"o"
#define PRIoLEAST64	"lo"

#define PRIoFAST8	"o"
#define PRIoFAST16	"lo"
#define PRIoFAST32	"lo"
#define PRIoFAST64	"lo"

#define PRIu8		"u"
#define PRIu16		"u"
#define PRIu32		"u"
#define PRIu64		"lu"

#define PRIuLEAST8	"u"
#define PRIuLEAST16	"u"
#define PRIuLEAST32	"u"
#define PRIuLEAST64	"lu"

#define PRIuFAST8	"u"
#define PRIuFAST16	"lu"
#define PRIuFAST32	"lu"
#define PRIuFAST64	"lu"

#define PRIx8		"x"
#define PRIx16		"x"
#define PRIx32		"x"
#define PRIx64		"lx"

#define PRIxLEAST8	"x"
#define PRIxLEAST16	"x"
#define PRIxLEAST32	"x"
#define PRIxLEAST64	"lx"

#define PRIxFAST8	"x"
#define PRIxFAST16	"lx"
#define PRIxFAST32	"lx"
#define PRIxFAST64	"lx"

#define PRIX8		"X"
#define PRIX16		"X"
#define PRIX32		"X"
#define PRIX64		"lX"

#define PRIXLEAST8	"X"
#define PRIXLEAST16	"X"
#define PRIXLEAST32	"X"
#define PRIXLEAST64	"lX"

#define PRIXFAST8	"X"
#define PRIXFAST16	"lX"
#define PRIXFAST32	"lX"
#define PRIXFAST64	"lX"

#define PRIdMAX	"ld"
#define PRIiMAX	"li"
#define PRIoMAX	"lo"
#define PRIuMAX	"lu"
#define PRIxMAX	"lx"
#define PRIXMAX	"lX"

#define PRIdPTR	"ld"
#define PRIiPTR	"li"
#define PRIoPTR	"lo"
#define PRIuPTR	"lu"
#define PRIxPTR	"lx"
#define PRIXPTR	"lX"

#define SCNd8		"hhd"
#define SCNd16		"hd"
#define SCNd32		"d"
#define SCNd64		"ld"

#define SCNdLEAST8	"hhd"
#define SCNdLEAST16	"hd"
#define SCNdLEAST32	"d"
#define SCNdLEAST64	"ld"

#define SCNdFAST8	"hhd"
#define SCNdFAST16	"ld"
#define SCNdFAST32	"ld"
#define SCNdFAST64	"ld"

#define SCNi8		"hhi"
#define SCNi16		"hi"
#define SCNi32		"i"
#define SCNi64		"li"

#define SCNiLEAST8	"hhi"
#define SCNiLEAST16	"hi"
#define SCNiLEAST32	"i"
#define SCNiLEAST64	"li"

#define SCNiFAST8	"hhi"
#define SCNiFAST16	"li"
#define SCNiFAST32	"li"
#define SCNiFAST64	"li"

#define SCNu8		"hhu"
#define SCNu16		"hu"
#define SCNu32		"u"
#define SCNu64		"lu"

#define SCNuLEAST8	"hhu"
#define SCNuLEAST16	"hu"
#define SCNuLEAST32	"u"
#define SCNuLEAST64	"lu"

#define SCNuFAST8	"hhu"
#define SCNuFAST16	"lu"
#define SCNuFAST32	"lu"
#define SCNuFAST64	"lu"

#define SCNo8		"hho"
#define SCNo16		"ho"
#define SCNo32		"o"
#define SCNo64		"lo"

#define SCNoLEAST8	"hho"
#define SCNoLEAST16	"ho"
#define SCNoLEAST32	"o"
#define SCNoLEAST64	"lo"

#define SCNoFAST8	"hho"
#define SCNoFAST16	"lo"
#define SCNoFAST32	"lo"
#define SCNoFAST64	"lo"

#define SCNx8		"hhx"
#define SCNx16		"hx"
#define SCNx32		"x"
#define SCNx64		"lx"

#define SCNxLEAST8	"hhx"
#define SCNxLEAST16	"hx"
#define SCNxLEAST32	"x"
#define SCNxLEAST64	"lx"

#define SCNxFAST8	"hhx"
#define SCNxFAST16	"lx"
#define SCNxFAST32	"lx"
#define SCNxFAST64	"lx"

#define SCNdMAX	"ld"
#define SCNiMAX	"li"
#define SCNoMAX	"lo"
#define SCNuMAX	"lu"
#define SCNxMAX	"lx"

#define SCNdPTR	"ld"
#define SCNiPTR	"li"
#define SCNoPTR	"lo"
#define SCNuPTR	"lu"
#define SCNxPTR	"lx"

#endif /* INTTYPES_H */
