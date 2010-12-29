;Elise v0.11 - 2003

[BITS 16] ; mode réel
[ORG 0x0]

jmp start

%include "fonctions.inc"
%include "affichage.inc"
%include "clavier.inc"
%include "temps.inc"

; Variables du noyau
buffer_inv: times 7 db 0
compteur: dd 0

start:

	; Initialisation de la mémoire vive
	mov ax,0x100
	mov ds,ax
	mov es,ax
	mov ax,0x8000
	mov ss,ax
	mov sp, 0xf000

	; Initialisation de l'affichage
	call clrscr
	call os_ban
	call inv_text

	; boucle principal du noyau
	main:
		mov ah,0x10
		int 0x16          ; Récupère une touche saisie par l'utilisateur
		cmp al, 0xd
		jne main_in
		call saut_ligne
		call system
		call inv_text
		mov ecx, 0x7
		xor al, al

		; permet d'effacer totalement le buffer_inv	
		eff:
			mov [buffer_inv + ecx], al
			dec ecx
			cmp ecx, 0
		jne eff
		
		mov [buffer_inv + ecx], al
	jmp main

	; affiche et recupere la saisie 
	main_in:
		call azerty ; permet de passer les caractères au format azerty
		cmp dword [compteur], 0x7 ; bloque l'invite à 7 pour pas de bof
		je main
		mov dword ecx, [compteur]
		mov [buffer_inv + ecx], al
		inc dword [compteur] ; utile pour concatenation
		call affich_char   ; Affiche caractère
	jmp main

; nop jusqu'à 1,40mo pour former une image valide pour vmware
;times 1474048-($-$$) db 144