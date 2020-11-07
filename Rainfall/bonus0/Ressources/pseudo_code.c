void p(char **buf, char *s) {
	char stack[4120];
	puts(s);
	read(stdin, stack + 16, 4096); 
	*strchr(stack + 16, 10) = 0; // Stops at the first line feed
	strncpy(*buf, stack + 16, 20); // Copy 20 chars, \0 terminated if less than 20 chars, s2 is divergent if not terminated (no bzero)
}

void pp(char **s) {
	char stack[80]
	char *s1 = stack + 32;
	char *s2 = stack + 52;
	p(&s1, " - "); // 0x80486a0 stored litteral
	p(&s2, " - "); // Directly follows the previous buffer, s1 overflows here
	strcpy(*s, s1);
	*s[strlen[*s]] = 32; // 0x80486a4 global (0x20), memory segment : ﻿080486A0 20 2D 20 00 [20] 00, repnz scas al,BYTE PTR es:[edi] "SCan As String" instruction represents a pure ASM strlen function, the space between s1 and s2
	strcat(*s, s2);
}

int main() {
	char a[54]; // Stack is 64, however segfault occurs with at least 55 chars, esp offset is 22 (0x16)
	pp(&a);
	puts(a);
	return (0);
}
