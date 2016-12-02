#include "ehlibc.h"

/* int main(int argc, char **argv) */
int main(void)
{
	const char *str;

	str = "hello, world\n";
	puts(str);

	return 0;
}
