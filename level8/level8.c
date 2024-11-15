#include <stdio.h>
#include <string.h>

int main(void) {
	void **ptr_1 = 0x8049aac;
	void **ptr_2 = 0x8049ab0;
	char *addr_print = "%p, %p \n";
	char str_input[128];

	while (1) {
		printf(addr_print, *ptr_1, *ptr_2);
		if (!fgets(str_input, 128, stdin))
			return 0;

		if (!strncmp(str_input, "auth ", 5)) {
			void *allocated = malloc(4);
			*ptr_1 = allocated;
			*(int *) allocated = 0;
		}

		if (!strncmp(str_input, "reset", 5)) {
			free(*ptr_1);
		}

		if (!strncmp(str_input, "service", 6)) {
			*ptr_2 = strdup(str_input + 7);
		}

		if (!strncmp(str_input, "login", 5)) {
			if (*ptr_1 + 32 != 0) {
				system("/bin/sh");
			}
		}

		fwrite("Password:\n", 1, 10, stdout);
	}
	return 0;
}