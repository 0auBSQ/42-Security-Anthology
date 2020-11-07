# Write up

Last level for this project now.
No file in the home folder, so like before we search files where level14 or flag14 have the rights in :
```
find / -user 'level14' -exec readlink -f {} \; 2> /dev/null | grep -v "proc"
find / -user 'flag14' -exec readlink -f {} \; 2> /dev/null | grep -v "proc"
```
Nothing relevant for level14, nothing at all for flag14.
I also tried a nmap to see if any port is open/any port is listening, but only the 80 and the 4242 are listening.
80 for a sample "hello world" page, 4242 for the VM ssh.

Since there is nothing to exploit here, the only thing left we can try to break is the `getflag` program :
```
(VM)
whereis getflag
(local machine)
scp -P 4242 level14@192.168.56.101:/bin/getflag getflag
```

We then one more time use the Reko decompiler to see what's going on.
We can see the program is LD_PRELOAD protected and contains the ft_des function as well.
The programm check the uid with the getuid() function, and store it in the eax register :
```
﻿(Dissassembled ASM)
08048AFD E8 AE F9 FF FF call getuid
08048B02 89 44 24 18 mov [esp+18],eax
(Decompiled C)
﻿Eq_477 eax_120 = getuid();
```
This uid value is compared with multiple values which gives the flag for each level.
To get the flag14 uid value, we check using the `id flag14` command.
Which gives us : 
```
uid=3014(flag14) gid=3014(flag14) groups=3014(flag14),1001(flag)
```
We convert the result in hex to get `0xBC6` which corresponds with this condition :
```
﻿else
{
    union Eq_408 * eax_283 = globals->ptr804B060;
    ft_des("G8H.6,=4k5J0<cd/D@>>B:>:4");
    fputs(eax_283, eax_283);
}
```
To be able to reach it, we will need to set the `eax` register content to `0xBC6` just after the getuid() call.
We will need, with gdb to use breakpoints and manualy edit the `eax` register content.
However, there is a ptrace call which prevents us to use gdb, we will have to bypass it :
```
(ptrace bypass)
gdb getflag
catch syscall ptrace
commands 1
set ($eax) = 0
continue
end
(getuid bypass, changing the eax register value at the 08048B02 address we saw in the dissassembled ASM)
break *0x08048B02
commands 2
set ($eax) = 0xBC6
continue
end
run
(result)
Check flag.Here is your token : 7QiHafiNa3HVozsaXkawuYrTstxbpABHD8CPnHJ
```
We got the last flag, great :)

... but this trick works for any flag in this VM, is it a huge troll ? Is it possible to get all flags at once from the level00 ?
To be continued.

## Ressources

- Reko Decompiler (http://decompiler.sourceforge.net/)

## Sources

https://gist.github.com/poxyran/71a993d292eee10e95b4ff87066ea8f2#file-easy-bypass-for-ptrace-ptrace_traceme-0-0-in-gdb-L15