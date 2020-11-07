void v()
{
	char buf[536];
	
	fgets(buf + 16, 512, stdin);
	printf(buf + 16); 
	if (*((int*)0x804988c) == 0x40)
	{
		printf("Wait what?!");
		system("/bin/sh");
	}
}

int main()
{
	v();
	return (0);
}