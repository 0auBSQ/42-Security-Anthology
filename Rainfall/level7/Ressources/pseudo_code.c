void m()
{
	﻿printf("%s - %d\n", (char*)&0x8049960, time(null));
}

int main(int argc, char **argv)
{
	struct s *a = malloc(8);
	struct t *b = malloc(8);
	a->c = malloc(8);
	b->d = malloc(8);

	﻿strcpy((char*)a->c, argv[1]);
    strcpy((char*)b->d, argv[2]);
	
    fgets((char*)&0x8049960, 0x44, fopen("/home/user/level8/.pass", "r"));
    puts("~~");
}
