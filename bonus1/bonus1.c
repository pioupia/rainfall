int main(int argc, char **argv) {
	int arg1 = atoi(argv[1]);
	char str[44];
	
	if (arg1 > 9) return 1;

	memcpy(str, argv[2], (arg1 * 4));

	if (arg1 != 0x574f4c46) return 0;

	execl("/bin/sh", "sh", 0);
}