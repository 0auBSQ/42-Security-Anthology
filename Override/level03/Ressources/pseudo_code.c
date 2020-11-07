void decrypt(unsigned int arg) { // Breaking it is unnecessary
	char stack[0x40];
	
	stack[0x1d] = 0x757c7d51;
	stack[0x19] = 0x67667360;
	stack[0x15] = 0x7b66737e;
	stack[0x11] = 0x33617c7d;
	
	size_t len = strlen(&stack[0x1d]);  // lea    eax,[ebp-0x1d]
	for (i = 1; i < len; i++) {
		*(&stack[0x1d] + i) = (unsigned int)(*(&stack[0x1d] + i)) ^ arg;
	}
	if (!strncmp(&stack[0x1d], "Congratulations!", 17)) {
		system("/bin/sh");
	}
	else {
		puts("Invalid Password");
	}
}

void test(unsigned int input, unsigned int global) {
	if ((global - input) > 0x15) {
		decrypt(rand());
	}
	else {
		decrypt(global - input);
	}
}

int main() {
	unsigned int stack[8] = {0}; // 32 bytes
	srand(time(NULL));
	puts("***********************************");
	puts("*               level03         **");
	puts("***********************************");
	printf("Password:");
	scanf("%u", &stack + 1);
	test(stack + 1, 0x1337d00d);
}