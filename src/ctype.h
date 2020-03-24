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
#ifndef _CTYPE_H
#define _CTYPE_H	1

#define isalnum(c) ehnlc_isalnum(c)
int ehnlc_isalnum(int c);

#define isalpha(c) ehnlc_isalpha(c)
int ehnlc_isalpha(int c);

#define isascii(c) ehnlc_isascii(c)
int ehnlc_isascii(int c);

#define isblank(c) ehnlc_isblank(c)
int ehnlc_isblank(int c);

#define iscntrl(c) ehnlc_iscntrl(c)
int ehnlc_iscntrl(int c);

#define isdigit(c) ehnlc_isdigit(c)
int ehnlc_isdigit(int c);

#define isgraph(c) ehnlc_isgraph(c)
int ehnlc_isgraph(int c);

#define islower(c) ehnlc_islower(c)
int ehnlc_islower(int c);

#define isprint(c) ehnlc_isprint(c)
int ehnlc_isprint(int c);

#define ispunct(c) ehnlc_ispunct(c)
int ehnlc_ispunct(int c);

#define isspace(c) ehnlc_isspace(c)
int ehnlc_isspace(int c);

#define isupper(c) ehnlc_isupper(c)
int ehnlc_isupper(int c);

#define isxdigit(c) ehnlc_isxdigit(c)
int ehnlc_isxdigit(int c);

#define tolower(c) ehnlc_tolower(c)
int ehnlc_tolower(int c);

#define toupper(c) ehnlc_toupper(c)
int ehnlc_toupper(int c);

#endif /* _CTYPE_H */
