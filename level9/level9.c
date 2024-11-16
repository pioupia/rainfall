#include <stdlib.h>

void	write_addr(int *ptr, int number) {
	*ptr = 0x8048848;
	*(int *)(((void *)ptr) + 104) = number;
}

int main(int argc, char **argv) {
	if (argc == 1)
		exit(1);

	void *first_alloc = malloc(108);
	write_addr(first_alloc, 5);

	void *sec_alloc = malloc(108);
	write_addr(sec_alloc, 6);

	memcpy(first_alloc, argv[1], strlen(argv[1]));
}