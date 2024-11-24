#include <stdio.h>

int main(int argc, char **argv) {
	char	str[132];

	FILE	*file = fopen("/home/user/end/.pass", "r");

	bzero(str, 33);

	if (!file || argc != 2) {
		return 0;
	}

	fread(str, 1, 66, file);
	str[65] = 0;
	*((char *) atoi(argv[1]) + 24) = 0;

	fread(str + 66, 1, 65, file);
	fclose(file);

	if (!strcmp(str, argv[1]))
		execl("/bin/sh", "sh", 0);
	else
		puts(str + 66);
	return (0);
}