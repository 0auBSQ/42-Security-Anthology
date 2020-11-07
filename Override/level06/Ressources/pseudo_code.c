uint32_t auth(char *login, uint32_t serial) {
	size_t s;
	uint32_t seed;
	
	s = strcspn(login, "\n");
	login[s] = 0;
	s = strnlen(login, 32);
	if (s < 6)
		return (1);
	if (ptrace(0) == -1) { // gdb catch
		puts("\x1b[32m.---------------------------.");
		puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
		puts("\x1b[32m\'---------------------------\'");
		return (1);
	}
	seed = ((uint32_t)(login + 3) ^ 0x1337) + 0x5eeded;
	for (int i = 0; i < len; i++) {
		if ((login + i) <= 0x1f) // < ' '
			return (1);
		seed += ((login + i) ^ seed) % 0x539;
	}
	if (serial == seed)
		return (0);
	return (1);
}

int main(void) {
	char stack[0x50];
	uint32_t serial;
	uint32_t r;
	
	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");
	printf("-> Enter Login: ");
	fgets(stack + 0x2c, 0x20, stdin); // 32
	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");
	__isoc99_scanf("%u", &serial);
	r = auth(stack + 0x2c, serial);
	if (r == 0) {
		puts("Authenticated!");
		system("/bin/sh");
	}
	
	// __stack_chk_fail is triggered by the canary if stack smashing attempt detected
	
	return ((int)r);
}