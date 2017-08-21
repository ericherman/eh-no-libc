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

int isalpha(int c);
int isalnum(int c);
int isascii(int c);
int isdigit(int c);
int islower(int c);
int isupper(int c);
int isspace(int c);
int isblank(int c);
int isxdigit(int c);

int toupper(int c);
int tolower(int c);

#endif /* _CTYPE_H */
