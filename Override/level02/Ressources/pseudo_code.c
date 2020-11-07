int main() {
	char stack[288];
	
	bzero(stack + (288 - 112), 12); // 0x70
	bzero(stack + (288 - 160), 5); // 0xa0 (48)
	bzero(stack + (288 - 272), 12); // 0x110 (112)
	FILE *fs = fopen("/home/users/level03/.pass", "r");
	if (!fs) {
		fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
		exit(1);
	}
	if (fread(stack + (288 - 160), 1, 41, fs) != 41) {
		fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
		fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
		exit(1);
	}
	*(stack + (288 - 160) + strcspn(stack + (288 - 160), "\n")) = 0;
	fclose(fs);

	puts("===== [ Secure Access System v1.0 ] =====");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\***************************************/");
	printf("--[ Username: ");
	fgets(stack + (288 - 112), 100, stdin);
	*(stack + (288 - 112) + strcspn(stack + (288 - 112), "\n")) = 0;
	printf("--[ Password: ");
	fgets(stack + (288 - 272), 100, stdin);
	*(stack + (288 - 272) + strcspn(stack + (288 - 272), "\n")) = 0;
	puts("*****************************************");
	if (strncmp(stack + (288 - 160), stack + (288 - 272), 41)) {
		printf(stack + (288 - 112)); // Format string bug
		puts(" does not have access!");
	}
	printf("Greetings, %s!\n", stack + (288 - 112));
	system("/bin/sh");
	return (0);	
}
