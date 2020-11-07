# Write up

In the `/etc/passwd` file, we have `42hDRfypTqqnw` as password for flag01.
The `/etc/passwd` passwords are hashed, so we have to find a way to crack it.
John The Ripper is very known for this kind of task.
We can't download it directly on the SnowCrash VM, so using scp we download the `etc/passwd` file : `scp -P 4242 level01@192.168.56.101:/etc/passwd ./passwd`
We crack our downloaded passwd file with john : `john passwd`
And we get the unhashed password :
```
Loaded 1 password hash (descrypt, traditional crypt(3) [DES 128/128 SSE2-16])
Press 'q' or Ctrl-C to abort, almost any other key for status
abcdefg          (flag01)
1g 0:00:00:00 100% 2/3 9.090g/s 12663p/s 12663c/s 12663C/s raquel..bigman
```

Using `abcdefg` as password, we can access to the flag01 account.

## Softs

- John the ripper `sudo apt install john`

## Sources

https://www.oreilly.com/library/view/practical-unix-and/0596003234/ch04s03.html