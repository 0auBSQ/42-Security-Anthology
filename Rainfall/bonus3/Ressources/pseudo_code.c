int main(int argc, char **argv) {
	char stack[160];
	﻿FILE *stream = fopen("/home/user/end/.pass", "r"); // 0x80486f0 and 0x80486f2
	bzero(stack + 24, 33);
	if (stream && argc == 2) {
		fread(stack + 24, 1, 66, stream); 
		stack[24 + atoi(argv[1])] = 0;
		fread(stack + 90, 1, 65, stream); // 24 + 66
		fclose(stream);
		if (!strcmp(stack + 24, argv[1])) {
			execl("/bin/sh", "sh", 0) // 0x8048707 and 0x804870a
		}
		else {
			puts(stack + 90);
		}
		return (0);
	}
	return (-1);
}