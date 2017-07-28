#include "ehlibc.h"

/* int main(int argc, char **argv) */
int main(void)
{
	struct stat si;

	if (stat("/etc/hosts", &si) == 0) {
		write(stdout, &si, sizeof(struct stat));
	}

	return 0;
}
