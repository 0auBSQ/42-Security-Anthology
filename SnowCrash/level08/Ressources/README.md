# Write up

Now we have a `token` file we want to open, and a `level08` executable
Using ls -l, we notice that the token file is readable only by flag08 :
```
-rwsr-s---+ 1 flag08 level08 8617 Mar  5  2016 level08
-rw-------  1 flag08 flag08    26 Mar  5  2016 token
```
The `level08` executable except a filename as argument, the command : `./level08 token` gives us the following error :
`You may not access 'token'`

I choosed to decompile the level08 file (after downloaded it) directly to C language
Which make me able to understand that the conditions which triggers the `You may not access` message in only a strstr on the filename :
`﻿if (strstr(dwArg08->ptr0004, "token") == null)`
To bypass this, I have to be able to target it with another filename, which doesn't contain the `token` key word
I tried first the symbolic link method :
```
level08@SnowCrash:~$ ln -s token /tmp/tok
level08@SnowCrash:~$ ./level08 /tmp/tok
```
But sadly the opening fails : `level08: Unable to open /tmp/tok: No such file or directory`

It's possible to rename any file in the folder if we have write access in this folder.
The level08 home folder doesn't give us this right, but since we're currently level08, we can grant ourself this right :
```
level08@SnowCrash:~$ chmod 777 .
level08@SnowCrash:~$ mv token tok
level08@SnowCrash:~$ ./level08 tok
```
This procedure lets us get the following token : `quif5eloekouj29ke0vouxean`, which is the flag08 account password.

## Ressources

- Reko Decompiler (http://decompiler.sourceforge.net/)