# Write up

We got now an executable which prompt asking for a password only.
NX (Non-executable stack) and Canary are activated here so I guess we're not searching for a buffer overflow.
By dissassembling the code, we notice that we have a random encrypt algorithm, and 21 (0x15) fixed values.
A value out of range is set to random so non-exploitable, but we can try to bruteforce the 21 choices.
From `322424844 (0x1337d00c)` to `322424824 (0x1337cfec)`.
`322424827` gives us the shell.
```
level03@OverRide:~$ ./level03
***********************************
*               level03         **
***********************************
Password:322424827
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```