# Write up

Initial situation :
- No interesting file in the level00 home folder
- Nothing interesting in the /etc/passwd file (except something which looks interesting for the flag01)

I first try to execute this command :
`find / -name '*level00*' -exec readlink -f {} \; 2> /dev/null`
To check if there is any file which contains "level00" in its name, but no result

By reading the find man, I discover the -user option which display files owned by the specified user.
Using the following command :
`find / -user 'level00' -exec readlink -f {} \; 2> /dev/null`
I can see the list of the files owned by level00 (me, curently).
Nothing is really relevent here, but I try the following command :
`find / -user 'flag00' -exec readlink -f {} \; 2> /dev/null`
Which displays me 2 paths :
```
/usr/sbin/john
/rofs/usr/sbin/john
```
Using `cat` on those file, they both displays `cdiiddwpgswtgt`

I try to use it to access the flag00 account and... nope.

It doesn't look like a hash, and since it's the first step, I don't expect some sort of complicated code to decrypt.
I try to bruteforce the result using ROT (Caesar cipher) using this website : `https://md5decrypt.net/en/Caesar/`
Which gives `Caesar(15) = nottoohardhere`

I'm able to access the flag00 account with this password.

## Sources

https://elearning.intra.42.fr/notions/snow-crash/subnotions/snow-crash/videos/snow-crash
