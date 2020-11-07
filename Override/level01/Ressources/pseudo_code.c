int verify_user_name() {
	puts("verifying username....\n");
	char *p1 = 0x804a040; // scanned
	char *p2 = 0x80486a8; // dat_wil in .rodata
	return (strncmp(p1, p2, 7));
}

int verify_user_pass(char *to_cmp) {
	puts("verifying username....\n");
	char *p1 = to_cmp; // scanned
	char *p2 = 0x80486b0; // admin in .rodata
	return (strncmp(p1, p2, 5));
}

int main() {
	char stack[96];
	puts("********* ADMIN LOGIN PROMPT *********");
    	printf("Enter Username: ");
	fgets(0x804a040 , 160, stdin);
	if (verify_user_name())
		puts("nope, incorrect username...\n");
	else {
		puts("Enter Password: ");
		fgets(stack + 28 , 100, stdin);
		verify_user_pass(stack + 28);
		puts("nope, incorrect password...\n");
	}
	return (0);
}
