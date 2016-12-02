#include "ehlibc.h"

/* int main(int argc, char **argv) */
int main(void)
{
	const char *str;

	str = "hello, world\n";
	write(1, str, strlen(str));

	return 0;
}
