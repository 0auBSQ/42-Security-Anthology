##### ###############
### Dirty Cow ######
##### ###############

Ouverture fichier root/etc/passwd


`f = open(argv[1], O_RDONLY)`

`map = mmap()` -> mapping du fichier dans une nouvelle zone mémoire (en lecture seule)
					accès en lecture (copie si modification)

la seconde fonction lancée en parallèle de la première va drop le cache du fichier.

Deux threads :
	 - un qui va écrire dans le mapping du fichier
	- un qui va drop le cache du fichier

La race condition est une faille qui consiste à provoquer un effet indésirable par l'exécution dans un ordre spécifique des tâches.
L'exploit du dirtycow consiste : 


à mapper le fichier dans la mémoire et écrire dessus
à drop le cache du fichier de la mémoire
à mapper le fichier dans la mémoire et écrire dessus
à drop le cache du fichier de la mémoire
à mapper le fichier dans la mémoire et écrire dessus
à drop le cache du fichier de la mémoire
à mapper le fichier dans la mémoire et écrire dessus
à drop le cache du fichier de la mémoire
à mapper le fichier dans la mémoire et écrire dessus
à drop le cache du fichier de la mémoire
à mapper le fichier dans la mémoire et écrire dessus
à drop le cache du fichier de la mémoire
à mapper le fichier dans la mémoire et écrire dessus
à drop le cache du fichier de la mémoire
à mapper le fichier dans la mémoire et écrire dessus
à drop le cache du fichier de la mémoire
à mapper le fichier dans la mémoire et écrire dessus
à drop le cache du fichier de la mémoire
à mapper le fichier dans la mémoire et écrire dessus
à drop le cache du fichier de la mémoire

À un moment, le premier process va essayer d'écrire sur le fichier au moment où le cache de celui-ci a été drop. Il finit donc par écrire sur le fichier original détenu par root.
On peut écrire sur le fichier /etc/passwd
