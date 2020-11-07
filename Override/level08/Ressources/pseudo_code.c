void	log_wrapper(FILE *fs, char *status, char *filename) {
	char stack[0x130];
	size_t s;
	
	strcpy(stack, status); // rbp - 0x130
	s = strlen(stack);
	snprintf(stack[s], 0xfe - (n - 1), filename); // Why ? Why not strncat ?
	stack[strcspn(stack, "\n")] = 0
	fprintf(fs, "LOG: %s\n", stack);
	
	// Canary
}

int	main(int argc, char **argv) {
	char	stack[0x130];
	FILE	*fs;
	FILE	*log;
	
	if (argc != 2)
		printf("Usage: %s filename\n", argv[0]);
	if ((log = fopen("./backups/.log", "w")) == NULL) {
		printf("ERROR; Failed to open %s\n", "./backups/.log");
		exit(1);
	}
	log_wrapper(log, "Starting back up: ", argv[1]);
	if ((fs = fopen(argv[1], "r")) == NULL) {
		printf("ERROR: Failed to open %s\n", argv[1]);
		exit(1);
	}
	strcpy(&stack[0x130 - 0x70], "./backups");
	// For the strlen, during this loop :
	//   400b48:	f2 ae                	repnz scas al,BYTE PTR es:[rdi]
	//	rax is dec from 0 at each loop and used with not, which gives the length
	strncat(&stack[0x130 - 0x70], argv[1], 0x63 - (strlen(&stack[0x130 - 0x70]) - 1));
	if ((int fd = open(&stack[0x130 - 0x70], 0xc1, 0x1b0)) < 0) {
		printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
		exit(1);
	}
	while ((char c = fgetc(fs)) != 1) {		// GNL à la poubelle, cf man fgetc
		write(fd, &c, 1);
	}
	log_wrapper(log, "Finished back up ", argv[1]);
	fclose(fs);
	close(fd);
	return (0);
}