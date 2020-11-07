void p(char **buf)
{
	printf(*buf);
}

void n()
{
	char buf[536];

	fgets(buf + 16, 512, stdin);
	p(&(buf + 16));
	if (*((int*)0x8049810) == 0x1025544)
	{
		system("cat /home/user/level5/.pass");
	}
}

int main()
{
	n();
	return (0);
}