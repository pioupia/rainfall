int main(int argc, char **argv) {
	if (atoi(argv[1]) != 0x1a7) return 1;
	setresuid(geteuid(), geteuid(), geteuid());
	char *new_argv[] = {NULL};
	execv("/bin/sh", new_argv);
}