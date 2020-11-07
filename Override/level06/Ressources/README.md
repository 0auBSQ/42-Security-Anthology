# Write up

The program here contains multiple protections (RELRO & Canary), so we don't expect any buffer overflow here.

By dissassembling the binary we notice an hard-to-predict encrypt algorithm, however there is an equal check at the end so we will check the value using gdb.

Don't forget to catch ptrace too :)

The instruction that interests us is :
```
8048866:       3b 45 f0                cmp    eax,DWORD PTR [ebp-0x10]
```

So lets do this using a sample login :
```
gdb level06

catch syscall ptrace
commands 1
set ($eax) = 0
continue
end

break *0x08048866
run
Starting program: /home/users/level06/level06
***********************************
*               level06           *
***********************************
-> Enter Login: lidlpainfromage				// Sample login we will use here
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 45							// Sample serial
x/4u ($ebp - 0x10)
0xffffd618:     6241858 15      0       0	// 6241858 => Our wanted serial, eax is 45 here, and the DWORD PTR at ebp - 0x10 contains 6241858
```

Which gives us our shell :
```
level06@OverRide:~$ ./level06
***********************************
*               level06           *
***********************************
-> Enter Login: lidlpainfromage
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6241858
Authenticated!
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```