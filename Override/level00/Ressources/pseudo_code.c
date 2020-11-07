int main() {
    puts("***********************************");
    puts("* \t     -Level00 -\t\t  *");
    puts("***********************************");
    printf("Password:");	// Why printf here ???
	
	int i;
	scanf("%d", i);
	if (i == 5276) {
		puts("Authenticated!");
		system("/bin/sh");
	}
	else {
		puts("\nInvaid Password!");
	}

	return (0);
}
