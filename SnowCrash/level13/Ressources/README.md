# Write up

We have a `level13` executable which print `UID 2013 started us but we we expect 4242` when we try to execute it.
The program call the `getuid()` function to identify the user.
The program have no call to `system()`, so no call to the `getflag` command.

We download it, and decompile it, to see those interesting lines :
```
﻿Eq_188 eax_8 = getuid();
if (eax_8 == (char *) 4242)
{
    ft_des("boe]!ai0FB@.:|L6l@A?>qJ}I");
    printf("your token is %s\n", eax_8);
}
```
Here we can try different solutions :
- Reverse enginering the ft_des function
- Trying to bypass the getuid function call

We tried the reverse enginering method first (The attempt is consigned in the `level13.c` file) but an unidentified struct limited my capacities here.
So I decided to try the bypass method.
A popular method is to create a .so library and set his path to the LD_PRELOAD env variable, which let us fake the getuid function.

I create a fake getuid function, upload it and try to exploit it : 
```
(local machine)
scp -P 4242 lidllib.c level13@192.168.56.101:/tmp/lidllib.c
(VM)
gcc -shared -fPIC -o /tmp/lidllib.so /tmp/lidllib.c
export LD_PRELOAD=/tmp/lidllib.so
~/level13
UID 2013 started us but we we expect 4242
```
However, it doesn't work, we tried the LD_PRELOAD exploit with a fake malloc.so file and it worked, but here it doesn't.

There is no ptrace() call, so we try to execute it with gdb, still using the LD_PRELOAD thing :
```
gdb level13
(gdb) set environment LD_PRELOAD /tmp/lidllib.so
(gdb) run
Starting program: /home/user/level13/level13
your token is 2A31L79asukciNyi8uppkEuSx
[Inferior 1 (process 8589) exited with code 050]
```
Which gives us the flag. (We can log to level14 directly with it)

## Sources

https://stackoverflow.com/questions/10448254/how-to-use-gdb-with-ld-preload
