#include <unistd.h>

size_t eh_strlen(char const* str)
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
