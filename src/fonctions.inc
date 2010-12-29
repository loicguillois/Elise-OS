%include "messages.inc"
%include "syscall.inc"

; Emettre un bip avec le buzzer
bip:
	mov al, 0x7
	mov [es:bx], al
	mov ah, 0xe
	int 0x10
ret

; Redémarre l'ordinateur
reboot:
	db 0xea
	dw 0x0
	dw 0xffff
ret

; gère l'execution des appels systèmes à mettre dans fichier séparé
system:

	push ds
	pop es

	mov si, sys01
	mov di, buffer_inv   ; Permet le reboot marche mais normalement OFFSET buffer_inv
	mov cx, 7            ; à remplacer par times 7
	repe cmpsb           ; Problème : marche aussi pour rebootmmfm il faut comparer longueurs !
	cmp cx, 0
	jne suiv1
	mov ecx, 6
	mov al, 0
	cmp [buffer_inv + ecx], al
	jne suiv1
	call reboot
ret

suiv1: ; donner des noms plus explicite

	mov si, sys02
	mov di, buffer_inv   ; Permet d'effacer l'ecran
	mov cx, 4
	repe cmpsb
	cmp cx, 0
	jne suiv2
	mov ecx, 3
	mov al, 0
	cmp [buffer_inv + ecx], al
	jne suiv2
	call clrscr
	call os_ban
ret

suiv2:

	mov si, sys03
	mov di, buffer_inv   ; Permet d'afficher l'aide
	mov cx, 5
	repe cmpsb
	cmp cx, 0
	jne suiv3
	mov ecx, 4
	mov al, 0
	cmp [buffer_inv + ecx], al
	jne suiv3
	call saut_ligne
	mov si, msg02
	call affich_text
	call saut_ligne
	call saut_ligne
	mov si, msg03
	call affich_text
	call saut_ligne
	mov si, msg05
	call affich_text
	call saut_ligne
	mov si, msg06
	call affich_text
	call saut_ligne
	mov si, msg07
	call affich_text
	call saut_ligne
	mov si, msg08
	call affich_text
	call saut_ligne
ret

suiv3:

; Buzzer

	mov si, sys04
	mov di, buffer_inv   ; Permet de bipper
	mov cx, 4
	repe cmpsb
	cmp cx, 0
	jne suiv4
	mov ecx, 3
	mov al, 0
	cmp [buffer_inv + ecx], al
	jne suiv4
	call bip
ret

suiv4:

; date

	mov si, sys05
	mov di, buffer_inv   ; Permet d'afficher la date
	mov cx, 5
	repe cmpsb
	cmp cx, 0
	jne suiv5
	mov ecx, 4
	mov al, 0
	cmp [buffer_inv + ecx], al
	jne suiv5
	call date
ret

suiv5:

; heure

	mov si, sys06
	mov di, buffer_inv   ; Permet d'afficher la date
	mov cx, 6
	repe cmpsb
	cmp cx, 0
	jne fin_sys
	mov ecx, 5
	mov al, 0
	cmp [buffer_inv + ecx], al
	jne fin_sys
	call heure
ret

fin_sys:
	call saut_ligne
	mov si, msg04       ; gère les commandes invalides
	call affich_text
	call saut_ligne
ret