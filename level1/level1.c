#include <stdio.h>

void	run(void) {
	fwrite("Good... Wait what?", 1, 18, stdout);
	system("/bin/sh");
}

int main(void) {
	char str[64];
	gets(str);
	return;
}