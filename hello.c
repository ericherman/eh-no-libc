#include <unistd.h>

#ifdef __WORDSIZE
#if ( __WORDSIZE == 64 )
#define uptr unsigned long
#elif ( __WORDSIZE == 32 )
#define uptr unsigned int
#endif
#endif

uptr eh_strlen(char const* str)
{
	char const* p;
	for (p = str; *p; ++p);
	return p - str;
}

int main(int argc, char **argv)
{
	const char *str;

	str = "hello, world\n";
	write(1, str, eh_strlen(str));

	return 0;
}
