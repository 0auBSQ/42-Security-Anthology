int main(int argc, char **argv)
{
	char a[32];
	while (1) {
	﻿	printf("%p, %p \n", 0x8049aac, 0x8049ab0);
	﻿	fgets(a, 0x80, stdin);
		if (a == NULL) // For example if CTRL-D
			break ;
		if (!strncmp(a, *0x8048819, 5)) {
			0x8049aac = malloc(4);
			if (strlen(&a[5]) <= 30)
				strcpy(0x8049aac, &a[5]);
		}
		if (!strncmp(a, *0x804881f, 5))
			free(0x8049aac);
		// This part looks odd, the "service" string is 7 char long but just writing "servic" is enough to trigger the command
		//  8048683:	b9 06 00 00 00       	mov    ecx,0x6
		//	8048688:	89 d6                	mov    esi,edx
		//	804868a:	89 c7                	mov    edi,eax
		//	804868c:	f3 a6                	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
		if (!strncmp(a, *0x8048825, 6))
			0x8049ab0 = strdup(&a[7]);
		if (!strncmp(a, *0x804882d, 5))
			if (*0x8049aac + 32)
				system("/bin/sh");
			else 
				fwrite(*0x804883b, 1, 10, stdout);
	}
}

// Data values
// a : each input
// 0x8048810 : %p, %p (size 7)
// 0x8048819 : auth (size 5)
// 0x804881f : reset (size 5)
// 0x8048825 : service (size 7)
// 0x804882d : login (size 5)
// 0x8048833 : /bin/sh (size 7)
// 0x804883b : Password: (size 9)

// Stack -> Heap pointers
// 0x8049aac : Set by "auth "
// 0x8049ab0 : Set by "service"