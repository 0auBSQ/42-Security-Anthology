void main() {
	char stack[176]; // esp - b0
	pid_t proc = fork(); // esp + 0xac 
	int a = 0; // esp + 0x1c
	
	// 80486e6:	b8 00 00 00 00       	mov    eax,0x0
	// 80486eb:	ba 20 00 00 00       	mov    edx,0x20
	// 80486f0:	89 df                	mov    edi,ebx
	// 80486f2:	89 d1                	mov    ecx,edx
	// 80486f4:	f3 ab                	rep stos DWORD PTR es:[edi],eax
	bzero(stack + 32, 32);

	if (proc == 0) { // child proc
		prctl(1, 1);
		ptrace(0, 0, 0, 0);
		puts("Give me some shellcode, k");
		gets(stack + 32); // 144
	}
	if (ptrace(...)) { // parent proc
		wait(a);
		if ((a & 0x7f) > 0)
			puts("child is exiting...");
	}
	
	puts("no exec() for you");
	kill(proc, 9);
}