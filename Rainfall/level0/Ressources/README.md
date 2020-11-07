# Write up

We have a `level0` file owned by level1, which displays `No !` when we give it an argument and gives a Segmentation fault when we give it no arguments.
We download it : `scp -p 4242 level0@192.168.43.94:level0 bin` to disassemble it directly with `objdump -d bin0 > asm0.txt`
We isolate the main function, starting at line 1176 / `0x08048ec0` address.

We notice that the program compare the atoi value of the first argument with `0x1a7` (423 in hex) :
```
 8048ed4:	e8 37 08 00 00       	call   8049710 <atoi>
 8048ed9:	3d a7 01 00 00       	cmp    $0x1a7,%eax
 8048ede:	75 78                	jne    8048f58 <main+0x98>
```
If the atoi value isn't 423, the jne instruction jump us to the `0x8048f58` address, which displays "No !" using the fwrite function and exits the program.

We try to execute the following command in the VM : `./level0 423` and get a prompt.
We write the ls command to check the result and get `ls: cannot open directory .: Permission denied`.
Seems like we got a shell, we get our flag by writing the following line : `cat /home/user/level1/.pass`