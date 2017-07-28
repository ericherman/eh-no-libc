#include "string.h"

size_t strlen(char const *str)
{
	char const *p;
	for (p = str; *p; ++p) ;
	return p - str;
}
