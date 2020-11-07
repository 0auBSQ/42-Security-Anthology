void greetuser(char **buf) {
	char stack[88];
	int g = *(&0x8049988); // Global var initialised to 0
	if (g == 1) {
		strcpy(stack + 16, "Hyvää päivää ");
	}
	else if (g == 2) {
		strcpy(stack + 16, "Goedemiddag! ");
	}
	else {
		strcpy(stack + 16, "Hello ");
	}
	strcat(stack + 16, *buf);
	puts(stack + 16);
}

int main(int argc, char **argv) {
	char stack[160];
	char *s1 = stack + 80; // offset esp + 0x50
	if (argc == 3) {
		//	8048548:	8d 5c 24 50          	lea    ebx,[esp+0x50]
		//	804854c:	b8 00 00 00 00       	mov    eax,0x0
		//	8048551:	ba 13 00 00 00       	mov    edx,0x13
		//	8048556:	89 df                	mov    edi,ebx
		//	8048558:	89 d1                	mov    ecx,edx
		//	804855a:	f3 ab                	rep stos DWORD PTR es:[edi],eax
		bzero(s1, 19);
		strncpy(s1 , argv[1], 40);
		strncpy(s1 + 40 , argv[2], 32); // add eax, 0x28
		char *e = getenv("LANG");
		if (e) {
			if (!memcmp(e, "fi", 2)) {		// 0x804873D
				*(&0x8049988) = 1;
			}
			else if (!memcmp(e, "nl", 2)) {	// 0x8048740
				*(&0x8049988) = 2;
			}
		}
		strncpy(??, s1, 19);
		greetuser(&s1);
		return (0);
	}
	return (1);
}