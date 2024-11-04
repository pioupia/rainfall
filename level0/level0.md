Première étape, ouvrir le binaire dans GDB, puis, désassembler la fonction `main`.

On peut voir au niveau des instructions les lignes suivantes :
```
0x08048ec6 <+6>:	sub    esp,0x20
0x08048ec9 <+9>:	mov    eax,DWORD PTR [ebp+0xc]
0x08048ecc <+12>:	add    eax,0x4
0x08048ecf <+15>:	mov    eax,DWORD PTR [eax]
0x08048ed1 <+17>:	mov    DWORD PTR [esp],eax
0x08048ed4 <+20>:	call   0x8049710 <atoi>
0x08048ed9 <+25>:	cmp    eax,0x1a7
0x08048ede <+30>:	jne    0x8048f58 <main+152>
[...]
0x08048f3d <+125>:	call   0x8054690 <setresuid>
0x08048f42 <+130>:	lea    eax,[esp+0x10]
0x08048f46 <+134>:	mov    DWORD PTR [esp+0x4],eax
0x08048f4a <+138>:	mov    DWORD PTR [esp],0x80c5348
0x08048f51 <+145>:	call   0x8054640 <execv>
```

On retire 32 à `esp`, ce qui laisse de la place pour les variables.
On déplace l'adresse (ou autre) contenu de `ebp+0xc` (+12 octets) sur 4 octets. En réalité, ici `0xc` correspond au pointeur sur argv[0]. 
Ensuite, on ajoute 4 au pointeur `eax`, ce qui nous fait passer à argv[1], puis on déplace dans `eax` le contenu (destack) du pointeur argv[1].
Enfin, on déplace cette valeur sur la base de la stack, ce qui va permettre de passer argv[1] en paramètre à `atoi`.

Puis, on appel la fonction `atoi` avec argv[1], et on compare le résultat à 423. Si le résultat est égal à 423, alors, on set le real user id à l'effective user id (pour le SUID et SGID flags).
Enfin, on exécute `execve` avec la string contenu dans l'adresse `0x80c5348`.

Checkons ça :
```
(gdb) x/1s 0x80c5348
0x80c5348:	 "/bin/sh"
```

Il ne reste plus qu'à exécuter le binaire avec 423 pour avoir un shell.

Le password: `1fe8a524fa4bec01ca4ea2a869af2a02260d4a7d5fe7e7c24d8617e6dca12d3a`