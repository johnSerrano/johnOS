; params: dh = number of sectors to load, dl = drive to load from, es:bx = memory location to load to

; dependency note: calling file must include print_string.asm

disk_load:
	pusha			; push all vars
	push dx			; store dx so we can recall original value

	mov ah, 0x02		; BIOS read sector 
	mov al, dh		; number of sectors to read
	mov ch, 0x00		; cylander 0
	mov dh, 0x00		; head 0
	mov cl, 0x02		; read from second sector

	int 0x13		; do read

	jc disk_error_c		; catch diskerror 

	pop dx 
	cmp dh, al		; check if correct number of sectors read
	jne disk_error

	popa
	ret			; fin

disk_error_c:
	mov bx, ERRMSGC
	call print_string_16

disk_error:
	
	mov bx, ERRMSG
	call print_string_16
	jmp $

ERRMSG:
	db "Failed to read from disk correctly.", 0

ERRMSGC:
	db "C: ", 0
