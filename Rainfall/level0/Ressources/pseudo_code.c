int main(int argc, char **argv)
{
	if (atoi(argv[1] != 423))
		puts("No !")
	else {
		setresgid(getegid(), getegid());
		setresuid(geteuid(), geteuid());
		execv("/bin/sh");
	}
}
