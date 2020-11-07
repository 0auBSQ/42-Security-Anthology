# Write up

The subject here looks very similar, except that the ls function is executed
Using `nm -u ./level07`, we notice that the asprintf function is also used
By using the same tests as the level03, we notice that the program still show `level07`, `/bin/ls` might be directly put

But to be sure if it's the case, I try to execute it in the tmp folder, with a different name : `cp level07 /tmp/test/level07bis`
But I still get `level07`... strange
The program seems to do a call to the binary `/usr/bin/whoami` directly

I expected an IFS issue first, but changing the IFS env value change nothing here (This exploit is patched in recent linux distributions)
Remembering that the asprintf function is used, I decide to do a fresh start and execute the following command : `env -i ./level07`
Which executes the `level07` prog but without any env variable
And by surprise, I get this result : `sh: 1: Syntax error: word unexpected (expecting ")")`
Which leads me to the conclusion that the asprintf function concats a program path (in raw) and an environnment variable value
Two env variables contains the level07 value : `USER` and `LOGNAME`, `env -i 'USER=test' ./level07` gives the same message,
but `env -i 'LOGNAME=test' ./level07` gives me `test`, which means that the system call is actually `/bin/echo` followed by the LOGNAME value

The following payload finally gives me the flag : `env -i 'LOGNAME=a;getflag' ./level07`

## Sources

http://gits.hydraze.org/article-14-la-faille-de-system.html