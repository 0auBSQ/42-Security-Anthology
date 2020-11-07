# Write up

Last level for the mandatory part before the bonus part here
Like the level08, we have 2 files : `level09` and `token`
This time, we can read the token file directly with cat, but we get some non-printable chars and nothing currently relevant

We decide, like for the level08, to decompile the level09 executable.
Which gives us some interesting lines :
```
﻿if (eax_28 < 0x00)
        puts("You should not reverse this");
    else if (getenv("LD_PRELOAD") != null)
        fwrite(&globals->v8048B98, 0x01, 0x25, globals->ptr804A040);
    else if (open("/etc/ld.so.preload", 0x00) > 0x00)
        fwrite(&globals->v8048B98, 0x01, 0x25, globals->ptr804A040);
    else if (syscall_open() == ~0x00)
        fwrite(&globals->v8048BE4, 0x01, 0x46, globals->ptr804A040)
```
With the globals pointers giving these strings :
```
LD_PRELOAD Injection Linked lib detected
/proc/self/maps in unaccessible, probably a LD_PRELOAD attempt
```
It can means that LD_PRELOAD exploits are expected, also, the `level09` executable doesn't open a file, and decrypt any string we give it as an argument
We seems to have to execute the level09 executable with the token contents
We try this command : `./level09 "$(< token)"`
However we still get nothing revealant
A closer investigation of the result : `./level09 "$(< token)" | od -vAn -tx1c`
Shows us that the `level09` program actually increase the ascii value of each char by their position
We will try to reverse it until it becomes a fully intelligible string

We upload our divine perl script directly on the VM tmp folder :
`scp -P 4242 lidlhaxxor.pl level09@192.168.56.101:/tmp/lidlhaxxor.pl`

And we execute it, the flag09 password is optained in the first reverse attempt :
```
level09@SnowCrash:~$ perl /tmp/lidlhaxxor.pl "$(< token)"
=== LIDL Haxxor ===
Your string LIDLed :
f3iji1ju5yuevaus41q1afiuq
```

## Ressources

- Reko Decompiler (http://decompiler.sourceforge.net/)