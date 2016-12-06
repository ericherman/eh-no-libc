#include "ehlibc.h"

/* int main(int argc, char **argv) */
int main(void)
{
	stat_info_s si;

	if (stat("/etc/hosts", &si) == 0) {
		write(stdout, &si, sizeof(stat_info_s));
	}

	return 0;
}
