hr: dw 0
min: dw 0
sec: dw 0
jour: dw 0
mois: dw 0
siecle: dw 0
annee: dw 0

; Affiche la date

date:

	;; affiche le jour
	mov word [jour], 0
	mov ah, 0x4 
	int 0x1a  ; lit la date
	shr dl, 0x4 ; d�calage pour r�cup�r� jours (dizaine)
	mov eax, 0xa
	mul dl
	mov [jour], al
	mov ah, 0x4 
	int 0x1a  ; lit la date
	and dl, 0xf ; masque pour r�cup�r� jours (unit�)
	add [jour], dl
	mov al, [jour]
	call AFFICHER_AL_DEC

	;; affiche la separation
	mov al, 0x2f
	call affich_char

	;; affiche le mois
	mov ah, 0x4 
	int 0x1a  ; lit la date
	shr dh, 0x4 ; d�calage pour r�cup�r� mois (dizaine)
	mov eax, 0xa
	mul dh
	mov [mois], al
	mov ah, 0x4 
	int 0x1a  ; lit la date
	and dh, 0xf ; masque pour r�cup�r� mois (unit�)
	add [mois], dh
	mov al, [mois]
	call AFFICHER_AL_DEC

	;; affiche la separation
	mov al, 0x2f
	call affich_char

	;; affiche l'annee
	mov ah, 0x4 
	int 0x1a  ; lit la date
	shr ch, 0x4 ; d�calage pour r�cup�r� siecle (dizaine)
	mov eax, 0xa
	mul ch
	mov [siecle], al
	mov ah, 0x4 
	int 0x1a  ; lit la date
	and ch, 0xf ; masque pour r�cup�r� siecle (unit�)
	add [siecle], ch
	mov al, [siecle]
	call AFFICHER_AL_DEC
	mov ah, 0x4 
	int 0x1a  ; lit la date
	shr cl, 0x4 ; d�calage pour r�cup�r� ann�e (dizaine)
	mov eax, 0xa
	mul cl
	mov [annee], al
	mov ah, 0x4 
	int 0x1a  ; lit la date
	and cl, 0xf ; masque pour r�cup�r� ann�e (unit�)
	add [annee], cl
	mov al, [annee]
	call AFFICHER_AL_DEC
ret

; Affiche l'heure
heure:
	mov word [hr], 0
	mov word [min], 0
	mov word [sec], 0

	;; affiche les heures
	mov ah, 0x2 
	int 0x1a  ; lit l'heure du bios
	shr ch, 0x4 ; d�calage pour r�cup�r� heures (dizaine)
	mov eax, 0xa
	mul ch
	mov [hr], al
	mov ah, 0x2 
	int 0x1a  ; lit l'heure du bios
	and ch, 0xf ; masque pour r�cup�rer heures (unit�)
	add [hr], ch
	mov al, [hr]
	call AFFICHER_AL_DEC

	;; affiche la separation
	mov al, 0x3a
	call affich_char

	;; affiche les minutes
	mov ah, 0x2 
	int 0x1a  ; lit l'heure du bios
	shr cl, 0x4 ; d�calage pour r�cup�r� minutes (dizaine)
	mov eax, 0xa
	mul cl
	mov [min], al
	mov ah, 0x2 
	int 0x1a  ; lit l'heure du bios
	and cl, 0xf ; masque pour r�cup�rer minutes (unit�)
	add [min], cl
	mov al, [min]
	call AFFICHER_AL_DEC

	;; affiche la separation
	mov al, 0x3a
	call affich_char

	;; affiche les secondes
	mov ah, 0x2 
	int 0x1a  ; lit l'heure du bios
	shr dh, 0x4 ; d�calage pour r�cup�r� minutes (dizaine)
	mov eax, 0xa
	mul dh
	mov [sec], al
	mov ah, 0x2 
	int 0x1a  ; lit l'heure du bios
	and dh, 0xf ; masque pour r�cup�rer minutes (unit�)
	add [sec], dh
	mov al, [sec]
	call AFFICHER_AL_DEC
ret