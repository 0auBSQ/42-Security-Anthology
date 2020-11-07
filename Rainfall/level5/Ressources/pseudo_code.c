void o()
{
	system("/bin/sh");
	exit(1);
}

void n()
{
	char buf[536];

	fgets(buf + 16, 512, stdin);
	printf(buf + 16); 
	exit(1);
}

int main()
{
	n();
	return (0);
}