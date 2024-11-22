#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int global_1 = 0;

void	greetuser(char *str) {
	char *str_store = 0x0804823c;

	if (global_1 == 1) { // fi
		// complete that
	} else if (global_1 == 2) { // nl
		*str_store = "Goedemiddag! ";
		str_store[4] = str_store[4];
		str_store[6] = str_store[6];
		str_store[12] = str_store[12];
	} else if (global_1 == 0) { // nothing
		*str_store = "Hello ";
		str_store[4] = str_store[4];
		str_store[6] = str_store[6];
	}

	strcat(str_store, str);
	puts(str_store);
}

int main(int argc, char **argv) {
	if (argc != 3) return 1;

	char str[76];

	bzero(str, 19);

	strncpy(str, argv[1], 40);
	strncpy(str + 40, argv[2], 32);

	char *lang_env = getenv("LANG");
	if (lang_env) {
		if (memcmp(lang_env, "fi", 2) == 0)
			global_1 = 1;
		else if (memcmp(lang_env, "nl", 2) == 0)
			global_1 = 2;
	}
	greetuser(memmove(lang_env, str, 19));
}

