void p()
{
	char buf[100];

	fflush(stdin);
	gets(buf + 24);
	if (((uint32_t)buf[100] & 0xB0000000) != 0xB0000000)
	{
		puts(buf + 24);
		strdup(buf + 24); 
	}
	else
	{
		printf("(%p)\n", (uint32_t)buf[100]);
		exit(1);
	}
}

int main(int argc, char **argv)
{
	p();
	return (0);
}