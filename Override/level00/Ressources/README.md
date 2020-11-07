# Write up

Download and dissassemble the file first :
```
scp -P 4242 level00@192.168.0.27:level00 bin00
objdump -M intel -d bin00 > asm0_intel.txt
```

We have an exercice very similar to the Rainfall level0 :
```
level00@OverRide:~$ ./level00
***********************************
*            -Level00 -           *
***********************************
Password:5276

Authenticated!
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```

Let's move on and go to the more serious stuff.