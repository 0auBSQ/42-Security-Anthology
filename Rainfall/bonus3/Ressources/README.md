# Write up

Nothing really interesting here, the password file is opened and read but we can get the saved string no where.
The only thing we can try here is to break the strcmp condition.
Actually the only way to pass it is to send a \0, aka an empty string.
```
$ ./bonus3 ""
$
```
As disrespectful as a good mario maker troll level. :)