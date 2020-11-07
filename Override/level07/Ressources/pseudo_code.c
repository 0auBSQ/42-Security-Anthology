void clear_stdin(void) {
	while (((int ret = getchar()) != -1) && c != '\n') {}
}

uint32_t	get_unum(void) {
	uint32_t	unum;
	
	fflush();
	__isoc99_scanf("%u", &unum);
	clear_stdin();
	return (unum);
}

bool	store_number(uint32_t *array) {
	uint32_t	index;
	uint32_t	number;
	
	printf(" Number: ");
	number = get_unum();
	printf(" Index: ");
	index = get_unum();
	if ((index % 3 == 0) || (number >> 0x18 == 0xb7)) { // Escape 0xb7~ addrs (ie. shell code in env) and %3 indexes (including 114, the eip which is 3 x 38)
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return true;
	}
	array[index] = number;
	return false;
}

bool	read_number(uint32_t *array) {
	uint32_t	index;
	
	printf(" Index: ");
	index = get_unum();
	printf(" Number at data[%u] is %u\n", index, array[index]);
	return false;
}

int main(int argc, char **argv, char **env) {
	char stack[0x1d0];
	bzero(argv, sizeof(argv));
	bzero(env, sizeof(env));
	puts("----------------------------------------------------\n  Welcome to wil\'s crappy numberstorage service!   \n----------------------------------------------------\n Commands:                                         \n    store - store a number into the data storage    \n   read  - read a number from the data storage     \n    quit  - exit the program                       \n----------------------------------------------------\n   wil has reserved somestorage :>                 \n----------------------------------------------------\n"); // RIP 42 norm

	while (1) {
		bool error = true;
		printf("Input command: ");
		fgets(stack + 0x1b8, 0x14, stdin); // 20
		stack[0x1b8 + strlen(stack + 0x1b8)] = 0; // Null-terminate the string
		// 80488b7:	8d 84 24 b8 01 00 00 	lea    eax,[esp+0x1b8]
		// 80488be:	89 c2                	mov    edx,eax
		// 80488c0:	b8 5b 8d 04 08       	mov    eax,0x8048d5b
		// 80488c5:	b9 05 00 00 00       	mov    ecx,0x5
		// 80488ca:	89 d6                	mov    esi,edx
		// 80488cc:	89 c7                	mov    edi,eax
		// 80488ce:	f3 a6                	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi] <= strncmp equivalent
		if (!strncmp("store", stack + 0x1b8, 5))
			error = store_number((uint32_t)stack + 0x24);
		else if (!strncmp("read", stack + 0x1b8, 4))
			error = read_number((uint32_t)stack + 0x24);
		else if (!strncmp("quit", stack + 0x1b8, 4))
			return (0);						// ret instruction here for ret2libc doods !
		if (error != false)
			printf(" Failed to do %s command\n", stack + 0x1b8);
		else
			printf(" Completed %s command successfully\n", stack + 0x1b8);
		bzero(stack + 0x1b8, 0x14); // 20
	}
	
	// Canary here
}

// Stack offsets :
// 0x1b8 : Input command
// 0x24 : Uint table, offset 0x1d0 – 0x24 = 1ac => 428 bytes before stack top