%define BASE 0x100
%define KSIZE 3; nombre de secteurs de 512 octets a charger

[BITS 16]
[ORG 0x0]

jmp start
start:
	
	mov [bootdrv],dl; recuparation de l'unite de boot
	
	; initialisation des segments en 0x07C0
	mov ax,0x07C0
	mov ds,ax
	mov es,ax
	mov ax,0x8000; stack en 0xFFFF
	mov ss,ax
	mov sp, 0xf000
	
	; charger le noyau
	xor ax,ax
	int 0x13
	push es
	mov ax,BASE
	mov es,ax
	mov bx,0
	mov ah,2
	mov al,KSIZE
	mov ch,0
	mov cl,2
	mov dh,0
	mov dl,[bootdrv]
	int 0x13
	pop es
	
	; saut vers le kernel
	jmp dword BASE:0
	bootdrv: db 0

	;; NOP jusqu'a 510
	times 510-($-$$) db 144
	dw 0xAA55
