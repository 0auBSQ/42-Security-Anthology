struct message {
	char		msg[140];
	char		user[40];
	uint32_t	intended_len;
};

void	secret_backdoor(void) {
	char	stack[128];	// sub 0x80 => 890:	48 83 c4 80          	add    rsp,0xffffffffffffff80

	fgets(stack, 128, stdin); // 0x80
	system(stack);
}

void	handle_msg(void) {
	//	8c4:	48 81 ec c0 00 00 00 	sub    rsp,0xc0 <= 192 stack : 140 bytes msg + 40 bytes username + 4 bytes len + 8 bytes struct pointer
	//	8cb:	48 8d 85 40 ff ff ff 	lea    rax,[rbp-0xc0]
	//	8d2:	48 05 8c 00 00 00    	add    rax,0x8c
	//	8d8:	48 c7 00 00 00 00 00 	mov    QWORD PTR [rax],0x0 <= NULL init 40 bytes of memory
	//	8df:	48 c7 40 08 00 00 00 	mov    QWORD PTR [rax+0x8],0x0 
	//	8e7:	48 c7 40 10 00 00 00 	mov    QWORD PTR [rax+0x10],0x0
	//	8ef:	48 c7 40 18 00 00 00 	mov    QWORD PTR [rax+0x18],0x0
	//	8f7:	48 c7 40 20 00 00 00 	mov    QWORD PTR [rax+0x20],0x0
	//	8ff:	c7 45 f4 8c 00 00 00 	mov    DWORD PTR [rbp-0xc],0x8c <= 140 bytes buffer
	struct message msg;
	
	(uint64_t)msg.msg[0] = 0;
	(uint64_t)msg.msg[8] = 0;
	(uint64_t)msg.msg[16] = 0;
	(uint64_t)msg.msg[24] = 0;
	(uint64_t)msg.msg[32] = 0;
	set_username(&msg);
	set_msg(&msg);
	puts(">: Msg sent!");
}

void	set_username(struct message *msg) {
	char	stack[160]; // Stack : 0xa0
	
	bzero(stack + 16, 16 * 8);
	puts(">: Enter your username");
	printf(">>: ");
	fgets(stack + 16, 128, stdin); // 0x80
	for (int i = 0; i <= 40; i++) {
		if (stack[16 + i] == 0)
			break ;
		msg->user[i] = stack[16 + i];
	}
	printf(" %s", msg->user);
}

void	set_msg(struct message *msg) {
	char	stack[1040]; // Stack : 0x410
	
	bzero(stack + 16, 128 * 8);
	puts(">: Msg @Unix-Dude");
	printf(">>: ");
	fgets(stack + 16, 1024, stdin); // 0x400
	strncpy(msg->msg, stack + 16, msg->intended_len);
}

int 	main(void) {
	puts("--------------------------------------------\n|   ~Welcome to l33t-m$n ~    v1337       |\n--------------------------------------------");
	handle_msg();
	return (0);
}