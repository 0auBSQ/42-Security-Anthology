void main() {
	char stack[144]; // esp - 0x90
	
	fgets(stack + 40, 100, stdin);
	str_to_lower(stack + 40); // Simple boucle effectuant un xor 32 sur chaque char dans le code asm
	printf(stack + 40);
	exit(0);
}