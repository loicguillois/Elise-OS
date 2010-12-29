; conversion azerty

azerty:

	cmp al, 0x8
	jne espace
	mov ah, 0x3
	mov bh, 0x0
	int 0x10     ; lit position actuelle
	cmp dl, 0x9
	jl espace
	dec dword [compteur]
	mov dword ecx, [compteur]
	xor al, al
	mov [buffer_inv + ecx], al
	mov ah, 0x3
	mov bh, 0x0
	int 0x10     ; lit position actuelle
	mov ah, 0x2
	dec dl
	mov bh, 0x0
	int 0x10    ; Support pour la touche suppr. arrière
	mov al, 0x20
	call affich_char
	mov ah, 0x3
	mov bh, 0x0
	int 0x10     ; lit position actuelle
	mov ah, 0x2
	dec dl
	mov bh, 0x0
	int 0x10
	jmp main

	espace:
		cmp al, 0x20 ; conserve espace
		jne a
	ret

	a:
		cmp al, 0x71  ; passe le q en a
		jne z
		mov al, 0x61
	ret

	z:
		cmp al, 0x77  ; passe le w en z
		jne q
		mov al, 0x7a
	ret

	q:
		cmp al, 0x61  ; passe le a en q
		jne m
		mov al, 0x71
	ret

	m:
		cmp al, 0x3b  ; passe le ; en m
		jne w
		mov al, 0x6d
	ret

	w:
		cmp al, 0x7a  ; passe le z en w
		jne exlu_qwerty
		mov al, 0x77
	ret

	exlu_qwerty:    ; bloque ce qui n'est pas azerty

		cmp al, 0x30
		jge fin_azerty1 ; vire les valeurs ascii inférieurs à 0x30
		jmp main ; retourne à main pas besoin de stocker une valeur non affichable

	fin_azerty1:
		cmp al, 0x7a    ; vire les valeurs ascii supérieurs à 0x7a
		jle fin_azerty2
		jmp main

	fin_azerty2:
		cmp al, 0x39
		jle fin_azerty  ; vire les valeurs ascii entre 0x39 et 0x61 
		cmp al, 0x61
		jge fin_azerty
		jmp main

	fin_azerty:
	ret