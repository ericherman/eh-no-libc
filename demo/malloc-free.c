#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int i;
	int j;
	char *pointers[10];

	printf("test_checkered_alloc ...");

	for (i = 0; i < 10; i++) {
		pointers[i] = malloc(100);
		if (!pointers[i]) {
			printf("1) expected a pointer for %i\n", i);
			printf("FAIL\n");
			return 1;
		}
		for (j = 0; j < 100; j++) {
			pointers[i][j] = 1;
		}
	}
	for (i = 1; i < 10; i += 2) {
		free(pointers[i]);
	}
	for (i = 1; i < 10; i += 2) {
		pointers[i] = malloc(90);
		if (!pointers[i]) {
			printf("2) expected a pointer for %i\n", i);
			printf("FAIL\n");
			return 1;
		}
		for (j = 0; j < 90; j++) {
			pointers[i][j] = 1;
		}
	}

	printf(" ok");
	for (i = 0; i < 10; i++) {
		free(pointers[i]);
	}
	printf(".\n");
	return 0;
}
