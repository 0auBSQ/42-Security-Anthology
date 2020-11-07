int main(int argc, char **argv) {
	 char buff[40]; // Stack : esp + 14
	 int av1 = atoi(argv[1]); // Stack : esp + 0x3c, 40 byte offset
	 if (av1 <= 9) {
		 memcpy(buff, argv[2], 4 * av1); // argv[2] : DWORD PTR [ebp+0xc] + 0x8
		 if (av1 == ﻿1464814662) { // 0x574f4c46
			 execl("sh", "/bin/sh", 0);
		 }
		 return (0);
	 }
	 return(1);
 }