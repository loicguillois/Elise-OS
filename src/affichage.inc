; Affiche une chaine de caractères mettre tout affichage dans un fichier
affich_text:
	push ax
	push bx

	debut:
		lodsb ; ds:si -> al
		cmp al,0 ; fin chaine ?
		jz fin
		call affich_char
	jmp debut

	fin:
	pop bx
	pop ax
ret


; Affiche un caractère seul
affich_char:
	mov [es:bx], al
	mov ah, 0xe
	int 0x10
ret


; Affiche un saut à la ligne
saut_ligne:
	mov ah, 0x3
	xor bh, bh
	int 0x10     ; lit position actuelle
	mov ah, 0x2
	xor bh, bh
	inc dh
	xor dl, dl
	int 0x10
ret


; Efface l'écran
clrscr:
	xor ah, ah
	mov al, 3
	int 0x10
ret


; Affiche les informations de l'os
os_ban:
	mov si, msg00
	call affich_text
ret


; Affiche l'invite
inv_text:
call saut_ligne
mov si,msg01
call affich_text
ret

; Affiche un chiffre au format ascii
AFFICHER_AL_DEC:
	push bx
	push ax
	xor bh, bh
	mov bl, 0Ah

	boucle:
		xor ah, ah
		div bl
		push ax
		add al, 30h
		mov ah, 0Eh
		int 10h
		pop ax
		cmp bx, 1
		je finboucle
		mov bx, 1
		mov al, ah
	jmp boucle

	finboucle:
	pop ax
	pop bx
ret
